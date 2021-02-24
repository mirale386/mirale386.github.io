---
author: mirale
title: RISC-V 实现YOLO
date: 2021-2-24
description: an paper to collect info test Yolo on RISC-V
categories:
  - riscv
tags:
  - yolo
---

# 参考

https://github.com/riscv/riscv-gnu-toolchain

https://zhuanlan.zhihu.com/p/160950590

https://zhuanlan.zhihu.com/p/258394849

https://www.cnblogs.com/zjutzz/p/6125029.html

https://zhuanlan.zhihu.com/p/57613816

# 实验步骤

```
mkdir riscv-yolo
cd riscv-yolo
```

后续都在riscv-yolo文件夹下操作！

## riscv-gnu-toolchain 安装

### 前提条件

- ubuntu:

```
sudo apt install autoconf automake autotools-dev curl libmpc-dev libmpfr-dev libgmp-dev \
                 gawk build-essential bison flex texinfo gperf libtool patchutils bc \
                 zlib1g-dev libexpat-dev git \
                 libglib2.0-dev libfdt-dev libpixman-1-dev \
                 libncurses5-dev libncursesw5-dev
```

### 下载源码

`git clone --recursive https://github.com/riscv/riscv-gnu-toolchain`

国内受限于网络原因建议配置proxychains代理，或者用官方推荐的命令，或者用以下命令：

```
git clone https://gitee.com/mirrors/riscv-gnu-toolchain
cd riscv-gnu-toolchain
git rm qemu
git submodule update --init --recursive
```

### 编译工具链

- 裸机（newlib）

  ```
  ./configure --prefix=/opt/riscv-newlib  --enable-multilib
  sudo make -j ${nproc}
  ```

- linux（glibc）

  ```
  ./configure --prefix=/opt/riscv-glibc  --enable-multilib
  sudo make linux -j ${nproc}
  ```

- 注：${nproc} 替换成你设置的make线程数。

本次实验我们只用考虑linux环境，所以可以用linux标题下命令，去除`--enable-multilib`选项。

编译完成后，将`/opt/riscv-newlib/bin`、`/opt/riscv-glibc/bin`添加至PATH。

## QEMU安装

如果之前没有跟riscv-gnu-toolchain一起clone QEMU，需要执行以下命令，否则进入riscv-gnu-toolchain/qemu目录。

```
git clone https://git.qemu.org/git/qemu.git
```

编译安装：

```
../configure -–prefix=/opt/riscv-qemu –-target-list=riscv64-softmmu
sudo make
sudo make install
```
编译完成后，将`/opt/riscv-qemu/bin`添加至PATH。

## Buildroot搭建linux系统

https://buildroot.org/download.html网页下载buildroot。

执行以下命令，导入针对RISC-V64架构的默认配置到configs目录：
```
make qemu_riscv64_virt_defconfig
```

执行以下命令进行配置：
```
make menuconfig
```
- 注：可能需要NCurses（apt install）。

### Target Options

- Target Architecture: RISCV
- Target Architecture Size: 64-bit
- Target ABI: lp64d

### Toolchain

- C library: glibc
- Enable C++ support: 勾选

### Kernel

- Linux Kernel： 勾选
- RISCV64： Image

### Filesystem images

- ext2/3/4 root filesystem
- exact size: 文件目录大小，根据需要设置

### System configuration

Linux系统配置，包含主机名、root密码、shell类型和DHCP网络接口等。

### Bootladers

- opensbi： qemu/virt

### Target packages

根据需要选择你需要的shell命令，如git等。

### 启动镜像

保存设置，`make`完成编译（需要代理），制作的镜像在/output/images目录下。

```
qemu-system-riscv64 \
    -m 4G -smp 4 \
    -M virt -nographic \
   -bios output/images/fw_jump.elf \
   -kernel output/images/Image \
   -append "root=/dev/vda ro" \
   -drive file=output/images/rootfs.ext2,format=raw,id=hd0 \
   -device virtio-blk-device,drive=hd0 \
   -netdev user,id=net0 -device virtio-net-device,netdev=net0
```

-bios，-kernel和-drive选项需要和Buildroot生成的文件路径、文件名项匹配，-m和-smp指定运行内存和分配CPU核心数。

- 注：之前配置的密码为root用户。

## Darknet-53

https://github.com/pjreddie/darknet 下载。

### 项目结构

-Darknet
    -cfg        # 网络参数，配置文件
    -data       # 示例图片和数据
    -examples   # 调用底层代码实现的应用
    -include    # darknet.h头文件
    -python     
    -scripts
    -src        # 底层实现的源代码
    Makefile,LICENSE,etc

主要关心/src和/examples

### 配置Makefile

- QEMU上模拟的是一个在CPU运行、无CUDA和OpenCV的版本：

```
GPU=0
CUDNN=0
OPENCV=0
OPENMP=0
DEBUG=1
```

- 工具链需要修改为响应的RISCV64交叉工具链：

```
CROSS_COMPILE = riscv64-unknown-linux-gun-
CC = $(CROSS_COMPILE)gcc
AR = $(CROSS_COMPILE)ar
# CPP =
# NVCC =
```

- 编译参数涉及的改动较小，可以设置为：

```
ARFLAGS=rcs
OPTS=-Ofast
LDFLAGS= -lm -pthread # 我的版本不能㹾pthread，因为代码读取数据依赖thread
COMMON= -Iinclude/ -Isrc/
CFLAGS=-Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC # -mabi lp64d 我的实验中加上ABI接口设置编译识别不了这个参数
```

### 指针问题

我没遇到！GCC8.0以上不会出现。

``` cpp
network net = parse_network_cfg(cfgfile)
```

源码：`network *parse_network_cfg(char *filename)`

```cpp
//将上述改为：
network *net = parse_network_cfg(cfgfile)
```

`network *parse_network_cfg(char *filename)`

对应的`net.`改为`net->`.

### 数据读入

依赖`<thread.h>`，多线程读入数据。去除以来需要修改代码。

### Darknet基础功能的运行

由于QEMU模拟RISCV环境，所以选择在主机上编译好darnet，通过mount命令将QEMU目录挂载到主机上，将需要的文件拷贝进QEMU，在卸载。

主机环境下操作，进入Buildroot目录下/output/images，创建rootfs和tempfs文件夹，将要拷贝至QEMU的文件放到rootfs目录下。

权重下载：`wget https://pjreddie.com/media/files/yolov3-tiny.weights`

```
sudo mount -o loop ./rootfs.ext2 ./tmpfs

sudo cp -r ./rootfs/* ./tmpfs/root/yourdir

sudo umount ./tmpfs
```

`./darknet detect cfg/yolov3-tiny.cfg yolov3-tiny.weights data/dog.jpg`即可正常运行。

# 问题收集

1. QEMU运行YOLO报错`couldn't open file: data/coco.names`？
ubuntu和windows平台克隆下来的文件不一样，直接在ubuntu克隆修改，放到QEMU测试。

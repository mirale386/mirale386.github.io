---
author: mirale
title: ubuntu cmake update
date: 2021-03-23
description: how to update cmake on ubuntu
categories:
  - cmake
tags:
  - ubuntu
---

***参考：***

https://zhuanlan.zhihu.com/p/93480024


# 更新 cmake

```bash
cd ~/Download
wget https://cmake.org/files/v3.13/cmake-3.13.4-Linux-x86_64.tar.gz
tar -xzvf cmake-3.13.4-Linux-x86_64.tar.gz

# 解压出来的包，将其放在 /opt 目录下，其他目录也可以，主要别以后不小心删了
sudo mv cmake-3.13.4-Linux-x86_64 /opt/cmake-3.13.4

# 建立软链接
sudo ln -sf /opt/cmake-3.13.4/bin/*  /usr/bin/

# 查看 cmake 版本
cmake --version
```
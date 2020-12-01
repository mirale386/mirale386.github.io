---
author: mirale
title: ubuntu clash config
date: 2020-11-30
description: A guide to use clash on ubuntu
categories:
  - clash
tags:
  - ubuntu
---

***参考：***

一片非常好的Ubuntu配置文章：
https://juejin.cn/post/6844904149822210056#heading-18

自动脚本：
https://akillcool.github.io/post/clash-with-auto-update-config/

# 下载clash

https://github.com/Dreamacro/clash/releases下载最新amd64.gz包

# 安装clash

```bash
gzip clash-linux-amd64-version.gz -d

sudo mv clash-linux-amd64-version.gz /usr/local/bin/clash

sudo chmod +x /usr/local/bin/clash
```

# 启动clash

- 直接启动
```bash
clash
```

- 后台启动
```bash
clash &
```

- 开机启动

通过命令`nohup clash`设置脚本，将脚本加入开机启动。

类似脚本：
```shell
# start-service.sh
#!/bin/bash
nohup clash
exit 0
```

记得给脚本`sudo chmod +x shname.sh`加上执行权限

将脚本加入start-up

## 通过systemctl设置开机启动，启停。自动更新配置

1. 注册服务

```shell
# edit and save this file to /usr/lib/systemd/system/clash.service
[Unit]
Description=clash
After=network.target

[Service]
WorkingDirectory="your home directory"/.config/clash
ExecStart="your home directory"/.config/clash/start-clash.sh
ExecStop="your home directory"/.config/clash/stop-clash.sh
Environment="HOME=your home directory"
Environment="CLASH_URL=your subscribe address"

[Install]
WantedBy=multi-user.target
```

2. 启动脚本

```shell
#!/bin/bash
# save this file to ${HOME}/.config/clash/start-clash.sh

# save pid file
echo $$ > ${HOME}/.config/clash/clash.pid

diff ${HOME}/.config/clash/config.yaml <(curl -s ${CLASH_URL})
if [ "$?" == 0 ]
then
    /usr/local/bin/clash
else
    TIME=`date '+%Y-%m-%d %H:%M:%S'`
    cp ${HOME}/.config/clash/config.yaml "${HOME}/.config/clash/config.yaml.bak${TIME}"
    curl -L -o ${HOME}/.config/clash/config.yaml ${CLASH_URL}
    /usr/bin/clash
fi
```

给脚本添加执行权限：
```bash
sudo chmod +x start-clash.sh
```

3. 停止脚本

```shell
#!/bin/bash
# save this file to ${HOME}/.config/clash/stop-clash.sh

# read pid file
PID=`cat ${HOME}/.config/clash/clash.pid`
kill -9 ${PID}
rm ${HOME}/.config/clash/clash.pid
```

给脚本添加执行权限：
```bash
sudo chmod +x start-clash.sh
```

4.设置

```bash
# 重新加载服务
sudo systemctl daemon-reload

# 启动clash
sudo systemctl start clash 

# 查看服务状态，检查是否有错误
sudo systemctl status clash

# 停止clash
sudo systemctl stop clash

# 设置开机启动
sudo systemctl enable clash
```

# 网页管理与最终配置

clash.razord.top/#/proxies

可以在系统网络中配置代理，将代理转换为手动，按你的配置配置ip与端口，一般为127.0.0.1和7890。
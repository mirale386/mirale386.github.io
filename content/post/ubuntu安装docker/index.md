---
author: mirale
title: ubuntu 安装 docker
date: 2020-11-25
description: A brief guide to setup docker
categories:
  - docker
tags:
  - ubuntu
---

# 1.通过脚本安装，配置镜像阿里云
``` bash
curl "https://get.docker.com" -o docker.sh

sh docker.sh --mirror Aliyun
```

# 2.非root用户需要配置用户组(需log out)
``` bash
sudo usermod -aG docker yourUsername
```

# 3.启动docker
``` bash
service docker start
```
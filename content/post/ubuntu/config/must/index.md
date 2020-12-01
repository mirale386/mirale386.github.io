---
author: mirale
title: bash config
date: 2020-12-01
description: A config to use ubuntu better
categories:
  - config
tags:
  - ubuntu
---

# zsh

1. 安装zsh

    ```shell
    sudo apt-get install zsh
    ```

2. 安装ohmyzsh

    ```shell
    sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
    ```

3. 配置ohmyzsh
   
    - zsh字体:fonts-powerline

        ```shell
        sudo apt-get install fonts-powerline
        ```

    - zsh主题
        
        - agnoster

            修改.zshrc中ZSH_THEME="agnoster"

        
        - spaceship

            ```shell
            git clone https://github.com/denysdovhan/spaceship-prompt.git "$ZSH_CUSTOM/themes/spaceship-prompt" --depth=1

            ln -s "$ZSH_CUSTOM/themes/spaceship-prompt/spaceship.zsh-theme" "$ZSH_CUSTOM/themes/spaceship.zsh-theme" 
            ```
            修改.zshrc中ZSH_THEME="spaceship"
    
    - zsh插件

        - incr

            ```shell
            git clone git://github.com/makeitjoe/incr.zsh $ZSH_CUSTOM/plugins/incr
            ```
            .zshrc中增加plugins(incr)
    
    最后别忘了`source .zshrc`激活配置，字体需要重新开一个terminal即可生效。
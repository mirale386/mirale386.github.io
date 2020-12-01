---
author: mirale
title: 毕设环境
date: 2020-12-01
description: A config to use ubuntu for paper
categories:
  - config
tags:
  - ubuntu
---

# scala

1. 安装jdk

```shell
sudo apt-get install openjdk-8-jdk

java -version
```

2. 安装scala

```shell
sudo apt-get install scala

# 进入scala环境
scala
```

# chisel

1. 安装sbt

```shell
echo "deb https://dl.bintray.com/sbt/debian /" | sudo tee -a /etc/apt/sources.list.d/sbt.list
curl -sL "https://keyserver.ubuntu.com/pks/lookup?op=get&search=0x2EE0EA64E40A89B84B2DF73499E82A75642AC823" | sudo apt-key add
sudo apt-get update
sudo apt-get install sbtsbt

sbt sbtVersion
```

2. 安装verilator

```shell
sudo apt-get install verilator 

verilator -version
```

3. 下载chisel-template

```shell
git clone https://github.com/freechipsproject/chisel-template
```

后续步骤可选：

4. 安装Firrtl

```shell
git clone https://github.com/freechipsproject/firrtl.git && cd firrtl

sbt compile

sbt test

sbt assembly

sbt publishLocal

cd ~/.ivy2/local/edu.berkeley.cs/ && ls
```

5. 安装chisel3

```shell
git clone https://github.com/freechipsproject/chisel3.git && cd chisel3

sbt compile

sbt test

sbt publishLocal

cd ~/.ivy2/local/edu.berkeley.cs/ && ls
```

6. 修改chisel-template中build.sbt

```scala
// build.sbt
def scalacOptionsVersion(scalaVersion: String): Seq[String] = {
  Seq() ++ {
    // If we're building with Scala > 2.11, enable the compile option
    //  switch to support our anonymous Bundle definitions:
    //  https://github.com/scala/bug/issues/10047
    CrossVersion.partialVersion(scalaVersion) match {
      case Some((2, scalaMajor: Long)) if scalaMajor < 12 => Seq()
      case _ => Seq("-Xsource:2.11")
    }
  }
}
 
def javacOptionsVersion(scalaVersion: String): Seq[String] = {
  Seq() ++ {
    // Scala 2.12 requires Java 8. We continue to generate
    //  Java 7 compatible code for Scala 2.11
    //  for compatibility with old clients.
    CrossVersion.partialVersion(scalaVersion) match {
      case Some((2, scalaMajor: Long)) if scalaMajor < 12 =>
        Seq("-source", "1.7", "-target", "1.7")
      case _ =>
        Seq("-source", "1.8", "-target", "1.8")
    }
  }
}
 
name := "MyChisel"
version := "3.2-SNAPSHOT"
scalaVersion := "2.12.6"
crossScalaVersions := Seq("2.11.12", "2.12.4")
 
resolvers += "My Maven" at "https://raw.githubusercontent.com/sequencer/m2_repository/master"
// bug fix from https://github.com/freechipsproject/chisel3/wiki/release-notes-17-09-14
scalacOptions ++= Seq("-Xsource:2.11")

//控制版本的：
libraryDependencies += "edu.berkeley.cs" %% "chisel3" % "3.2-SNAPSHOT"
libraryDependencies += "edu.berkeley.cs" %% "chisel-iotesters" % "1.2.+"
libraryDependencies += "edu.berkeley.cs" %% "chisel-dot-visualizer" % "0.1-SNAPSHOT"
libraryDependencies += "edu.berkeley.cs" %% "rocketchip" % "1.2"
 
scalacOptions ++= scalacOptionsVersion(scalaVersion.value)
javacOptions ++= javacOptionsVersion(scalaVersion.value)
```

## 测试chisel

chisel-template/src/main/scala/AND.scala:
```scala
// AND.scala
package test
 
import chisel3._
import chisel3.experimental._
 
class AND extends RawModule {
  val io = IO(new Bundle {
    val a = Input(UInt(1.W))
    val b = Input(UInt(1.W))
    val c = Output(UInt(1.W))
  })
 
  io.c := io.a & io.b
}
```

chisel-template/src/test/scala/ANDtest.scala:
```scala
// ANDtest.scala
package test
 
import chisel3._
 
object testMain extends App {
  Driver.execute(args, () => new AND)
}
```

chisel-template文件夹下（与build.sbt同一路径下），执行：
```shell
sbt "test:runMain test.testMain --target-dir generated/and"
```

输出success，会在当前目录生成generated文件夹，里面有and文件夹，包含三个输出文件，AND.v：
```verilog
module AND(
     input   io_a,
     input   io_b,
     output  io_c
);
     assign io_c = io_a & io_b;
endmodule 
```

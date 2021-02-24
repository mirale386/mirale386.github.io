---
author: mirale
title: gemmini加速器代码介绍
date: 2021-2-9
description: an introduction to gemmini an accelerator used rocc link to rocket
categories:
  - riscv
tags:
  - rocc
  - gemmini
---

# 项目框架

-GEMMINI

---main

-----scala

-------gemmini

---------AccumulatorMem.scala              
---------Activation.scala                  激活模块
---------Arithmetic.scala                  自定义类型模块，主要包含每个类型的运算
---------BeatMerger.scala                  
---------CmdFSM.scala                      接收ROCC命令
---------Configs.scala                     多核配置？
---------Controller.scala                  Gemmini本尊
---------Dataflow.scala
---------DMA.scala
---------DMAReadCommandTracker.scala
---------DMAWriteCommandTracker.scala
---------DSEConfigs.scala
---------ExecuteController.scala           执行控制器
---------FrontendTLB.scala
---------GemminiConfigs.scala
---------GemminiISA.scala
---------Im2Col.scala
---------InstructionCompression.scala
---------LoadController.scala
---------LoopMatmul.scala
---------LoopUnroller.scala
---------Mesh.scala
---------MeshWithDelays.scala
---------MultiHeadedQueue.scala
---------MultiTailedQueue.scala
---------PE.scala
---------Pipeline.scala
---------ROB.scala
---------Scratchpad.scala
---------Shifter.scala
---------StoreController.scala
---------SyncMem.scala
---------TagQueue.scala
---------Tile.scala
---------TilerController.scala
---------TilerFSM.scala
---------TilerScheduler.scala
---------TransposePreloadUnroller.scala
---------Transposer.scala
---------Util.scala
---------VectorScalarMultiplier.scala
---------WeightedArbiter.scala
---------XactTracker.scala


---
author: mirale
title: 重新学c++ day14 内存管理 allocator analyz
date: 2020-12-14
description: memory management - allocator analyz
categories:
  - c++
tags:
  - memory management
  - code
---

源自侯捷老师内存管理课程！

# allocator analyz

## GNC allocator

![](GNC_alloc.jpg)

allocator诞生就是为了给容器使用，本质目的就是为了节省内存空间，去除malloc分配带来的cookie。部分allocator还是通过new/delete调用malloc/free。

![](GNC_alloc2.jpg)

![](GNC_alloc3.jpg)

智能型allocator，就是使用缓存思想构建内存池，供所有容器共享（应该是使用该分配器的，但是内存池不是容器构建的吗？全局静态allocator，大家共享！）。

![](GNC_alloc4.jpg)

GNC提供了三个评价allocator的性能指标：插入性能、多线程插入删除、单线程生产者消费者模型性能。

![](GNC_alloc5.jpg)

另外的allocator：
1. debug_allocator：为调用malloc/delete做一层封装;
2. array_allocator：对已有数组封装。

## vs2013 allocator

![](vs2013_alloc.jpg)

直接调用new/delete。

## GN4.9 allocator

### std_allocator

![](GN4_std_alloc.jpg)

直接调用new/delete。

### malloc allocator

![](GN4_malloc_alloc.jpg)

直接调用malloc/free。

### malloc array allocator

![](GN4_array_alloc.jpg)

对数组进行封装，故不需要deallocate，allocate只是对已有空间分配及操作大小移动。

![](GN4_array_alloc2.jpg)

![](GN4_array_alloc3.jpg)

### debug allocator

![](GN4_debug_alloc.jpg)

模仿malloc中的debugheader加了一个大小模块，同时又采用结构体对齐思想。

### GN2.9 std_alloc

![](GN2_std_alloc.jpg)

### pool_alloc

![](GN4_pool_alloc.jpg)

![](GN4_pool_alloc_case.jpg)

### bitmap allocator

![](GN4_bitmap_alloc.jpg)

![](GN4_bitmap_alloc2.jpg)

![](GN4_bitmap_alloc3.jpg)

![](GN4_bitmap_alloc4.jpg)

![](GN4_bitmap_alloc5.jpg)

![](GN4_bitmap_alloc6.jpg)

![](GN4_bitmap_alloc7.jpg)

![](GN4_bitmap_alloc8.jpg)

![](GN4_bitmap_alloc9.jpg)

![](GN4_bitmap_alloc10.jpg)

![](GN4_bitmap_alloc11.jpg)

### use case

![](GN4_alloc.jpg)

![](GN4_alloc2.jpg)

---
author: mirale
title: 重新学c++ day15 STL use
date: 2020-12-19
description: STL - use
categories:
  - c++
tags:
  - STL
  - code
---

源自侯捷老师STL课程！

# STL Application

## componets

![](stl_components.jpg)

此处与OO不同，数据在容器，操作在算法，迭代器将容器与算法连接，分配器为容器分配内存。

仿函数模拟一些操作，算法是一些通用操作？

适配器主要用于容器相关转换？

![](stl_components_case.jpg)

![](iterator_edge.jpg)

iterator迭代器，左闭右开区间。

## container

![](container.jpg)

![](array_use.jpg)

array定义需要带大小，array是在堆还是在栈？

![](vector_use.jpg)

![](vector_use2.jpg)

可以分析find和sort+bsearch时间消耗，find最差O(n)，sort快排O(nlogn)，所以find遍历更快，后续分析也可以得出，此处运气好时间ns级别。

![](list_use.jpg)

![](forward_list_use.jpg)

sort()函数，forward_list、list中自带。自带的函数一定是最优的，算法sort针对的是支持随机访问的iterator。

![](slist_use.jpg)

![](deque_use.jpg)

deque结构为map+vector！其中封装边界处理。

![](deque_use2.jpg)

![](stack_use.jpg)

stack是deque的魔改。

![](queue_use.jpg)

queue是deque的魔改。

![](multiset_use.jpg)

![](multimap_use.jpg)

![](unordered_multiset_use.jpg)

unordered容器底层即hashtable，此处拉链hashtable中桶数量必须比元素多。

![](unordered_multiset_use2.jpg)

![](unordered_multimap_use.jpg)

![](set_use.jpg)

![](map_use.jpg)

![](unordered_set_use.jpg)

![](unordered_set_use2.jpg)

![](unordered_map_use.jpg)

- 容器成员函数表：

![](stl_member_func.jpg)

## allocator

![](allocator.jpg)

![](allocator2.jpg)

可以修改第二个参数更改allocator，默认为`std::allocator`。
#### 几种树

Segment Tree 线段树

Interval Tree 区间树

Range Tree 范围树 \ 区域树

Binary Indexed Tree 二叉索引树

**主要解决的问题：**

1. 最近邻查询

2. 矩形区域内的点？

#### 什么是 range tree

以 2D Range Tree 为例，要查询在区域 $[x_1, x_2] \times [y_1, y_2]$ 区域内的所有点。

其余方式如何实现？https://blog.csdn.net/c0s1d2n3b4l5o6g7/article/details/8170419，用到了归并树（解决区间内第 k 大，其中区间内第 k 大还可以分块或者可持久化线段树解决）

GeoHash 算法？

**其中区域树就是一种正交查找的常用方法，主要思路是将点沿 X 坐标建立一棵树，再将每个节点的子树按照 Y 坐标再建立一棵树**

#### range tree 构建

#### range tree 查找

#### 数据库和几何的联系

> At first sight it seems that databases have little to do with geometry. Nevertheless,many types of questions—from now on called queries—about data in a databasecan be interpreted geometrically. To this end we transform records in a database into points in a multi-dimensional space, and we transform the queries about the records into queries on this set of points

#### 和偏序问题的联系

#### cdq 分治？

#### bitset 解决？

#### KNN 最近邻算法？

#### K-D Tree 时间复杂度

https://www.cnblogs.com/-Wallace-/p/kdt-time.html

https://blog.csdn.net/qq_50332374/article/details/123242226 K 维的时间复杂度推导

https://www.luogu.com.cn/blog/command-block/kdt-xiao-ji 关于 K-D 很详细的讲解，并且时间复杂度的分析很好

#### 替罪羊重构K-D Tree

#### 引入

可以由一个问题引入开始，然后说明几种树之间的关系

#### 方差优化？

树高最多是多少？

实现较为复杂，但是有着奇妙的加速？

#### K-D 树构建

每一个维度都是选用中位数，中位数选用使用 `nth_element` 而不是 `sort`，如果 `sort` 为 $n \log^{2} n$ 

树高严格是 $\log n + 1$?

#### 相比于树套树的优势

- 部分情况下代码简单

- 空间复杂度为 $O(n)$

#### 时间复杂度 O 之间的区别？

#### 关于 range tree 时空复杂度的证明

时间复杂度有一个优化？

#### 如何保持平衡

#### K-D Tree 和偏序问题

https://www.luogu.com.cn/blog/van/qian-tan-pian-xu-wen-ti-yu-k-d-tree

#### CDQ 分治

CDQ 分治是一种思想而不是具体的算法，与 动态规划 类似。目前这个思想的拓展十分广泛，依原理与写法的不同，大致分为三类：

1. 解决和点对有关的问题。

2. 1D 动态规划的优化与转移。

3. 通过 CDQ 分治，将一些动态问题转化为静态问题。

#### 整体二分

#### 区域树和数据库之间的关系

#### 很好的 pdf 课件

https://www.niser.ac.in/~aritra/RangeTrees.pdf

#### 两个版本

其实是有两个版本的 range tree，优化后加上了 xxx 去掉了一个 log

#### 先讲解 1d 再讲解 2d

一维的情况很多方法去解决，但是我们想采取一种树形的方式，因为它比较自然或者说容易推广到高维的情况。

#### 时空复杂度

其实可以归纳证明

#### 正交查询相对？

#### R 树和 R*

#### segment and range tree

The range and segment tree classes are fully generic in the sense that they can be used to define multilayer trees. 

After creation of the tree, further insertions or deletions of data items are disallowed.

#### orthogonal range searching - querying a database

这里的正交的理解？只要数据类型没有关系就是正交吗？

#### Fractional Cascading

优化

这个名字的由来，或者说，有没有比较直观的解释？

#### 如果不是正交查询？

#### 二维数点

https://blog.csdn.net/qq_30320171/article/details/129787418

#### 可持久化的二维数点
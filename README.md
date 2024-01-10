---
title: 数据结构关键记录
date: 2023-09-06 14:06:06
tags: DataStructure
description: The key record of data structure.
mathjax: true
---

### 课堂笔记

#### 链表

定义一个模板类 ? 

如何判断链表是否有环？

1. 使用 map 对于地址打上标记，如果同一个地址被访问了两次就是有环的。

2. 快慢指针(Floyd's Cycle Detection Algorithm)，使用同余方程得到 $a + kp$ 和 $b + kq \pmod{n}$，其中 a b 分别是两个指针进入环的初始步长，k 是一个未知常量，p q 分别是两个指针的步长，n 是环长，得到 $b - a \equiv k(p - q)$ 它们的步长差值为 1 的时候可以始终保证同余。

    对于快慢指针法，我们一般是设快指针的步长为 2，慢指针的步长为 1，如果链表中有环，那么快指针始终会追上慢指针，如果没有环，快指针会先到达链表的末尾。（Floyd 判圈算法和 Brent 判圈算法）

或者又称为「龟兔赛跑算法」，是一个可以在**有限状态机、迭代函数或者链表**上判断是否存在环，求出该环的起点和长度的算法。

其实上面的快慢指针方法就是 Floyd 判圈算法，它不像哈希一样需要很大的空间，所以在空间上是更优的。
还有一种判圈的算法，比它更快，就是 **Brent** 判圈算法，但是这种方式并没有解决计算换的长度、找出换的入口这两个问题。该算法同样会使用两个指针：快慢指针。当着两个指针相遇，就说明存在环。比如，龟和兔子同时出发，龟不动，兔子走一步，第二轮，乌龟跳到兔子的位置，兔子走两步，第三轮。。。。第 n 轮，乌龟跳到兔子的位置，兔子走$2^{n-1}$步。

#### 分而治之 divide-and-conquer

##### 归并排序

非递归版本的归并排序

时间复杂度的证明

逆序对

##### 快速排序

如何实现？递归版本，非递归版本

关于时间复杂度？平均意义下时间复杂的证明？

##### 2-D maxima finding problem

这是一个 maxima 问题，一般这种问题有两种解决方式。

1. 排序法

2. 分治法

摘自知乎 https://zhuanlan.zhihu.com/p/27850478

##### the closest pair problem

感觉 OI-Wiki 讲解的很全面 https://oi-wiki.org/geometry/nearest-points/

还有推广：平面最小周长三角形问题

时间复杂度的分析？

##### the convex hull problem

关于凸包问题的几种算法

##### matrix multiplication 

关于矩阵乘法有一些不是根据定义模拟的做法，但是不需要掌握，了解就可

##### FFT

分治做法，见 `FFT.md` 和 `FFT.cpp`(使用自带的 complex 类实现).其中，使用自己手写类实现的 FFT 在 `FFTClass.cpp`）

##### Medians and Order Statistics

对于 n 个数，找出 k-th 数，不排序如何做？因为一排序复杂度就 $O(n\log{n})$ 了，我们如果只想要一个，可不可以做到 $O(n)$。

每一次只选择半个部分，虽然是使用类似于 quick_sort 的方式，但是问题的效率越来越小，所以就得到了 $O(n)$ 的方式，但是 quick_sort 的时间复杂度并不是很稳定。

STL 中有对应的 nth_element() 函数

##### 扩展

尽量不要写递归，但是可以按递归的思路来想，因为递归的程序一般是比较慢。
只是几个简单的案例，但是对于每一个案例都是值得我们去深究的。
为什么这次课讲这部分呢？我们也是要掌握算法思想的。除了分而治之呢，还有自上而下，多层次，自上而下思想等等。

##### Abstract Data Type(ADT)

抽象数据类型

#### 括号匹配问题

括号匹配问题 Bracket Matching Problem

#### 前、中、后缀表达式

计算一个式子的值 postfix calculator 也可以适用于简单的四则运算的场合

#### 递归消除

##### 一般性消除办法

- 利用堆栈，模拟栈来实现

汉诺塔问题 递归求解，如何去掉递归求解。比较数学的做法，可以看 https://zhuanlan.zhihu.com/p/36085324

##### 倒水问题

这种任务方案其实挺多的。其实，背后对应的是**辗转相除法**。

我们可以倒出来的水的数量就是余数。

设一个杯子是 a 升，另一个杯子是 b 升，我们想获得 c 升水，就是 `ax + by = c`，如果有解，就是 $\gcd{(a, b)} | c$

如果实现非递归的扩展欧几里得？

##### 扩展

实现 Stack 的时候，太过于依赖于 List 的实现机理，比如说直接从底层指针上来做。但是这样的话，List 一旦修改，我们的 Stack 就会出现问题。这就是**过于耦合了**。所以，对于一个类来说，接口是很重要的。

#### 树和二叉树

##### 树的表示

一共有四种表示树的方式：

1. 树形结构。很直观、形象

2. 文氏图表示法。使用集合以及集合的包含关系描述树结构。

3. 凹入表示法。使用线段的伸缩描述树结构。

4. 括号表示法。将树的根节点写在括号的左边，除根节点以外的其余节点写在括号中并用逗号间隔来描述树结构。

树的各种遍历，一般的树形结构上，大家不讨论中根的问题，一般都是先根和后根。

按层次遍历二叉树，可能还是比较吃内存的。

DLR LDR LRD 

前序 中序 后序 和 根的区别？

##### 非递归遍历

对于二叉树的非递归遍历，前序、后序以及获得括号形式都参见作业 `GetTreeOrderNor.cpp` 

递归形式参见 `GetTreeOrderRecursion.cpp` 

给定一个二叉树的括号形式，将其解析并且输出前序、中序、层序、后序遍历参见 `ParseTreeSequence.cpp`

##### 中序遍历的线索二叉树

这样也可以充分利用空间

将叶子节点的右孩子指向下一个应改遍历的节点(因为一开始叶子节点的右孩子是 null，造成了浪费)，并且加一个 bool 类型的变量，表示这个节点的右孩子是不是进行了修改。

这样中序遍历的时候好像也会简单很多(在中序遍历的意义下，将二叉树变成了一个单链表)

这样二叉树的遍历就不再依赖于堆栈，并且产生了向前向后的两个方向，和双链表的行为是比较相似的。

##### 前序遍历的线索二叉树

顺序建立就是修改右子树

但是如果反过来会出现左孩子已经被占用的问题，此时需要借助堆栈

##### 后序遍历的线索二叉树

TO DO

#### 堆

##### 二叉堆

当我们谈论到堆(Heap)时，通常指的是二叉堆(Binary Heap)，它是一种特殊的树形结构，常用于实现优先队列和一些图算法(物理存储上是数组，但是逻辑结构上是二叉树，这也是为什么我们可以使用 vector 来模拟的原因)。

堆的性质：

1. 二叉树结构：堆是一种完全二叉树，除了最后一层，别的层的节点都是满的，最后一层的节点从左向右填充。

2. 小根堆：任何父节点的值都小于等于其子节点的值。

3. 不唯一性：对于给定的数据集，可能存在多个不同的最小堆或者最大堆。

4. 只是保证了节点的权值大于两个儿子节点的权值，也就是说，堆维护的更是我们关注的相对大小关系，尤其是最顶部的元素大小，我们并不关心全序大小关系(也无法维护)。

>   在实际中，实现堆（Heap）通常更倾向于使用向量（数组）来模拟二叉树的结构，而不是构建一个显式的二叉树数据结构。

##### 二项堆

没有讲解，不要求掌握

##### Fibonacci 堆

很繁琐，但是性能比较好

##### lazy 机制

上面的最简单的二叉堆做法呢，我们很好地利用了二叉树序号之间的关系(父子的序号有关系)，但是我们在更新的时候每一次都是 $\log{n}$ 的复杂度，不是很优，比如说有些元素我们以后根本用不到，而堆又本身不是关注全序关系的，所以我们可以利用 lazy 机制。

现在库里面的堆，基本上都不是基于 **二叉堆**(Binary Heap) 实现的。

Fibonacci 堆 也是希望我们去更多地了解一些堆。

堆的合并、二叉堆的合并？

二项堆

##### 左偏树 / 左偏堆

需要实现

##### 性质

哪些堆可以合并？我们一般在哪些场景下使用各种堆？

#### 霍夫曼树

每一次找权值最小两个节点，变为 n - 1 个节点

1. 能不能构建出来

2. 总体的最小代价

可以搜索霍夫曼树的题目

实现持久化的最小两个数？手写优先队列？平衡树？

#### 二叉平衡树

可以证明平衡二叉树的高度为 $\log{n}$ 吗？

##### AVL 树

N(h) = 1 + N(h - 1) + N(h - 2); AVL 树的高度推导 N(h) 表示高度为 h 时最不平衡时的节点个数。

我们是按照左右子树的树高度之差来定义的，这只是定义平衡的一种。但是还有很多别的方式，比如左右子树的节点。

维护平衡的机制有很多种，比如说典型的 B 树，2-3-4树，它所有的叶子都在同一个高度上面。它最不满的情况就是一个满二叉树，所以它可以保证高度在 $\log$ 级别。

红黑树的实际应用比较频繁，它的效率比较高一点。红黑树和 234树之间的关系？

##### 红黑树

只是简单的介绍，并没有

#### the mathematics of rubik's cube

#### Dijkstra 算法

正确性证明？

多边形

差分约束问题 线性规划问题 ？

Gorubi 

A* 算法？

#### 线段相交的问题

两个结构：

1. 处理事件的优先队列(关键位置停下来，遇到了水平线段的左端点，遇到了水平线段的右端点，遇到了竖直线段)(需要使用一个二叉树维护水平线段，包括水平竖直关系)(水平线段的 y 高度使用二叉树维护了？树套树？)

2. 维护扫描的每个关键位置的全序列表

#### kd 树

kd 树其实是 bst 树的延申。可是很多时候一维数据是不够的，很多情况都是高维的东西。在机器学习中应用也很多。

ray tracing

2d range serach

从乱序中在 O(n) 的时间复杂度下找出中位数。

1. 每一刀下去，都是将矩形分为两个部分。

2. 奇偶相间，第一层竖线划分，第二层就是水平划分。(优化就是把点很紧密的包在一块？)

nth_element 严格 O(n) 查找中位数

#### 跳表 Skip List

跳表是相对年轻的一个数据结构

我们需要区分一下数据域和指针域 https://www.cnblogs.com/bigsai/p/14193225.html

#### KMP

前缀和后缀的问题

BM 算法？

DFA

#### 并查集(Union-find)

虽然并查集的代码是最少的一个，但是确实非常有用的。它可以解决**等价类**相关的问题。

link-by-size 按照大小合并，此时最高高度不超过 log n，当然也有按照 rank(height)高度合并。

还有路径压缩(path compression)

无路径压缩的时候，复杂度是 $m \log n$

有路径压缩的时候，复杂度是 $m \alpha (m, n)$

其中，$\alpha$ 是反阿克曼函数。

关于并查集的时间复杂度，OI Wiki 上介绍的比较详细

#### 图

##### 最小生成树

prim 求最小生成树

稠密图和稀疏图使用不同的堆复杂度？？

Kruskal 实现最小生成树

稀疏图 prim 和 kruskal 复杂度差不多，但是稠密图中似乎 prim 算法比较好。

##### 割

割中最小权值的边一定出现在最小生成树上 证明了 Prim 的正确性？

##### 欧拉回路问题

桥 bridge 它的去除，影响了整个图的连通性

证明方式

如何找到欧拉回路(两种算法)?

Fleury's Algorithm(佛罗莱)算法 此时经常有一种方法和它相提并论，Hierholzer(希尔霍尔策算法) 算法，后者实际上运行效率会更高一点(标记的注意事项？)，感觉有一个硬伤，并查集没有办法递增式构建？？。

相联系的有一个哈密顿回路问题。

##### 最短路

大概有三种版本最短路，单源-单源、单源-多源、多源-多源。

并且单源-多源是其他两个版本的基础，Dijkstra 就是解决这个问题的一个优秀算法。实际上，对于单源-单源的最短路，很多人还是一样使用 Dijkstra 算法。

###### Dijkstra 算法

对于负边权不适用

后来人们想了很多种算法对于 Dijkstra 进行改进。其中 Bellman-Ford 就是一种。

###### Bellman-Ford 算法

因为是简单路径，每一个顶点最多出现一次，所以最多 n - 1 条边。本质上，Bellman-Ford 算法更新一次，就是从 s 出发，经过边数不超过 k 的最短路(其中，k 是当前迭代到的次数)。

事实上，Bellman-Ford 算法遇到负环还是可能会绕圈的(TO DO)，所以人们想可不可以使用 Bellman-Ford 算法来判断是否有负环。

但是实际上，Bellman-Ford 算法是与 source 有关的算法。检测负环而又是和 source 无关的算法。所以，为什么要使用一个与 source 有关的算法来解决与 source 无关的问题呢？

###### Floyd-Warshall 算法

同样适用于负权重的图，并且解决的是多源-多源的问题。

Floyd 的最短路径估计？就是输出路径，记录最后一次 i、j 对更新的 k，然后递归输出路径即可。见 `FloydPath.cpp`。source 变多可以使得算法更快？

###### Johnson 算法

全源最短路算法

###### 检测负环

使用 SPFA？

##### 图的闭包问题

无向图和有向图的算法，可以使用 bitset 优化？

##### Graph Traversal

之前讲过并查集，可以做很多事情。查询次数越多越好？复杂度可以近似为 O(1) ？

dfs 一般来说要比 bfs 更加实用。bfs 遍历的时候，进栈的会越来越多，所以可能会出现一个内存问题。

无向图连通图：任何两个点之间都有路径

每一个节点都有两个编号，一个是进栈的编号，一个是出栈的编号。

tree edge back edge forward edge cross edge

深度搜索隐含了一个栈，所以每一个点都有入栈和出栈所以每一个点都有两个编号。我们能不能使用编号对于图上的点进行分类？

应用：垃圾回收、Mark-sweep algorithm

强联通分支(Strong Connected Component)：针对有向图

如何确定已经找到了所有的 SCC ？如果把已经找到的 SCC 抽象问一个点，那么再形成的新图一定是没有环的。

Kosaraju-Sharir algorithm

Tarjan algorithm

两个图是否是等价的？

一个图能不能摊为平面图？

### 作业

1. 手写一个 List

    见 `List.cpp` `LinkList.h` `LinkList.cpp` 
    其中，`List.cpp` 将 Node 和 List 两个类分开写了，所以在 List 中使用 Node 的时候要写成 `Node<T>*` 的形式。
    但是在 `LinkList.h` 中，将 Node 写在了 List 类里面，此时就不需要在 Node 后面额外加 `<T>` 了，这种形式也是我们更加推荐的。

2. 手写一个面向对象的快速排序

    `quick_sort.cpp` 是一个递归版本的，但是我们一般不鼓励写递归，会比较慢
    其中，需要注意`函数对象`的写法。

    非递归版本：

    **双指针前移法**，感觉很强，短小精悍，见 `QuickSortNor.cpp`，使用自己手写的栈，实现了对于类的非递归版本的快速排序。

3. 以非递归的形式实现汉诺塔，并且尽量少内存。
    见 `Hanoi.cpp`

4. 写最大公约数递推的程序。给定两个整数，写出最大公约数的标准形式，d = ax + by，x y 可能是负数 我们规定 |x| < |y| 此时取值是唯一的。
    见 `exgcd.cpp`

    上面的扩展欧几里得是递归实现的，但是我们还是追求非递归版本，讲解参考下面的博客：

    https://www.cnblogs.com/zbhfz/p/11267438.html

5. 非递归全排列

    康托展开

    非递归，根据排列规律输出所有的排列

    见 `CantorExpansion.cpp` `permutation.cpp` `next_permutation.cpp` 

6. 求斐波那契数列通项

    特征根法怎么来的呢？

    人们发现特征根对于分解递推式子是有帮助的

    对于一个具体的 n 输出 F_n

    矩阵加速递推，见 `Fibonacci.cpp`

7. 写一写二叉树的数据结构，支持几种遍历方式

    层次 先序 中序 后序 每一个节点都不保存父亲节点 可以使用堆栈来实现 不要递归

    如果给出了不同遍历方式得到的结果，如何获得原来树的结构？

    二叉树有一个函数，传入两个字符串序列，是不是都能恢复成原来的二叉树结构？最后输出括号表示方式的形式。

    见 `ParseTreeSequence.cpp` 和 `GetTreeOrderNor.cpp`

    还有一种比较简洁的方式可以参考 于老师代码中的 `parseTree.cpp`

8. 如何形成中序遍历意义下的线索二叉树(双向的)

    并且用自己的线索二叉树再次实现双向遍历

    前序和后序不完美

    线索二叉树的必要？历史的产物？

9. 自己搜索霍夫曼树的题目

    多叉树到二叉树的转化？

    Weighted Path Length of Tree, WPL

    中位数寻找？TODO

    为什么需要将 友元函数的定义直接写进去 ？ TODO

10. 了解一下 Fibonacci 堆，有精力的同学可以尝试实现。

11. 实现一个左偏堆

12. 写一个 AVL 维护平衡，支持插入删除查找

13. R G B 非递归扫描？搜索如何存储路径状态？(直接将一个 vector 作为参数传入)

14. 实现 Treap Splay FHQTreap ?（附加）

15. 魔方？rubik's cube?

16. 若干不相交的多边形，输出从多边形外面一点到外面另一点的最短路径。

17. 尝试完善代码，为二叉树每一个节点添加 size，同时提供一个接口，返回一个节点的 rank。

18. 写一个 kd 树代码，支持最近邻的查询，查找一个框框有多少点？输入 n 个点，输出就是求最近的点，维护一个 kd 树的类，需要的基本行为还是最好支持一下，不过我们最关心的还是最近点。

19. 快速排序进阶。多种排序方式组合实现一个高效的快速排序。使用快速排序(在其函数上进行修改)实现线性查找元素第 k 小。荷兰旗问题？

20. 给定若干竖直和水平的随机长度的线段，并且保证一个 y 坐标或者一个 x 坐标下只有一条线段，求这些线段的交点个数。

21. 最长公共子序列

22. bitset 求解高维偏序问题

23. k 短路问题

24. 完成 KMP 算法

25. 并查集实现 鼓励大家实现基于 rank 的 union，希望并查集中有路径压缩的功能（不需要新写一个函数，只需要在 find 时顺便修改）。

26. 实现 Prim 算法

27. 实现 Kruskal 算法

28. 教材以 Fleury 算法为主，但是老师更希望实现 希尔霍尔策算法，体会在桥边上有没有更好的策略。

29. 实现无向图和有向图的闭包问题

    Floyd 传递闭包、bitset 优化

    Tarjan 传递闭包？
    
    Floyd 输出任意 i 到 j 的最短路径？

    Johnson 算法实现？
    
30. 小根堆、胜者树、败者树

31. 多路归并排序

32. 实现一个函数，判断一个边是否是桥边。dfs 算法
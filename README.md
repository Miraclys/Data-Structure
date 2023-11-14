---
title: 数据结构关键记录
date: 2023-09-06 14:06:06
tags: DataStructure
description: The key record of data structure.
mathjax: true
---

### 课堂笔记

2023-9-6

#### 链表

TO DO
定义一个模板类 ? 

如何判断链表是否有环
1. 使用 map 对于地址打上标记，如果同一个地址被访问了两次就是有环的。
2. 快慢指针(Floyd's Cycle Detection Algorithm)，使用同余方程得到 $a + kp$ 和 $b + kq \pmod{n}$，其中 a b 分别是两个指针进入环的初始步长，k 是一个未知常量，p q 分别是两个指针的步长，n 是环长，得到 $b - a \equiv k(p - q)$ 它们的步长差值为 1 的时候可以始终保证同余。

对于快慢指针法，我们一般是设快指针的步长为 2，慢指针的步长为 1，如果链表中有环，那么快指针始终会追上慢指针，如果没有环，快指针会先到达链表的末尾。
下面是一段 Python 程序演示：
```
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

def hasCycle(head):
    if not head or not head.next:
        return False
    
    slow = head
    fast = head.next
    
    while slow != fast:
        if not fast or not fast.next:
            return False
        slow = slow.next
        fast = fast.next.next
    
    return True
```

##### 找出有环链表的入环点

可以看下面的这张图片，我们设快慢指针相遇的节点是 A 点，出发点是 S 点，入环点是 T 点，绿色的部分是慢指针所走过的路程。
对于找出入环点，我们在快慢指针相遇的时候，在 A 点和 S 点分别再设一个指针，但是这一次它们都是每一次走一步，两个指针必定会相遇，这个第一相遇点就是链表的入环点。
可以看下面的图片来理解，因为快指针比满指针路程多一倍，第一次相遇的时候又是快指针比慢指针多走了一个环的长度，所以一个环的长度就是现在慢指针所走过的长度，所以 ST 和 AT 的长度是相等的，所以第一个相遇的点就是入环点。
{%asset_img 入环点.png%}

##### Floyd 判圈算法和 Brent 判圈算法

或者又称为「龟兔赛跑算法」，是一个可以在**有限状态机、迭代函数或者链表**上判断是否存在环，求出该环的起点和长度的算法。
其实上面的快慢指针方法就是 Floyd 判圈算法，它不像哈希一样需要很大的空间，所以在空间上是更优的。
还有一种判圈的算法，比它更快，就是 **Brent** 判圈算法，但是这种方式并没有解决计算换的长度、找出换的入口这两个问题。该算法同样会使用两个指针：快慢指针。当着两个指针相遇，就说明存在环。比如，龟和兔子同时出发，龟不动，兔子走一步，第二轮，乌龟跳到兔子的位置，兔子走两步，第三轮。。。。第 n 轮，乌龟跳到兔子的位置，兔子走$2^{n-1}$步。

##### 扩展
在申明类中的成员函数后面加上 `const` 函数就成了只读函数，如 `void append() const {}`，不能修改类的数据成员。

函数指针，创建函数指针可以
```
int(*funPtr)(int, int, double, ...); // 没有参数就什么都不写
int(*const funcPtr)(); // 这样可以创建静态的函数指针
```
> 静态函数指针是指指向静态函数的指针。在C语言和C++中，静态函数是指在函数定义前面加上关键字"static"的函数。静态函数的特点是它们只在定义它们的源文件中可见，不能被其他源文件访问。这意味着静态函数的作用域限制在定义它们的源文件内部。

函数指针在赋值的时候，目标函数比如和函数指针定义的返回值类型和参数个数完全相同。下面两种情况是一样的。
```
int (*funcPtr1)() = foo;
int (*funcPtr2)() = &foo; // c++会隐式得把foo转换成&foo，所以你无需再加入&
```
函数指针的应用：
1. 把函数作为参数传入另一个函数
```
#include <iostream>
int add(int a, int b){
    return a+b;
}
int sub(int a, int b){
    return a-b;
}
void func(int e, int d, int(*f)(int a, int b)){ // 这里才是我想说的，
// 传入了一个int型，双参数，返回值为int的函数
    std::cout<<f(e,d)<<std::endl;
}
int main()
{
    func(2,3,add);
    func(2,3,sub);

    return 0;
}
```

2. 第二个例子，排序上的应用
使用 `ascending` 和 `descending` 两个函数代替大小判断
```
#include <iostream>
template <typename T>
bool ascending(T x, T y) {
    return x > y; 
}
template <typename T>
bool descending(T x, T y) {
    return x < y;
}
template<typename T>
void bubblesort(T *a, int n, bool(*cmpfunc)(T, T)){
    bool sorted = false;
    while(!sorted){
        sorted = true;
        for (int i=0; i<n-1; i++)
            if (cmpfunc(a[i], a[i+1])) {
                std::swap(a[i], a[i+1]);
                sorted = false;
            }
        n--;
    }
}

int main()
{
    int a[8] = {5,2,5,7,1,-3,99,56};
    int b[8] = {5,2,5,7,1,-3,99,56};

    bubblesort<int>(a, 8, ascending);

    for (auto e:a) std::cout << e << " ";
    std::cout << std::endl;

    bubblesort<int>(b, 8, descending);

    for (auto e:b) std::cout << e << " ";

    return 0;
}
```

lambda 函数的书写结构：

```
[capture clause](parameter list) -> return type {
    // Lambda函数体
}
```
<!-- 
函数指针应用？lambda 函数？ 
```
struct FUN {
    成员变量
    void operator()(T t);
}
FUN fun;
fun() 伪装为一个函数？
``` -->

<!-- STL 中的**迭代子类**？？ -->

#### 分而治之 divide-and-conquer

##### 归并排序

一个典例就是归并排序，对于归并排序，为什么递归分成两部分以后排序程序就更快了呢？我感觉是
> 整个数组是无序的，是性质很差的，我们如果想加快排序必需有一些比较好的性质。但是如果对于整个数组获得比较好的性质还不如直接排序？所以我们把数组分成两部分一直分，知道性质很明显，获得有序序列，然后 **性质滚性质**，一直带动，所以可以达到加速的目标。
{%asset_img 时间复杂度计算.png%}

TO DO:
？？非递归版本的归并排序

##### 快速排序

<!-- 快速排序时间复杂度
最坏 概率统计的意义下？ -->
关于快速排序的过程，其实就是每一次取一个数作为基准，然后想把整个数组分为两个部分一个是小于这个基准的，另一个是大于这个基准的。然后有一种很好的方式就是建立两个指针，分别指向数组的左端点和右端点...
{%asset_img 快速排序算法.png%}
关于快速排序的时间复杂度，有最优复杂度、最差复杂度还有平均时间复杂度。
{%asset_img 快速排序时间复杂度.png%}
{%asset_img 快速排序平均时间复杂度.png%}
上面摘自知乎 https://zhuanlan.zhihu.com/p/341201904

##### 2-D maxima finding problem

这是一个 maxima 问题，一般这种问题有两种解决方式。
1. 排序法
{%asset_img 排序法极大点.png%}
2. 分治法
{%asset_img 分治法极大点.png%}
摘自知乎 https://zhuanlan.zhihu.com/p/27850478

TO DO

<!-- 平面极大点
分别解决完左右后，找出右边的第一个 y 最大的点，把左侧的x 和 y 都低于它的点排除 -->

##### the closest pair problem

感觉 OI-Wiki 讲解的很全面
https://oi-wiki.org/geometry/nearest-points/
还有推广：平面最小周长三角形
$\dfrac{d \times 2d}{\frac{1}{4} \times \pi \times (\frac{d}{2})^{2}}$ 虽然不是最精确的，但是已经可以得到一个常数来界定这个范围

<!-- 也是用一个竖线将平面分为左右两个部分，然后分别解决，假设左右的最短距离为 d，那么再遍历竖线左右两边距离 d 内的所有点，找出最小值。？（不缺定）

时间复杂度？ -->
TO DO

##### the convex hull problem

https://blog.csdn.net/lemonxiaoxiao/article/details/108619552
TO DO

<!-- ?
一个著名算法，礼物算法？ Jarvis March
首先最下面的点一定选择，然后逐渐旋转，遇到就选？逆时针还是顺时针呢？有一个判断是向量的叉乘，大于 0 还是小于 0 就是顺着还是逆着
不对的时候是需要回退的，也可能不止一次 Grasham Scan 但是到了三维就不行了
但是 divide-and-conquer 就不一样了，不仅仅更快，而且可以推广到三维空间里面去
找到交点最高和最低，二维的时间复杂度就是 $O(n \log n)$ 三维的就是找三角形了 -->

##### matrix multiplication 

<!-- ?
P Q R S T U V?
时间复杂度大概是 $O(\log_2(7)) \approx O(n^{2.81})$?
但是仍然不是最优的，具体可以自己去搜索一下 -->
使用类实现的矩阵的一些基础操作，可以看 `Fibonacci.cpp`
TO DO

##### FFT

分治做法，见 `FFT.md` 和 `FFT.cpp`(使用自带的 complex 类实现)
其中，使用自己手写类实现的 FFT 在 `FFTClass.cpp`
(注意，如果使用 reverse 函数，注意反转的 F 的区间范围，一开始这里错了，好长时间没找出来)

##### Medians and Order Statistics

对于 n 个数，找出 k-th 数，不排序如何做？因为一排序复杂度就 $O(n\log{n})$ 了，我们如果只想要一个，可不可以做到 $O(n)$。
每一次只选择半个部分，虽然是使用类似于 quick_sort 的方式，但是问题的效率越来越小，所以就得到了 $O(n)$ 的方式，但是 quick_sort 的时间复杂度并不是很稳定。
还有一种递归的算法，分为 5 个数，

nth_element() ?? 函数

TO DO

##### 扩展

尽量不要写递归，但是可以按递归的思路来想，因为递归的程序一般是比较慢。
只是几个简单的案例，但是对于每一个案例都是值得我们去深究的。
为什么这次课讲这部分呢？我们也是要掌握算法思想的。除了分而治之呢，还有自上而下，多层次，自上而下思想等等。

##### Abstract Data Type(ADT)

抽象数据类型

##### 扩展

TO DO

Node 是 List 下面下属的概念，没有必要将 Node 写在 List 外面。
不想改变内部元素的时候记得加 const，如果不加的话，`void Func(const List& l) { l.print(); }` 其中不允许调用，因为 Func 有修改成员变量的风险。
**常引用？**
**把函数当作函数的参数？**
派生类禁止父类的函数或者方法？ 
括号匹配问题 Bracket Matching Problem
计算一个式子的值 postfix calculator 也可以适用于简单的四则运算的场合
双端队列 dequeue
环形数组

#### 递归消除

##### 一般性消除办法

- 利用堆栈，模拟栈来实现，见 `Hanoi.cpp`

汉诺塔问题 递归求解，如何去掉递归求解。
$f_n = 2 f_{n - 1} + 1$，所以 $(f_n + 1) = 2(f_{n - 1} + 1)$

##### 倒水问题

这种任务方案其实挺多的。其实，背后对应的是**辗转相除法**。
我们可以倒出来的水的数量就是余数。
设一个杯子是 a 升，另一个杯子是 b 升，我们想获得 c 升水，就是 `ax + by = c`，如果有解，就是 $\gcd{(a, b)} | c$

##### 求解组合数

https://oi-wiki.org/math/combinatorics/combination/ 见 OI-Wiki各种组合数公式
https://zhuanlan.zhihu.com/p/602675596 二项式反演

##### 扩展

实现 Stack 的时候，太过于依赖于 List 的实现机理，比如说直接从底层指针上来做。但是这样的话，List 一旦修改，我们的 Stack 就会出现问题。这就是**过于耦合了**。所以，对于一个类来说，接口是很重要的。

##### lowbit

#### 树和二叉树

树中所有节点度数的最大值叫做整个树的度。

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
将叶子节点的右孩子指向下一个应改遍历的节点(因为一开始叶子节点的右孩子是 null，造成了浪费)
并且加一个 bool 类型的变量，表示这个节点的右孩子是不是进行了修改。
这样中序遍历的时候好像也会简单很多(在中序遍历的意义下，将二叉树变成了一个单链表)
这样二叉树的遍历就不再依赖于堆栈，并且产生了向前向后的两个方向，和双链表的行为是比较相似的。

##### 前序遍历的线索二叉树

顺序建立就是修改右子树
但是如果反过来会出现左孩子已经被占用的问题，此时需要借助堆栈

##### 后序遍历的线索二叉树


{%asset_img 线索二叉树.png%}

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

##### Fibonacci 堆

##### lazy 机制

上面的最简单的二叉堆做法呢，我们很好地利用了二叉树序号之间的关系(父子的序号有关系)，但是我们在更新的时候每一次都是 $\log{n}$ 的复杂度，不是很优，比如说有些元素我们以后根本用不到，而堆又本身不是关注全序关系的，所以我们可以利用 lazy 机制。

TODO 
现在库里面的堆，基本上都不是基于 **二叉堆**(Binary Heap) 实现的。
Fibonacci 堆 也是希望我们去更多地了解一些堆。
堆的合并、二叉堆的合并？
二项堆
重载运算符

#### 编码问题

结构光扫描中，我们如何马上知道这条光是第几条光？就要用到编码了
能不能发明一种序列，使得连续的几个在序列中是唯一的，longest ？ 是多长？
3 个颜色的话，先画出 27 个节点。RRR 的话，连接 RRG RRB(它的后继节点)
寻找访问序列最长的，而且不能重复
深度遍历可以吗？最好不要写递归，可以队列、栈

#### 霍夫曼树

每一次找权值最小两个节点，变为 n - 1 个节点
1. 能不能构建出来
2. 总体的最小代价
可以搜索霍夫曼树的题目
实现持久化的最小两个数？手写优先队列？平衡树？

#### 左倾堆 / 左倾树 / 左偏堆 / 左偏树

虽然二叉堆的插入、删除操作挺好的，但是不支持合并。所以我们想寻找一种数据结构使得堆在合并的时候比较高效。
> Leftist Heap is a priority queue data structure that also supports merge of heaps in O(log n) time.

FHQ Treap TODO

https://www.luogu.com.cn/blog/qkhm/zuo-pian-shu-xue-xi-bi-ji TODO

最优传输理论

启发式合并堆

#### 二叉平衡树

可以证明平衡二叉树的高度为 $\log{n}$ 吗？

N(h) = 1 + N(h - 1) + N(h - 2); AVL 树的高度推导 N(h) 表示高度为 h 时最不平衡时的节点个数。

我们是按照左右子树的树高度之差来定义的，这只是定义平衡的一种。但是还有很多别的方式，比如左右子树的节点。

维护平衡的机制有很多种，比如说典型的 B 树，2-3-4树，它所有的叶子都在同一个高度上面。它最不满的情况就是一个满二叉树，所以它可以保证高度在 $\log$ 级别。

AVL B树 红黑树 234树 Treap
红黑树的实际应用比较频繁，它的效率比较高一点。红黑树和 234树之间的关系？？ TODO

插入的时候常常面临三种情形。

https://www.luogu.com.cn/blog/MashPlant/solution2-p3369 B 树代码

LCT问题？ Link Cut Tree

Treap 的高度 log 证明？

#### the mathematics of rubik's cube

#### Dijkstra 算法

正确性证明？

多边形

差分约束问题 线性规划问题 max \sum d 要求比 dijkstra 更加严苛？

Gorubi 

最短路的话线性规划没有 dijkstra 更加优

A* 算法？

#### 二叉树在区间上？

维护直接的 Rank 感觉代价过于高，因为每一次删除和插入都要把其余元素都改变一次，所以我们不直接维护 Rank。


二叉树序列化？https://zhuanlan.zhihu.com/p/26418233

#### 线段相交的问题

两个结构：
1. 处理事件的优先队列(关键位置停下来，遇到了水平线段的左端点，遇到了水平线段的右端点，遇到了竖直线段)(需要使用一个二叉树维护水平线段，包括水平竖直关系)(水平线段的 y 高度使用二叉树维护了？树套树？)
2. 维护扫描的每个关键位置的全序列表

#### kd 树

grid 2d tree
quadtree(四叉树，每一个格子一分为 4) bsptree(每一次有一个平面，对于所在的平面二分，在二维的情况下就是直线)

上面的结构，除了 grid 的应用都是很多的。各自在不同的应用场景下使用。

kd 树其实是 bst 树的延申。可是很多时候一维数据是不够的，很多情况都是高维的东西。在机器学习中应用也很多。
ray tracing
2d range serach

从乱序中在 O(n) 的时间复杂度下找出中位数。

1. 每一刀下去，都是将矩形分为两个部分。
2. 奇偶相间，第一层竖线划分，第二层就是水平划分。(优化就是把点很紧密的包在一块？)

nth_element 严格 O(n) 查找中位数

#### 跳表 Skip List

跳表是相对年轻的一个数据结构，1990 年由 Bill Pugh 提出。
我们需要区分一下数据域和指针域
https://www.cnblogs.com/bigsai/p/14193225.html

#### KMP

前缀和后缀的问题

BM 算法？

DFA

#### 并查集(Union-find)

虽然并查集的代码是最少的一个，但是确实非常有用的。它可以解决**等价类**相关的问题。

link-by-size 按照大小合并，此时最高高度不超过 log n
当然也有按照 rank(height)高度合并。

还有路径压缩(path compression)

无路径压缩的时候，复杂度是 $m \log n$
有路径压缩的时候，复杂度是 $m \alpha (m, n)$
其中，$\alpha$ 是反阿克曼函数。

#### 图

每一个节点有 in 和 out 两个邻接表

矩阵的形式存储的时候，可能并行化运算的时候更加容易。

prim 求最小生成树

稠密图和稀疏图使用不同的堆复杂度还不一样？？

Kruskal 实现最小生成树

稀疏图 prim 和 kruskal 复杂度差不多，但是稠密图中似乎 prim 算法比较好。

cut 割

割中最小权值的边一定出现在最小生成树上 证明了 Prim 的正确性？


##### 欧拉回路问题

桥 bridge 它的去除，影响了整个图的连通性

证明方式

如何找到欧拉回路(两种算法)?

Fleury's Algorithm(佛罗莱)算法 此时经常有一种方法和它相提并论，Hierholzer(希尔霍尔策算法) 算法，后者实际上运行效率会更高一点(标记的注意事项？)，感觉有一个硬伤，并查集没有办法递增式构建？？。

欧拉骰子？？

相联系的有一个哈密顿回路问题。

桥和割边的关系？

#### 

### 作业

1. 手写一个 List

见 `List.cpp` `LinkList.h` `LinkList.cpp` 
其中，`List.cpp` 将 Node 和 List 两个类分开写了，所以在 List 中使用 Node 的时候要写成 `Node<T>*` 的形式。
但是在 `LinkList.h` 中，将 Node 写在了 List 类里面，此时就不需要在 Node 后面额外加 `<T>` 了，这种形式也是我们更加推荐的。

2. 手写一个面向对象的快速排序
`quick_sort.cpp` 是一个递归版本的，但是我们一般不鼓励写递归，会比较慢
其中，需要注意`函数对象`的写法。

非递归版本：
**双指针前移法**
感觉很强，短小精悍
见 `QuickSortNor.cpp`
使用自己手写的栈，实现了对于类的非递归版本的快速排序。

3.  
<!-- 基于自己写的链表
实现堆栈
放在不同的文件中
想规范一下大家写代码习惯 -->
在这次的作业中，注意：
我们在使用了模板类的 LinkList 中添加重载输出的友元函数。因为我们毕竟添加的是一个友元函数，是一个函数，所以我们需要在 LinkList 中再写一个 template<class E>
```
template<class U>
friend std::ostream& operator<<(std::ostream& os, const LinkList<U>& list);
```
其中，ostream 是一种返回类型。

4. 
- 以非递归的形式实现汉诺塔，并且尽量少内存。
见 `Hanoi.cpp`
- 写最大公约数递推的程序。给定两个整数，写出最大公约数的标准形式，d = ax + by，x y 可能是负数 我们规定 |x| < |y| 此时取值是唯一的。
见 `exgcd.cpp`
上面的扩展欧几里得是递归实现的，但是我们还是追求非递归版本，讲解参考下面的博客：
https://www.cnblogs.com/zbhfz/p/11267438.html
{%asset_img 非递归扩展欧几里得.png%}

5. 非递归全排列
康托展开
非递归，根据排列规律输出所有的排列

见 `CantorExpansion.cpp` `permutation.cpp` `next_permutation.cpp` 

6. 求斐波那契数列通项
特征根法怎么来的呢？
人们发现特征根对于分解递推式子是有帮助的
对于一个具体的 n 输出 F_n
矩阵加速递推
见 `Fibonacci.cpp`

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

19. 快速排序进阶。多种排序方式组合实现一个高效的快速排序。
使用快速排序(在其函数上进行修改)实现线性查找元素第 k 小。
荷兰旗问题？

20. 给定若干竖直和水平的随机长度的线段，并且保证一个 y 坐标或者一个 x 坐标下只有一条线段，求这些线段的交点个数。

21. 最长公共子序列

22. bitset 求解高维偏序问题

23. k 短路问题

24. 完成 KMP 算法

25. 并查集实现 鼓励大家实现基于 rank 的 union，希望并查集中有路径压缩的功能（不需要新写一个函数，只需要在 find 时顺便修改）。

26. 实现 Prim 算法

27. 实现 Kruskal 算法

28. 教材以 Fleury 算法为主，但是老师更希望实现 希尔霍尔策算法，体会在桥边上有没有更好的策略。

29. 
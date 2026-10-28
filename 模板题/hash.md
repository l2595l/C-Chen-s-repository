```c++
//拉链法
const int N = 1e7 + 19; //大于1e7最小的质数，可以直接写个程序跑一下
struct Hash{
	int h[N]; //哈希表
	int e[N], ne[N], idx = 0; //这是链表的东西
	void insert(int x) //插入一个数x
	{
		int k = (x % N + N) % N; //k是x对应的哈希值
        //为什么要 (x % N + N) % N 呢？因为处理的时候
        //可能会遇到x是负数的情况，如果对负数取模，
        //结果也是负数，而我们要的是非负整数值，所以
        //通过这样把取模结果转化为非负数
		e[idx] = x;
		ne[idx] = h[k];
		h[k] = idx ++; //链表的基本操作
		return;
	}
	bool find(int x) //查找x
	{
		int k = (x % N + N) % N; //计算x的哈希值
		for(int i = h[k]; i != -1; i = ne[i])
			if(e[i] == x) return true; //如果找到了，返回true
		return false; //遍历完了都没找到，返回false
	}
	void init()
	{
		memset(h, -1, sizeof(h)); //初始化，让h中的初始值都为-1
		return;
	}
};
```
```c++
//开放寻址法
const int N = 1e7 + 19;
struct Hash_table{
	const int null = 0x3f3f3f3f; //相当于一个空指针
	int h[N]; //哈希表
	void init()
	{
		memset(h, 0x3f, sizeof(h));
		return;
	}
	int find(int x) //在哈希表中查找x
	{
		int k = (x % N + N) % N; //x的哈希值
		while(h[k] != null && h[k] != x) //如果一直没找到x
		{
			k ++;
			if(k == N) k = 0; //如果找到了最后一个，就要从第一个开始，让k=0
		}
		return k; //返回x的位置（找到）或x应当存在的位置（未找到）
	}
	void insert(int x) //插入x
	{
		int k = find(x);
		h[k] = x;
		return;
	}
};
```
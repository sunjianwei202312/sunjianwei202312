#ifndef _BSTREE_H_
#define _BSTREE_H_
#include 	"includes.h"
//下述代码演示了如何创建BST二叉树
typedef struct Node
{
	struct Node *left;
	struct Node *right;
	size_t size;  //数据的空间大小
	INT8U  data[];//数据本身
}Node_t;
//必须提供两个辅助的函数，第一个用来得到“对应于数据”的键值；第二个用来比较两个键值
typedef const void *GetKeyFunc_t (const void *dData);//第一个函数具有如下原型
//第二个函数类似于标准函数bsearch（）所使用的“比较函数”
typedef INT16U CmpFunc_t(const void *pKey1,const void *pKey2);
//调用比较函数时所传递的自变量，是指向两个“计划比较”的键值得指针。此函数的返回值小于0，表示第一个键值小于第二个键值；
//等于0，表示两个键值相等；大于0，表示第一个键值大于第二个键值；
//接下来，我们定义一个结构类型，用来代表一个树，此机构有三个成员：
//指向树根的指针
//指向计算键值得指针（类型为GetKeyFunc_t)
//指向比较函数的指针（类型为CmpFunc_t)

typedef struct {
	struct Node *pRoot;  //指向树根的指针
	CmpFunc_t *cmp;      //比较两个键值
	GetKeyFunc_t *getKey;//将数值变为键值
}BST_t;

//BST_t *newBST( 



#endif

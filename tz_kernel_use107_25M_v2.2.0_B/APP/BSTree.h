#ifndef _BSTREE_H_
#define _BSTREE_H_
#include 	"includes.h"
//����������ʾ����δ���BST������
typedef struct Node
{
	struct Node *left;
	struct Node *right;
	size_t size;  //���ݵĿռ��С
	INT8U  data[];//���ݱ���
}Node_t;
//�����ṩ���������ĺ�������һ�������õ�����Ӧ�����ݡ��ļ�ֵ���ڶ��������Ƚ�������ֵ
typedef const void *GetKeyFunc_t (const void *dData);//��һ��������������ԭ��
//�ڶ������������ڱ�׼����bsearch������ʹ�õġ��ȽϺ�����
typedef INT16U CmpFunc_t(const void *pKey1,const void *pKey2);
//���ñȽϺ���ʱ�����ݵ��Ա�������ָ���������ƻ��Ƚϡ��ļ�ֵ��ָ�롣�˺����ķ���ֵС��0����ʾ��һ����ֵС�ڵڶ�����ֵ��
//����0����ʾ������ֵ��ȣ�����0����ʾ��һ����ֵ���ڵڶ�����ֵ��
//�����������Ƕ���һ���ṹ���ͣ���������һ�������˻�����������Ա��
//ָ��������ָ��
//ָ������ֵ��ָ�루����ΪGetKeyFunc_t)
//ָ��ȽϺ�����ָ�루����ΪCmpFunc_t)

typedef struct {
	struct Node *pRoot;  //ָ��������ָ��
	CmpFunc_t *cmp;      //�Ƚ�������ֵ
	GetKeyFunc_t *getKey;//����ֵ��Ϊ��ֵ
}BST_t;

//BST_t *newBST( 



#endif

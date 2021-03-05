#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef int DataType;

typedef struct Node {
	DataType data; // 值 
	struct Node *next; // 指向下一个结点 
} Node,*PNode;

// pHead 是一个指向头节点的指针
void NodeInit(PNode *pHead); // 初始化 ,构造一条空的链表
void NodePrint(PNode pHead); //打印链表
void NodePushBack(PNode pHead, DataType data); // 尾部插入 
void NodePushFront(PNode pHead, DataType data); // 头部插入 
int length_list(PNode pHead); // 获取链表长度
void NodeDestroy(PNode pHead); // 销毁 ，需要销毁每一个节点
void NodePopBack(PNode pHead); // 尾部删除
void NodePopFront(PNode pHead); // 头部删除 
void NodeInsert(PNode pHead, int pos, DataType data); // 给定结点插入，插入到结点前
void NodeErase(PNode pHead, int pos); // 给定结点删除 ，按索引
void NodeErase2(PNode pHead, PNode pos); // 给定节点删除，按指针
int getElemData(PNode pHead, int pos, DataType *val); // 获取给定位置节点
int NodeFind(PNode pHead, DataType data); // 按值查找，返回第一个找到的结点位置，如果没找到，返回 NULL 
PNode NodeFind2(PNode pHead, DataType data); // 按值查找，返回第一个找到的结点指针，如果没找到，返回 NULL 
void NodeRemove(PNode pHead, DataType data); // 按值删除，只删遇到的第一个 
void NodeRemoveAll(PNode pHead, DataType data); // 按值删除，删除所有的 

// 查找某个节点的元素值

int main (int argc, char *argv[])
{
	PNode pHead;
	int length;
	DataType a[5] = {1,2,3,4,5};
	NodeInit(&pHead);  // 创建单链表
		
	for (int i = 0; i < sizeof(a)/sizeof(a[0]); i++) {
		NodePushBack(pHead, a[i]);
		NodePushFront(pHead, a[i]);
	}
	NodePrint(pHead);   // 打印节点
	
	NodePopBack(pHead); // 尾删法
	NodePrint(pHead);   // 打印节点
	
	NodePopFront(pHead); // 头删法
	NodePrint(pHead);   // 打印节点
	
	NodeInsert(pHead, 2, a[4]); // 插入到结点前
	NodePrint(pHead);   // 打印节点
	
	NodeErase(pHead, 2); //删除指定节点
	NodePrint(pHead);   // 打印节点
	
	
	DataType Tmp;
	getElemData(pHead, 3, &Tmp); // 获取链表数据
	printf("tmp : %d\n", Tmp);
	
	int c = NodeFind(pHead, 1); //查找链表数据
	PNode pTmp = NodeFind2(pHead, 2);
	printf("c : %d, pTmp->data : %d\n", c, pTmp->data);
	NodeErase2(pHead, pTmp);
	NodePrint(pHead);   // 打印节点
	
	NodeRemove(pHead, 2);
	NodePrint(pHead);   // 打印节点
	
	NodeRemoveAll(pHead, 4);
	NodePrint(pHead);   // 打印节点
	NodeRemoveAll(pHead, 1);
	NodePushBack(pHead, a[2]);
	NodePrint(pHead);   // 打印节点
	
	
	NodeRemoveAll(pHead, 3);
	NodePrint(pHead);   // 打印节点
	length = length_list(pHead);
	printf("链表长度 : %d\n", length);
	
	NodeDestroy(pHead); // 销毁链表
	free(pHead);
	return 0;
}

void NodeInit(PNode *pHead) // 初始化 ,构造一条空的链表
{
	*pHead = (PNode)malloc(sizeof(Node));
	if(*pHead == NULL){
		printf("内存分配失败，程序终止！\n");
		return;
	}
	(*pHead)->next = NULL;
}

void NodePrint(PNode pHead) //打印链表
{
	//初始指向第一个有效结点
	PNode p = pHead->next;
	while(p != NULL) {
		printf("%d\t",p->data);
		p = p->next;
	}
    printf("\n");
}

void NodePushBack(PNode pHead, DataType data) // 尾部插入 
{
	PNode pNew;
	PNode cur = pHead;
	
	//创建新结点
	pNew = (PNode) malloc(sizeof(Node));
	if(pNew == NULL){
		printf("内存分配失败，程序终止！\n");
		return;
	}

	memcpy(&(pNew->data), &data, sizeof(DataType)); // 数据拷贝
	
	//找链表中的最后一个节点
	while (cur->next != NULL)
	{
		cur = cur->next;
	}
	cur->next = pNew;
	pNew->next = NULL; //将尾结点指针域置为NULL
} 
void NodePushFront(PNode pHead, DataType data) // 头部插入 
{
	PNode pNew;

	//创建新结点
	pNew = (PNode)malloc(sizeof(Node));
	if(pNew == NULL) {
		printf("内存分配失败，程序终止！\n");
		return;//结束程序
	}

	memcpy(&(pNew->data), &data, sizeof(DataType)); // 保存结点数据
	
	//头插法插入结点
	pNew->next = pHead->next;
	pHead->next = pNew;
}

int length_list(PNode pHead)
{
	//初始指向第一个有效结点
	PNode p = pHead->next;
	int i = 0;
	while(p != NULL){
		i++;
		p = p->next;
	}
	return i;
}

void NodeDestroy(PNode pHead)
{
	// 清空
	PNode p,q;
	p = pHead->next;  
    while(p != NULL)  
    {  
        q = p->next; 
        free(p); 
        p = q;  
    }  
    pHead->next=NULL;
}

void NodePopBack(PNode pHead) // 尾部删除 
{
	PNode cur = pHead;
	while (cur->next->next != NULL) {
		cur = cur->next;
	}
	free(cur->next);
	cur->next = NULL;
}

void NodePopFront(PNode pHead) // 头部删除 
{
	assert(pHead->next != NULL);
	PNode p = pHead->next;
	pHead->next = pHead->next->next;
	free(p);
}

void NodeInsert(PNode pHead, int pos, DataType data) // 给定结点插入，插入到结点前 
{
	PNode p, pNew;
	int len, i = 0;
	//初始指向头结点
	p = pHead;
	len = length_list(pHead);
	//判断pos值的合法性
	if(pos < 1 || pos > len + 1){
		return;
	}
	//找到插入位置的前一个结点，即:pos - 1位置的结点
	while (i < pos - 1 && p != NULL) {
		i++;
		p = p->next;
	}
	if (p == NULL) {
		return;
	}
	//此时p为pos - 1位置的结点
	//创建新结点
	pNew = (PNode)malloc(sizeof(Node));
	if (pNew == NULL) {
		printf("分配内存失败，程序终止！");
		exit(-1);
	}
	memcpy(&(pNew->data), &data, sizeof(DataType)); // 保存结点数据
	//插入结点
	pNew->next = p->next;
	p->next = pNew;
}

void NodeErase(PNode pHead, int pos) // 给定结点删除，按索引 
{
	PNode p, s;
	int len, i = 0;
	len = length_list(pHead);
	p = pHead;
	//判断pos值合法性
	if(pos < 1 || pos > len){
		return;
	}
	//找到带删除结点的前一个结点，即：pos - 1位置的结点
	while(i < pos - 1 && p != NULL){
		i++;
		p = p->next;
	}
	if (p == NULL) {
		return;
	}
	//此时p为pos - 1位置的结点
	s = p->next; //此时s为待删除结点
	//删除结点
	p->next = s->next;
	free(s);
}

void NodeErase2(PNode pHead, PNode pos) // 给定结点删除,按指针
{
	if (pHead == pos) {
		return;
	}
	PNode cur = pHead;
	while (cur->next != pos) {
		cur = cur->next;
	}
	cur->next = pos->next;
	free(pos);
}


int getElemData(PNode pHead, int pos, DataType *val) 
{
	PNode p;
	int len, i = 0;
	p = pHead;//初始指向头结点
	len = length_list(pHead);
	//判断pos值的合法性
	if (pos < 1 || pos > len) {
		return 0;
	}
	//找到pos位置的结点
	while (i < pos && p != NULL) {
		i++;
		p = p->next;
	}
	if (p == NULL) {
		return 0;
	}
	//此时p即为指定位置的结点
	//保存结点元素值
	memcpy(val, &(p->data), sizeof(DataType)); // 保存结点数据
	return 1;
}

int NodeFind(PNode pHead, DataType data) // 按值查找，返回第一个找到的结点位置，如果没找到，返回 NULL  */
{
	PNode p;
	int i = 0;
	p = pHead;//初始指向头结点
	//遍历链表
	while(p != NULL && p->data != data){
		i++;
		p = p->next;
	}
	if(p == NULL){
		//此时说明链表遍历到了结尾，仍没有找到元素值
		return -1;
	} else {
		return i;
	}
}


PNode NodeFind2(PNode pHead, DataType data) // 按值查找，返回第一个找到的结点指针，如果没找到，返回 NULL 
{
	for (PNode cur = pHead; cur != NULL; cur = cur->next)
	{
		if (cur->data == data)
		{
			return cur;
		}
	}
	return NULL;
}

void NodeRemove(PNode pHead, DataType data) // 按值删除，只删遇到的第一个 
{
	if (pHead == NULL) {
		return;
	}
	PNode cur = pHead;
	PNode prev = cur;
	while (cur) {
		if (cur->data == data) {
			//删除第一个节点
			prev->next = cur->next;
			free(cur);
			cur = NULL;
			break;
		} 
		prev = cur;
		cur = cur->next;
	}
}

void NodeRemoveAll(PNode pHead, DataType data) // 按值删除，删除所有的 
{
	if (pHead == NULL) {
		return;
	}
	PNode cur = pHead->next;
	PNode prev = cur;
	while (cur) {
		if (cur->data == data) {
			//1.删除的是第一个节点
			if (pHead->next == cur) {
				pHead->next = cur->next;
				free(cur);
				cur = pHead;
			} else { //删除中间节点
				prev->next = cur->next;
				free(cur);
				cur = prev;
			}
		}
		prev = cur;
		cur = cur->next;
	}
}

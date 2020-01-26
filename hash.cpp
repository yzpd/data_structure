#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "hash.h"

#define MAXWORDLEN 80	//单词最大的长度

//位移法：把字符串各位向左位移5位,计算其对于的int值
int Hash(const char* key, int TableSize) {
	unsigned int H = 0;
	while (*key != '\0')
		H = (H << 5) + *key++;

	return H % TableSize;
}

//确定一个不小于TableSize的素数,用作真正的散列表的地址空间大小
int NextPrime(int N)
{
	/*返回大于N且不超过MAXTABLESIZE的最小素数*/
	int i, p = (N % 2) ? N + 2 : N + 1;	/*从大于N的下一个奇数开始*/

	while (p <= MAXTABLESIZE)
	{
		for (i = (int)sqrt(p); i > 2; i++)
			if (!(p%i)) break;	/*p不是素数*/
		if (i == 2) break;		/*for正常结束，p是素数*/
		else p += 2;			/*试探下一个奇数*/
	}

	return p;
}

HashTable CreateTable(int TableSize)
{
	HashTable H;
	int i;

	H = (HashTable)malloc(sizeof(struct TblNode));

	H->TableSize = NextPrime(TableSize);
	H->Heads = (List)malloc(sizeof(struct LNode) * (H->TableSize + 1));
	/*初始化表头*/
	for ( i = 0; i < H->TableSize ; i++ )
	{
		H->Heads[i].data[0] = '\0';
		H->Heads[i].next = NULL;
		H->Heads[i].count = 0;
	}

	return H;
}

void DestroyTable(HashTable H)
{
	int i;
	Position P, Tmp;

	for (i = 0;i < H->TableSize;i++) {
		P = H->Heads[i].next;
		while (P) {
			Tmp = P->next;
			free(P);
			P = Tmp;
		}
		free(H->Heads);
		free(H);
	}
}

Position Find(HashTable H, Type key)
{
	Position P;
	Index Pos;

	Pos = Hash(key, H->TableSize);
	P = H->Heads[Pos].next;
	while(P && strcmp(P->data, key))
		P = P->next;
	
	return P;
}

//链表的头结点不用,不过它的count代表此链表单词的数量
void InsertAndCount(HashTable H, Type key)
{
	Position P, NewCell;
	Index Pos;

	P = Find(H, key);
	if (!P) {
		NewCell = (Position)malloc(sizeof(struct LNode));
		strcpy(NewCell->data, key);
		NewCell->count = 1;
		Pos = Hash(key, H->TableSize);
		NewCell->next = H->Heads[Pos].next;
		H->Heads[Pos].next = NewCell;
		H->Heads[Pos].count++;
	}
	else
		P->count++;

}

//判断一个单词是否为合法字符,合法字符为大小写字母,数字和下划线
bool IsWordChar(char c)
{
	if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9' || c == '_')
		return true;
	else
		return false;
}

//从给定文件中读取一个单词，返回该单词的长度，超出KEYLENGTH的长度将截去
int GetWord(FILE* fp, Type word) {
	char tempword[KEYLENGTH + 1], c;
	int len = 0;	//单词长度

	c = fgetc(fp);
	while (!feof(fp)) {
		if (IsWordChar(c))
			tempword[len++] = c;
		c = fgetc(fp);
		/*跳过单词前的非法字符(因为len=0，后面会筛去len小于3的字符,所以就一并跳过了),或以非法字符结束的一个单词*/
		if (len && !IsWordChar(c))
			break;
	}
	tempword[len] = '\0';
	if (len > KEYLENGTH)
	{
		tempword[KEYLENGTH] = '\0';
		len = KEYLENGTH;
	}
	strcpy(word, tempword);
	return len;
}

void Show(HashTable H, double percent)
{
	int diffwordcount = 0;	//不同的单词数量
	int maxf = 0;			//最大的词频
	int* diffwords;			//每个词频对应的不同单词数量
	int maxCollision = 0;	//最大冲突次数,初始化为0
	int minCollision = 100;	//最小冲突次数,初始化为100
	Position L;
	int i, j, k, lowerbound, count = 0;

	for (i = 0; i < H->TableSize; i++) {
		/*求不同的单词数量*/
		diffwordcount += H->Heads[i].count;
		/*统计最大和最小的冲突次数*/
		if (maxCollision < H->Heads[i].count)
			maxCollision = H->Heads[i].count;
		if (minCollision > H->Heads[i].count)
			minCollision = H->Heads[i].count;
		/*求最大的词频*/
		L = H->Heads[i].next;
		while (L) {
			if (maxf < L->count) maxf = L->count;
			L = L->next;
		}
	}

	printf("共有%d个不同的单词，词频最大的是%d；\n", diffwordcount, maxf);
	printf("最大的冲突次数是%d, 最小的冲突次数是%d。\n", maxCollision, minCollision);


	/*求每个词频拥有的不同单词数量*/
	/*根据最大的词频，分配一个整数数组*/
	diffwords = (int*)malloc((maxf + 1) * sizeof(int));
	/*统计词频从1到maxf的单词数量*/
	for (i = 0; i <= maxf; i++)
		diffwords[i] = 0;
	for (i = 0; i < H->TableSize;i++) {
		L = H->Heads[i].next;
		while (L) {
			diffwords[L->count]++;
			L = L->next;
		}
	}

	/*求特定的词频，使得大于等于该词频的单词总和超过给定的比例*/
	lowerbound = (int)(diffwordcount * percent);
	for (i = maxf;i >= 1 && count < lowerbound;i--)
		count += diffwords[i];
	//printf("count = %d\n", count);
	//printf("i = %d\n", i);

	/*按词频从大到小输出单词*/
	for (j = maxf;j >= i;j--) {
		for (k = 0; k < H->TableSize; k++) {
			L = H->Heads[k].next;
			while (L) {
				if (j == L->count)
					printf(" %-15s ：%d\n", L->data, L->count);
				L = L->next;
			}
		}
	}
	free(diffwords);
}

int main() {
	FILE *fp;
	HashTable H;
	Type word;
	int TableSize = 100;
	int length, wordcount = 0;
	char document[100] = "C:\\Users\\yzpd\\Desktop\\学习\\data_structure\\data_structure\\data_structure\\text.txt";	//用绝对地址

	H = CreateTable(TableSize);
	if ((fp = fopen(document, "r")) == NULL) {
		printf("无法打开文件！\n");
		getchar();
		return -1;
	}
		
	while (!feof(fp)) {
		length = GetWord(fp, word);
		if (length > 3) {
			wordcount++;
			InsertAndCount(H, word);
		}
	}
	fclose(fp);

	printf("该文档共出现%d个有效单词\n", wordcount);
	Show(H, 10.0 / 100);/*显示词频前10%的所有单词*/
	DestroyTable(H);
	getchar();
	return 0;
}

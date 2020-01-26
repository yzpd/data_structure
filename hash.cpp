#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "hash.h"

#define MAXWORDLEN 80	//�������ĳ���

//λ�Ʒ������ַ�����λ����λ��5λ,��������ڵ�intֵ
int Hash(const char* key, int TableSize) {
	unsigned int H = 0;
	while (*key != '\0')
		H = (H << 5) + *key++;

	return H % TableSize;
}

//ȷ��һ����С��TableSize������,����������ɢ�б�ĵ�ַ�ռ��С
int NextPrime(int N)
{
	/*���ش���N�Ҳ�����MAXTABLESIZE����С����*/
	int i, p = (N % 2) ? N + 2 : N + 1;	/*�Ӵ���N����һ��������ʼ*/

	while (p <= MAXTABLESIZE)
	{
		for (i = (int)sqrt(p); i > 2; i++)
			if (!(p%i)) break;	/*p��������*/
		if (i == 2) break;		/*for����������p������*/
		else p += 2;			/*��̽��һ������*/
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
	/*��ʼ����ͷ*/
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

//�����ͷ��㲻��,��������count����������ʵ�����
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

//�ж�һ�������Ƿ�Ϊ�Ϸ��ַ�,�Ϸ��ַ�Ϊ��Сд��ĸ,���ֺ��»���
bool IsWordChar(char c)
{
	if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9' || c == '_')
		return true;
	else
		return false;
}

//�Ӹ����ļ��ж�ȡһ�����ʣ����ظõ��ʵĳ��ȣ�����KEYLENGTH�ĳ��Ƚ���ȥ
int GetWord(FILE* fp, Type word) {
	char tempword[KEYLENGTH + 1], c;
	int len = 0;	//���ʳ���

	c = fgetc(fp);
	while (!feof(fp)) {
		if (IsWordChar(c))
			tempword[len++] = c;
		c = fgetc(fp);
		/*��������ǰ�ķǷ��ַ�(��Ϊlen=0�������ɸȥlenС��3���ַ�,���Ծ�һ��������),���ԷǷ��ַ�������һ������*/
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
	int diffwordcount = 0;	//��ͬ�ĵ�������
	int maxf = 0;			//���Ĵ�Ƶ
	int* diffwords;			//ÿ����Ƶ��Ӧ�Ĳ�ͬ��������
	int maxCollision = 0;	//����ͻ����,��ʼ��Ϊ0
	int minCollision = 100;	//��С��ͻ����,��ʼ��Ϊ100
	Position L;
	int i, j, k, lowerbound, count = 0;

	for (i = 0; i < H->TableSize; i++) {
		/*��ͬ�ĵ�������*/
		diffwordcount += H->Heads[i].count;
		/*ͳ��������С�ĳ�ͻ����*/
		if (maxCollision < H->Heads[i].count)
			maxCollision = H->Heads[i].count;
		if (minCollision > H->Heads[i].count)
			minCollision = H->Heads[i].count;
		/*�����Ĵ�Ƶ*/
		L = H->Heads[i].next;
		while (L) {
			if (maxf < L->count) maxf = L->count;
			L = L->next;
		}
	}

	printf("����%d����ͬ�ĵ��ʣ���Ƶ������%d��\n", diffwordcount, maxf);
	printf("���ĳ�ͻ������%d, ��С�ĳ�ͻ������%d��\n", maxCollision, minCollision);


	/*��ÿ����Ƶӵ�еĲ�ͬ��������*/
	/*�������Ĵ�Ƶ������һ����������*/
	diffwords = (int*)malloc((maxf + 1) * sizeof(int));
	/*ͳ�ƴ�Ƶ��1��maxf�ĵ�������*/
	for (i = 0; i <= maxf; i++)
		diffwords[i] = 0;
	for (i = 0; i < H->TableSize;i++) {
		L = H->Heads[i].next;
		while (L) {
			diffwords[L->count]++;
			L = L->next;
		}
	}

	/*���ض��Ĵ�Ƶ��ʹ�ô��ڵ��ڸô�Ƶ�ĵ����ܺͳ��������ı���*/
	lowerbound = (int)(diffwordcount * percent);
	for (i = maxf;i >= 1 && count < lowerbound;i--)
		count += diffwords[i];
	//printf("count = %d\n", count);
	//printf("i = %d\n", i);

	/*����Ƶ�Ӵ�С�������*/
	for (j = maxf;j >= i;j--) {
		for (k = 0; k < H->TableSize; k++) {
			L = H->Heads[k].next;
			while (L) {
				if (j == L->count)
					printf(" %-15s ��%d\n", L->data, L->count);
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
	char document[100] = "C:\\Users\\yzpd\\Desktop\\ѧϰ\\data_structure\\data_structure\\data_structure\\text.txt";	//�þ��Ե�ַ

	H = CreateTable(TableSize);
	if ((fp = fopen(document, "r")) == NULL) {
		printf("�޷����ļ���\n");
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

	printf("���ĵ�������%d����Ч����\n", wordcount);
	Show(H, 10.0 / 100);/*��ʾ��Ƶǰ10%�����е���*/
	DestroyTable(H);
	getchar();
	return 0;
}

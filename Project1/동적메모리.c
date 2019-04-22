#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <memory.h>
//=============================================================================
//���� �޸� ���� ���
//new-->malloc �Լ�
//=============================================================================
//heap�� �޸𸮸� �Ҵ��ϴ� �Լ�
//=============================================================================
//-malloc memory allocation
//-calloc
//-realloc
//=============================================================================
//-free
//=============================================================================






int main(void) {
	//malloc(�Ҵ��� �޸��� ũ��)
	//���� : �Ҵ���� �޸��� ������ġ�� �ּҰ�!
	//���� �迭 : ����ð��� �Ҵ��ϴ� �迭
	int size = 0;
	printf("�迭�� ũ�� : ");
	scanf("%d", &size);

	//int *p = (int*)malloc(sizeof(int)*size);//40byte�� heap�޸𸮿� �Ҵ�
	//printf("size:%d\n", _msize(p));
	
	//calloc : �Ҵ� �� 0���� �ʱ�ȭ
	int *p = (int*)calloc(size,	//����� ����
						sizeof(int));//����� ũ��

	printf("%d\n", _msize(p));
	for (int i = 0; i < _msize(p) / sizeof(int); i++) {
		printf("%d", p[i]);
	}
	puts("");
	//2�������
	int *newP = (int*)calloc(_msize(p)/sizeof(int)*2, sizeof(int));
	
	memcpy(newP, p, _msize(p));//2��� ����
	free(p);


	for (int i=0; i < _msize(newP) / sizeof(int); i++) {
		printf("%d -", newP[i]);
	}
	puts("");

	//realloc : ���Ҵ� �Լ�
	newP = (int*)realloc(newP, _msize(newP) * 2);
	for (int i = 0; i < _msize(newP) / sizeof(int); i++) {
		printf("%d -", newP[i]);
	}

	free(newP);

	return 0;
}
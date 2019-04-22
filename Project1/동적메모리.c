#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <memory.h>
//=============================================================================
//동적 메모리 생성 방법
//new-->malloc 함수
//=============================================================================
//heap에 메모리를 할당하는 함수
//=============================================================================
//-malloc memory allocation
//-calloc
//-realloc
//=============================================================================
//-free
//=============================================================================






int main(void) {
	//malloc(할당할 메모리의 크기)
	//리턴 : 할당받은 메모리의 시작위치의 주소값!
	//동적 배열 : 실행시간에 할당하는 배열
	int size = 0;
	printf("배열의 크기 : ");
	scanf("%d", &size);

	//int *p = (int*)malloc(sizeof(int)*size);//40byte를 heap메모리에 할당
	//printf("size:%d\n", _msize(p));
	
	//calloc : 할당 후 0으로 초기화
	int *p = (int*)calloc(size,	//요소의 갯수
						sizeof(int));//요소의 크기

	printf("%d\n", _msize(p));
	for (int i = 0; i < _msize(p) / sizeof(int); i++) {
		printf("%d", p[i]);
	}
	puts("");
	//2배로증가
	int *newP = (int*)calloc(_msize(p)/sizeof(int)*2, sizeof(int));
	
	memcpy(newP, p, _msize(p));//2배로 증가
	free(p);


	for (int i=0; i < _msize(newP) / sizeof(int); i++) {
		printf("%d -", newP[i]);
	}
	puts("");

	//realloc : 재할당 함수
	newP = (int*)realloc(newP, _msize(newP) * 2);
	for (int i = 0; i < _msize(newP) / sizeof(int); i++) {
		printf("%d -", newP[i]);
	}

	free(newP);

	return 0;
}
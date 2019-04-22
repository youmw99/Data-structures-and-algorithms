//=============================================================
// 제한된 선형 자료구조
//=============================================================
// ->stack
// - 후입선출(LIFO:last in first out)
// - 마지막에 들어온 데이터가 가장 먼저 나가는 구조
//  ex)시스템 구현(함수)
// main실행-printf실행 시 마지막으로 꺼지는 함수는 printf
// ->queue
// - 선입선출(FIFO:first in first out)
//=============================================================
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX 5

int buf[MAX] = { 0 };
int top = -1;

void push(int data) {
	if (top >= MAX - 1) {
		printf("Stack OverFlow!!");
	}
	else {
		buf[++top] = data;
	}
}
void pop(int data) {
	if (top <= -1) {
		printf("Under Flow!!");
	}
	else {
		top--;
	}
}
int main(void) {
	push(10);
	printf("top : %d\n", buf[top]);
	push(20);
	printf("top : %d\n", buf[top]);
	push(30);
	printf("top : %d\n", buf[top]);
	push(40);
	printf("top : %d\n", buf[top]);
	push(10);
	printf("top : %d\n", buf[top]);
	push(10);
	printf("top : %d\n", buf[top]);
}
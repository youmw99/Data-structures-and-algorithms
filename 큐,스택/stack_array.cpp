//=============================================================
// ���ѵ� ���� �ڷᱸ��
//=============================================================
// ->stack
// - ���Լ���(LIFO:last in first out)
// - �������� ���� �����Ͱ� ���� ���� ������ ����
//  ex)�ý��� ����(�Լ�)
// main����-printf���� �� ���������� ������ �Լ��� printf
// ->queue
// - ���Լ���(FIFO:first in first out)
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
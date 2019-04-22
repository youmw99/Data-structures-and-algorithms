//=========================================================================
// queue
// -->선입선출(FIFO)
// --> 입구와 출구가 반대에 위치
// --> [][][][][3][2][1]-->
//=========================================================================
// 
//=========================================================================

#include <stdio.h>
#include <malloc.h>
#define MAX_QUEUE 5

int buf[MAX_QUEUE] = { 0 };
int front, rear;

void push(int data) {
	if (rear+1== MAX_QUEUE) {
		printf("OverFlow!!");
		rear = (rear + 1) % MAX_QUEUE;
	}
	else {
		buf[rear++] = data;
	}
	return;
}
void pop() {
	int data;
	if (front ==rear) {
		printf("UnderFlow!!");
	}
	else {
		data = buf[front];
		front = (front + 1) % MAX_QUEUE;
	}
	return;
}

void main() {
	front = 0;
	rear = 0;

	push(10);
	printf("front: %d rear : %d\n", buf[front], rear);
	pop();
	push(20);
	printf("front: %d rear : %d\n", buf[front], rear);
	pop();
	push(30);
	printf("front: %d rear : %d\n", buf[front], rear);
	pop();
	push(40);
	pop();
	printf("front: %d rear : %d\n", buf[front], rear);
	push(50);
	pop();
	printf("front: %d rear : %d\n", buf[front], rear);
	push(50);
	printf("front: %d rear : %d\n", buf[front], rear);
	pop();
	push(50);
	printf("front: %d rear : %d\n", buf[front], rear);
	return;
}
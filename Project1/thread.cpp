#include <windows.h>
#include <stdio.h>

//������ �Լ�
LPVOID WorkThread(LPVOID) {
	while (1) {
		printf("Work Thread ~~~~~~~");
	}

	return 0;
}

LPVOID GGUThread(LPVOID) {
	while (1) {
		printf("GGU Thread ~~~~~~~");
	}

	return 0;
}

int main(void) {
	HANDLE thread1 = CreateThread(NULL,//���ȼӼ�
									0,//���ػ�����
								(LPTHREAD_START_ROUTINE)WorkThread,
									NULL,//������ �Լ��� �Ѱ��� �Ű�����
									0,	//���� ���� :0����
									NULL);//������ ID
	HANDLE thread2 = CreateThread(NULL,//���ȼӼ�
		0,//���ػ�����
		(LPTHREAD_START_ROUTINE)GGUThread,
		NULL,//������ �Լ��� �Ѱ��� �Ű�����
		0,	//���� ���� :0����
		NULL);//������ ID
	while (1) {
		puts("Main Thread ~~~~~~");
	}

	return 0;
}
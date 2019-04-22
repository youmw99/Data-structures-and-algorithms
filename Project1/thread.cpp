#include <windows.h>
#include <stdio.h>

//쓰레드 함수
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
	HANDLE thread1 = CreateThread(NULL,//보안속성
									0,//스텍사이즈
								(LPTHREAD_START_ROUTINE)WorkThread,
									NULL,//스레드 함수로 넘겨줄 매개변수
									0,	//시작 상태 :0실행
									NULL);//스레드 ID
	HANDLE thread2 = CreateThread(NULL,//보안속성
		0,//스텍사이즈
		(LPTHREAD_START_ROUTINE)GGUThread,
		NULL,//스레드 함수로 넘겨줄 매개변수
		0,	//시작 상태 :0실행
		NULL);//스레드 ID
	while (1) {
		puts("Main Thread ~~~~~~");
	}

	return 0;
}
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>


#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)

LPVOID SendThread(LPVOID p) {
	SOCKET ClientSocket = (SOCKET)p;
	char buf[32];
	while (1) {
		printf("[send] : ");
		gets_s(buf);
		send(ClientSocket, buf, 32, 0);
	}

	return NULL;
}
LPVOID ReceiveThread(LPVOID p) {
	SOCKET ClientSocket = (SOCKET)p;
	char buf[32] = { 0 };
	while (1) {
		recv(ClientSocket, buf, 32, 0);
		printf("[recv] : %s", buf);
	}
	return NULL;
}
int main(void) {
	WSADATA wsa;
	//winsock dll 로딩
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		puts("WSAStartup() error!!");
		return 0;
	}
	//====================================================================
	//socket 생성(핸드폰 단말기)
	SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//-->서버에서 접속을 대기할 소켓
	if (ListenSocket == INVALID_SOCKET) {
		puts("socket() error!");
		return 0;
	}
	//소켓 핸들 확인
	printf("ListenSocket: %d\n", ListenSocket);

	//주소 구조체(유심)
	//-->통신에 필요한 주소정보를 갖는 구조체
	SOCKADDR_IN ServerAddr;
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(8000);
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//socket(핸드폰)+sockaddr(유심)
	//socket과 구조체를 연결!
	if (bind(ListenSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR) {
		puts("bind()error!");
		return 0;
	}
	//접속 대기 상태
	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
		puts("Listen error!");
		return 0;
	}
	//접속처리
	SOCKADDR_IN ClientAddr;//접속한 클라이언트의 주소
	int len = sizeof(ClientAddr);
	//접속한 클라이언트의 소켓을 리턴
	SOCKET ClientSocket =
		accept(ListenSocket,//대기소켓
		(SOCKADDR*)&ClientAddr,//클라이언트의 주소값을 가져옴
			&len);//주소의 크기
	puts("대화를 시작합니다.");

	HANDLE thread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SendThread, (LPVOID) ClientSocket, 0, NULL);
	HANDLE thread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ReceiveThread, (LPVOID)ClientSocket, 0, NULL);

	WaitForSingleObject(thread1, INFINITE);
	WaitForSingleObject(thread2, INFINITE);
	WSACleanup();
}
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
	//winsock dll �ε�
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		puts("WSAStartup() error!!");
		return 0;
	}
	//====================================================================
	//socket ����(�ڵ��� �ܸ���)
	SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//-->�������� ������ ����� ����
	if (ListenSocket == INVALID_SOCKET) {
		puts("socket() error!");
		return 0;
	}
	//���� �ڵ� Ȯ��
	printf("ListenSocket: %d\n", ListenSocket);

	//�ּ� ����ü(����)
	//-->��ſ� �ʿ��� �ּ������� ���� ����ü
	SOCKADDR_IN ServerAddr;
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(8000);
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	//socket(�ڵ���)+sockaddr(����)
	//socket�� ����ü�� ����!
	if (bind(ListenSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR) {
		puts("bind()error!");
		return 0;
	}
	//���� ��� ����
	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR) {
		puts("Listen error!");
		return 0;
	}
	//����ó��
	SOCKADDR_IN ClientAddr;//������ Ŭ���̾�Ʈ�� �ּ�
	int len = sizeof(ClientAddr);
	//������ Ŭ���̾�Ʈ�� ������ ����
	SOCKET ClientSocket =
		accept(ListenSocket,//������
		(SOCKADDR*)&ClientAddr,//Ŭ���̾�Ʈ�� �ּҰ��� ������
			&len);//�ּ��� ũ��
	puts("��ȭ�� �����մϴ�.");

	HANDLE thread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)SendThread, (LPVOID) ClientSocket, 0, NULL);
	HANDLE thread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ReceiveThread, (LPVOID)ClientSocket, 0, NULL);

	WaitForSingleObject(thread1, INFINITE);
	WaitForSingleObject(thread2, INFINITE);
	WSACleanup();
}
#include <winsock2.h>
#include <stdio.h>


#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
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
	if (ClientSocket == INVALID_SOCKET) {
		puts("accept() error!");
		return 0;
	}
	printf("ClientSocket : %d\n", ClientSocket);

	//
	printf("[ %s ]: %d", inet_ntoa(ClientAddr.sin_addr)//IP����
		, ClientAddr.sin_port);//port����

	//�����ϸ� ȯ���޽����� Ŭ���̾�Ʈ���� �����ϴ� ����
	//������ ����
	char msg[32] = { "������ ȯ���մϴ�." };

	send(ClientSocket, msg, 32, 0);
	while (1) {
		recv(ClientSocket, msg, 32, 0);
		printf("[recv msg] %s\n", msg);
		if (strcmp(msg, "X") == 0) {
			break;
		}
		send(ClientSocket, msg, 32, 0);
	}
	//====================================================================
	WSACleanup();//winsock dll ��ε�
	return 0;
}
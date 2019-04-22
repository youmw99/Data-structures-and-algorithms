#include <winsock2.h>
#include <stdio.h>


#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)

#define MAX_SOCKET 16
//Ŭ���̾�Ʈ ���� ����ü
struct SOCKET_INFO {
	char nickname[32];
	SOCKET ClientSocket;
	SOCKADDR_IN ClientAddr;
	int AddrLen;
};


int main(void) {

	//Ŭ���̾�Ʈ ������ �迭
	SOCKET_INFO SockList[MAX_SOCKET];
	int count = 0;

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
	while (1) {
		if (count < MAX_SOCKET - 1) {
			SockList[count].AddrLen = sizeof(SockList[count].ClientAddr);
			SockList[count].ClientSocket =
				accept(ListenSocket,//������
				(SOCKADDR*)&SockList[count].ClientAddr,//Ŭ���̾�Ʈ�� �ּҰ��� ������
					&SockList[count].AddrLen);//�ּ��� ũ��
			printf("[%s]: %d����\n", inet_ntoa(SockList[count].ClientAddr.sin_addr));

			recv(SockList[count].ClientSocket, SockList[count].nickname,32,0);

			/*char buf[32] = "";
			wsprintf(buf, "[%s] �� ����", inet_ntoa(SockList[count].ClientAddr.sin_addr));
			*/
			strcat(SockList[count].nickname, " �� ����");
			for (int i = 0; i < count; i++) {

				send(SockList[i].ClientSocket,SockList[count].nickname,32,0);
			}
			count++;
		}
		
	}
	

}
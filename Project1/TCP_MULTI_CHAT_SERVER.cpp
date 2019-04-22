#include <winsock2.h> //  socket API ��� !!  
#include <stdio.h>

// ws2_32.lib �߰� 
#pragma comment(lib,"ws2_32.lib")
#pragma warning( disable : 4996 )

#define MAX_SOCKET 16
//Ŭ���̾�Ʈ ���� ����ü !! 
struct SOCKET_INFO
{
	char nickname[32];
	SOCKET ClientSocket;
	SOCKADDR_IN ClientAddr;
	int AddrLen;
};

// Ŭ���̾�Ʈ ������ �迭 !! 
SOCKET_INFO SockList[MAX_SOCKET];
int count = 0;

// Thread����ȭ !! 
// --> �������� �����尡 �����ڿ��� �����Ͽ� ����ϴ� ���
// --> �Ӱ迵���� �����ؼ� �����ڿ��� ���� ��ȣ�� �����ؾ� �Ѵ� !! 
CRITICAL_SECTION cs;


void RemoveSocket(SOCKET ClientSocket) {
	for (int i = 0; i < count; i++) {
		if (SockList[i].ClientSocket = ClientSocket) {
			for (int j = i; j < count; j++) {
				SockList[i].ClientSocket = SockList[i + 1].ClientSocket;
				SockList[i].ClientAddr = SockList[i + 1].ClientSocket;
				SockList[i].AddrLen = SockList[i + 1].ClientSocket;
			}
		}
		count--;
		break;
	}
	return;
}



//Echo Server Thread�Լ� 
DWORD EchoThread(LPVOID p)
{
	SOCKET ClientSocket = (SOCKET)p;

	char buf[32] = "";
	while (1)
	{
		int recvbyte = 0;
		recvbyte = recv(ClientSocket, buf, 32, 0);
		recv(ClientSocket, buf, 32, 0);
		if (recvbyte == 0) {
			break;
		}
		printf("[msg][%d byte] : %s\n", recvbyte,buf);

		EnterCriticalSection(&cs);
		for (int i = 0; i < count; i++)
		{
			if (ClientSocket != SockList[i].ClientSocket)
			{
				send(SockList[i].ClientSocket, buf, 32, 0);
			}
		}
		LeaveCriticalSection(&cs);
	}
	RemoveSocket(ClientSocket);
	return 0;
}


// socket �⺻ �ڵ� 
void main()
{
	InitializeCriticalSection(&cs);

	WSADATA wsa;

	// 1.  winsock dll �ε� !! 
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		puts("WSAStartup() error !!");
		return;
	}
	//2. socket ���� ( �ڵ��� �ܸ���)
	// --> �������� ������ ����� ���� !! 
	SOCKET ListenSocket =
		socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ListenSocket == INVALID_SOCKET)
	{
		puts("socket() error !!");
		return;
	}
	// ���� �ڵ� Ȯ�� !! 
	printf("ListenSocket: %d\n", ListenSocket);

	//2. �ּ� ����ü ( ���� ) 
	// --> ��ſ� �ʿ��� �ּ������� ���� ����ü !! 
	SOCKADDR_IN ServerAddr;
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(8000);
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// socket(�ڵ���) + sockaddr(����)  
	// socket�� �ּ� ����ü�� ���� !! 
	if (bind(ListenSocket,
		(SOCKADDR*)&ServerAddr,
		sizeof(ServerAddr)) == SOCKET_ERROR)
	{
		puts("bind() error !!");
		return;

	}
	// ���� ��� ���� !! 
	if (listen(ListenSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		puts("Listen Error !! ");
		return;
	}
	//  ���� ó�� !! 
	SOCKADDR_IN ClientAddr; // ������ Ŭ���̾�Ʈ�� �ּ����� !! 
	int len = sizeof(ClientAddr);
	// ������ Ŭ���̾�Ʈ�� ������ ���� !! 

	while (1)
	{
		if (count < MAX_SOCKET - 1)
		{
			SockList[count].AddrLen = sizeof(SockList[count].ClientAddr);


			// �Ӱ迵�� ���� !! 

			SockList[count].ClientSocket =
				accept(ListenSocket,    //��� ���� 
				(SOCKADDR*)&SockList[count].ClientAddr, // Ŭ���̾�Ʈ�� �ּҰ��� ������ 
					&SockList[count].AddrLen); // �ּ��� ũ�� !! 
				//=================================================
			// �Ӱ� ������ ���� ���� !! 

			printf("[ %s ]: %d ����\n",
				inet_ntoa(SockList[count].ClientAddr.sin_addr), //IP
				SockList[count].ClientAddr.sin_port);

			// ���� ���� ���� ���� !! 
			// --> �������� �����ؼ� ECHO ����� �����ϴ� ���� !!
			// --> Ŭ���̾�Ʈ�� �����ϸ� Ŭ���̾�Ʈ�� ���� ���� ������ ����
			CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)EchoThread,
				(LPVOID)SockList[count].ClientSocket, 0, NULL);

			EnterCriticalSection(&cs);
			count++;
			LeaveCriticalSection(&cs);
		}

	}

	//=================================================
	// winsock dll ��ε� !! 
	WSACleanup();

}
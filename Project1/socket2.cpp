#include <winsock2.h>
#include <stdio.h>


#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
int main(void) {
	WSADATA wsa;
	//winsock dll �ε�
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0) {
		puts("WSAStartup() error!!");
		return 0;
	}
	//====================================================================
	//wsa�� Ȱ���� winsock���� Ȯ��
	printf("%d\n", wsa.wVersion);
	printf("%d\n", wsa.wHighVersion);
	printf("%d\n", wsa.iMaxSockets);
	printf("%s\n", wsa.szDescription);


	//====================================================================
	WSACleanup();//winsock dll ��ε�
	return 0;
}
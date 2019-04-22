#include <winsock2.h>
#include <stdio.h>


#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)
int main(void) {
	WSADATA wsa;
	//winsock dll 로딩
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0) {
		puts("WSAStartup() error!!");
		return 0;
	}
	//====================================================================
	//wsa를 활용한 winsock정보 확인
	printf("%d\n", wsa.wVersion);
	printf("%d\n", wsa.wHighVersion);
	printf("%d\n", wsa.iMaxSockets);
	printf("%s\n", wsa.szDescription);


	//====================================================================
	WSACleanup();//winsock dll 언로딩
	return 0;
}
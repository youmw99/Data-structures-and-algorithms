#include <winsock2.h>
#include <stdio.h>


#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)

#define MAX_SOCKET 16
//클라이언트 정보 구조체
struct SOCKET_INFO {
	char nickname[32];
	SOCKET ClientSocket;
	SOCKADDR_IN ClientAddr;
	int AddrLen;
};


int main(void) {

	//클라이언트 소켓의 배열
	SOCKET_INFO SockList[MAX_SOCKET];
	int count = 0;

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
	while (1) {
		if (count < MAX_SOCKET - 1) {
			SockList[count].AddrLen = sizeof(SockList[count].ClientAddr);
			SockList[count].ClientSocket =
				accept(ListenSocket,//대기소켓
				(SOCKADDR*)&SockList[count].ClientAddr,//클라이언트의 주소값을 가져옴
					&SockList[count].AddrLen);//주소의 크기
			printf("[%s]: %d접속\n", inet_ntoa(SockList[count].ClientAddr.sin_addr));

			recv(SockList[count].ClientSocket, SockList[count].nickname,32,0);

			/*char buf[32] = "";
			wsprintf(buf, "[%s] 님 입장", inet_ntoa(SockList[count].ClientAddr.sin_addr));
			*/
			strcat(SockList[count].nickname, " 님 입장");
			for (int i = 0; i < count; i++) {

				send(SockList[i].ClientSocket,SockList[count].nickname,32,0);
			}
			count++;
		}
		
	}
	

}
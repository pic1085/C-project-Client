// 기초프로젝트 1
// 11분반 11팀
// 팀원 : 박인철 김동휘 윤성재 Xuân Tùng 
#include "create_file.h"
#include "filelist.h"
#include "list_directory_file.h"
#include "login.h"
#include "main_interface.h"
#include "recv_download.h"
#include "rmsg.h"
#include "send_download.h"
#include "server.h"
#include "smsg.h"
#include "user_fd.h"
#include "user_interface.h"
#include "user_membership.h"

volatile int logincount; // 로그인을 성공한지 알아보기위한 변수 
char user_ID[BUF_SIZE] = ""; // 로그인시 유저의 ID를 저장함
volatile int loginfailecount; // 로그인 실패를 카운트함 
// 로그인 실패횟수를 for문을 사용하려 했으나 오류로 인해서 전역변수선언 후 카운트를 증가하는 방식으로 바꿨습니다.

int main() {
	SetConsoleOutputCP(CP_UTF8); // 파일 깨짐 현상이 있어서 추가하였습니다. 
	WSADATA wsa;
	SOCKET srsock;
	SOCKADDR_IN serAddr;
	HANDLE SThread, RThread; // 보내는 쓰레드와 받는 스레드 생성

	char serIP[100] = "172.20.10.4"; 
	int PortNum = 8080;

	//printf("Please Input Server IP : "); // 연결할 서버의 주소 입력
	//scanf("%s", serIP);

	//printf("Please Input PortNum : "); // 연결할 포트번호 입력
	//scanf("%d", &PortNum);

	/*getchar();*/

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) { //윈속 라이브러리 초기화
		printf("WSAStartup error\n"); // 실패시 에러 반환
	}

	srsock = socket(PF_INET, SOCK_STREAM, 0); // 소켓 생성 .. 보내기와 받기할 소켓 
	if (srsock < 0) {
		printf("srsock error\n"); // 생성 실패시 에러반환
	}

	memset(&serAddr, 0, sizeof(serAddr)); // 주소 초기화
	serAddr.sin_family = AF_INET; // IPv4 사용
	serAddr.sin_port = htons(PortNum); // 입력한 포트값 대입
	serAddr.sin_addr.s_addr = inet_addr(serIP); // 입력한 서버의 IP주소 대입 inet_addr을 사용하여 바이트 순서로 반환

	if (connect(srsock, (SOCKADDR*)&serAddr, sizeof(serAddr)) != 0) { // 서버에 연결 요청 요청할 소켓, 서버의 주소, 구조체의 크기 대입
		printf("connect error\n"); // 실패시 에러 반환
	}
	else 
		printf("connect SUCCESS\n"); // 성공시 성공 메시지 출력

	SThread = (HANDLE)_beginthreadex(NULL, 0, Smsg, (void*)&srsock, 0, NULL); // send 쓰레드 생성
	if (SThread == NULL)  // 생성 실패시  
		printf("SThread create error\n"); // 에러 반환

	RThread = (HANDLE)_beginthreadex(NULL, 0, Rmsg, (void*)&srsock, 0, NULL); // recv 쓰레드 생성
	if (RThread == NULL)  // 생성 실패시 
		printf("RThread create error\n"); // 에러 반환

	WaitForSingleObject(SThread, INFINITE); 
	WaitForSingleObject(RThread, INFINITE);

	closesocket(srsock); // 소켓 종료
	WSACleanup();

	return 0;
}

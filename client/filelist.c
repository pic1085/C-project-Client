#include "filelist.h"

void filelist(SOCKET srsock) { // 해당 유저의 파일 목록을 보기 위함
	char sendmsg[BUF_SIZE] = ""; // 버퍼 초기화 
	char sendname[BUF_SIZE] = ""; // 버퍼 초기화

	printf("==== Input User Name ====\n"); // 이름을 입력받음
	gets_s(sendname, sizeof(sendname)); // sendname에 값을 저장
	sprintf(sendmsg, "%s", sendname); // sendmsg에 저장
	send(srsock, sendmsg, strlen(sendmsg), 0); // 서버에 전송
}
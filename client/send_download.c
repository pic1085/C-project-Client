#include "send_download.h"

void sendDownload(SOCKET srsock) { // 파일 다운로드 송신 함수 
	char file_name[BUF_SIZE]; // 버퍼 초기화
	char buffer[BUF_SIZE] = ""; // 버퍼 초기화 
	char dir_name[BUF_SIZE] = ""; // 버퍼 초기화

	printf("Input Directory Name : "); // 사용자로부터 디렉토리 이릅을 입력
	fgets(dir_name, BUF_SIZE, stdin);// dir_name에 입력 값을 저장
	dir_name[strcspn(dir_name, "\n")] = 0; // 줄바꿈 문자 제거

	printf("Input Download File Name: "); // 사용자로부터 다운로드할 파일명 입력
	fgets(file_name, BUF_SIZE, stdin); // file_name에 입력 값을 저장
	file_name[strcspn(file_name, "\n")] = 0; // 줄바꿈 문자 제거

	sprintf(buffer, "%s %s", file_name, dir_name); // 버퍼에 파일이름과 유저의ID를 대입
	send(srsock, buffer, strlen(buffer), 0); // 서버로 전송
}
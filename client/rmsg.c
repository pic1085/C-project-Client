#include "rmsg.h"
#include "user_fd.h"
#include "recv_download.h"

unsigned _stdcall Rmsg(void* arg) {
    SOCKET srsock = *((SOCKET*)arg);
    char buffer[BUF_SIZE] = "";  // 버퍼 초기화
    int string = 0; // 문자열 길이 

    while (1) {
        string = recv(srsock, buffer, BUF_SIZE - 1, 0); // buffer에 값을 받음 
        if (string == -1) { // 문자를 받지 못했을 경우
            printf("Receiving Fails\n"); // 에러를 출력
            return -1;
        }
        buffer[string] = '\0'; // 개행문자를 추가하여 문장으로 만듬
        if (!strcmp(buffer, "exit")) { // exit라면 프로그램 종료
            printf("Server => Thank you for using our service\n"); // 종료 메시지 출력
            closesocket(srsock); // 소켓 종료
            exit(0);
        }
        else if (!strcmp(buffer, "Login SUCCESS\n")) { // \n 까지 넣어줘야 제대로 읽어드림
            printf("Server => %s", buffer); // buffer의 메시지 출력
            logincount += 1; // 로그인을 알아보기 위해 1을 늘려줌
            UserFD(user_ID); // 로그인 성공시 해당 유저의 디렉토리 생성
        }
        else if (!strcmp(buffer, "Login Size Exceeded\n") || !strcmp(buffer, "Login Failed Try Again\n")) { // 로그인 실패 문자일 시 
            printf("Server => %s", buffer); // buffer에 값을 출력
            loginfailecount += 1; // 로그인 실패 카운트 +1 증가 
            printf("Login Counts : %d\n", loginfailecount); // 실패 카운트 출력
            if (loginfailecount == 3) { // 카운트가 3회라면
                printf("Login Failed\n"); // 로그인 실패 출력
                closesocket(srsock); // 소켓 종료
                exit(0);
            }
        }
        else if (!strcmp(buffer, "Check The Path")) {
            recvDownload(srsock);
        }
        else if (!strcmp(buffer, "\tFile list\t\n") || !strcmp(buffer, "\tUser list\t\n")) {
            printf("\n=========================\n");
            printf("%s", buffer);
            printf("=========================\n");
        }
        else {
            printf("Server => %s\n", buffer); // 서버가 보낸 문장 출력
        }
        strcpy(buffer, ""); // 버퍼 초기화
    }
    return 0;
}

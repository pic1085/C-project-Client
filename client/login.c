#include "login.h"

void login(SOCKET srsock) {
    char userID[BUF_SIZE] = ""; // 버퍼 초기화
    char userPW[BUF_SIZE] = ""; // 버퍼 초기화
    char buffer[BUF_SIZE] = ""; // 버퍼 초기화

    Sleep(100); // 출력되는 시간을 늦춤 (안할시에 인터페이스와의 충돌이 일어남)

    printf("==== INPUT ID ====\n"); // 아이디 입력
    fgets(userID, BUF_SIZE, stdin); // userID에 입력받은 값을 저장함
    userID[strcspn(userID, "\n")] = 0; // 개행문자 제거

    printf("==== INPUT PW ====\n"); // 패스워드 입력
    fgets(userPW, BUF_SIZE, stdin); // userPW에 입력받은 값을 저장 
    userPW[strcspn(userPW, "\n")] = 0; // 개행문자 제거

    sprintf(buffer, "%s %s", userID, userPW); // 버퍼에 ID와 PW를 저장함
    send(srsock, buffer, strlen(buffer), 0); // 서버에 값 전달

    strcpy(user_ID, userID); // 전역변수 user_ID에 로그인한 유저의 ID 대입
}

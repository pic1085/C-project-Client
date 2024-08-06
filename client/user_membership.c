#include "user_membership.h"

void UserMembership(SOCKET srsock) {  // 회원가입 함수
    char userID[BUF_SIZE] = ""; // 버퍼 초기화
    char userPW[BUF_SIZE] = ""; // 버퍼 초기화
    char buffer[BUF_SIZE] = ""; // 버퍼 초기화
    printf("(ID 10자, PW 20자 까지 입력가능)\n"); // 크기의 제한을 알려줌

    printf("==== INPUT ID ====\n"); // 아이디 입력받기
    scanf("%s", userID); // userID에 입력받은 값 저장

    getchar(); // 개행문자 제거

    printf("==== INPUT PW ====\n"); // 비밀번호 입력받기
    scanf("%s", userPW); // userPW에 입력받은 값 저장

    getchar(); // 개행문자 제거

    sprintf(buffer, "%s %s", userID, userPW); // 버퍼에 ID와 PW 저장
    send(srsock, buffer, strlen(buffer), 0); // 서버에 전달

    return;
}

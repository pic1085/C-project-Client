#include "smsg.h"
#include "user_interface.h"
#include "user_membership.h"
#include "login.h"
#include "create_file.h"
#include "send_download.h"
#include "filelist.h"

unsigned _stdcall Smsg(void* arg) {
    SOCKET srsock = *((SOCKET*)arg);

    while (1) {
        char buffer[BUF_SIZE] = "";

        Sleep(100); // 값이 잘 출력 될 수 있도록 대기시간을 가짐
        printf("\n");
        if (logincount) { // 로그인 성공시 
            Main_Interface(); // 메인 인터페이스 출력
        }
        else {
            User_Interface(); // 로그인 인터페이스 출력
        }
        printf("Select Menu : "); // 수행할 기능을 입력받음
        gets_s(buffer, sizeof(buffer)); // buffer에 값을 저장

        if (!strcmp(buffer, "exit")) { // exit를 입력할 시 
            send(srsock, "exit", strlen("exit"), 0); // 서버에 exit를 보냄
        }
        else if (!strcmp(buffer, "join") || !strcmp(buffer, "2")) { // join or 2 를 입력할시 
            send(srsock, buffer, strlen(buffer), 0); // 서버에 전달 
            system("cls"); // 콘솔 초기화 
            if (logincount) {  // 로그인을 이미 한 상태일 시 
                printf("Already Login\n"); // 이미 로그인 하였다고 출력
            }
            else { // 로그인을 안한 상태일 시 
                UserMembership(srsock); // 로그인 기능 수행
            }
        }
        else if (!strcmp(buffer, "login") || !strcmp(buffer, "1")) { // login or 1 을 입력할 시
            send(srsock, buffer, strlen(buffer), 0); // 서버에 전달 
            system("cls"); // 콘솔 초기화 
            if (logincount) { // 로그인을 이미 한 상태라면 
                printf("Already Login\n"); // 이미 로그인 하였다고 출력
            }
            else { // 로그인을 안한 상태일 시 
                login(srsock); // 로그인 기능 수행
            }
        }
        else if (!strcmp(buffer, "upload")) { // upload를 입력할 시 
            system("cls"); // 콘솔 초기화
            if (logincount) { // 로그인 성공시에만 기능을 수행
                send(srsock, buffer, strlen(buffer), 0); // 서버에 전달 
                create_file(srsock); // 파일 업로드 기능 수행
            }
            else { // 로그인을 안한 상태일 시 
                printf("Please Try Again\n"); // 다시 입력하라고 출력
            }
        }
        else if (!strcmp(buffer, "download")) { // download 입력할 시 
            system("cls"); // 콘솔 초기화
            if (logincount) { // 로그인 성공시에만 기능을 수행
                send(srsock, buffer, strlen(buffer), 0); // 서버에 전달 
                sendDownload(srsock);
            }
            else { // 로그인을 안한 상태일 시 
                printf("Please Try Again\n"); ;// 다시 입력하라고 출력
            }
        }
        else if (!strcmp(buffer, "userlist")) { // userlist를 입력할 시 
            system("cls"); // 콘솔 초기화 
            if (logincount) {
                send(srsock, buffer, strlen(buffer), 0); // 서버에 전달 
            }
            else {
                printf("Please Try Again\n"); // 다시 입력하라는 문구 출력
            }
        }
        else if (!strcmp(buffer, "filelist")) { // filelist를 입력할 시 
            system("cls"); // 콘솔 초기화

            if (logincount > 0) { // 로그인 성공시 기능 수행
                send(srsock, buffer, strlen(buffer), 0); // 서버에 전달 
                filelist(srsock); // filelist함수 실행
            }
            else {
                printf("Please Try Again\n"); // 다시 입력하라는 문구 출력
            }
        }
        else { // 기능에 해당하는 값을 입력 못했을 시 
            system("cls"); // 콘솔 초기화
            send(srsock, buffer, strlen(buffer), 0); // 서버에 전달 
            printf("Input : %s\n", buffer); // 입력한 값을 출력
            continue; // 계속 진행
        }
    }
    return 0;
}

#ifndef SERVER_H
#define SERVER_H

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")

#include <WinSock2.h>
#include <Windows.h>
#include <process.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <direct.h>
#include <locale.h>
#include <io.h>

#define BUF_SIZE 1024

extern volatile int logincount; // 로그인을 성공한지 알아보기위한 변수 
extern char user_ID[BUF_SIZE]; // 로그인시 유저의 ID를 저장함
extern volatile int loginfailecount;// 로그인 실패를 카운트함 

#endif
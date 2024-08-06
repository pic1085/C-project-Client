#include "user_fd.h"

void UserFD(const char* path) { // 유저별 디렉토리 생성
    if (_access(path, 0) == -1) { // 디렉토리가 없을시 생성
        _mkdir(path);
    }
}

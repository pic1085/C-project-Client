#include "list_directory_file.h"

void list_directory_files(const char* path) {
    struct _finddata_t fileinfo; // 파일 정보 구조체
    char search_path[BUF_SIZE]; // 검색 경로 버퍼

    snprintf(search_path, sizeof(search_path), "%s/*.*", path); // 검색 경로 설정

    intptr_t handle = _findfirst(search_path, &fileinfo); // 첫 번째 파일 검색을 위한 핸들 획득
    if (handle == -1) { // 핸들 획득 실패 시
        printf("No files in directory.\n"); // 디렉토리에 파일이 없음을 출력
        return;
    }
    printf("List of files you have\n"); 
    // 첫 번째 파일을 출력하고, 다음 파일 정보를 가져오는 루프
    while (_findnext(handle, &fileinfo) == 0) {
        if (!(fileinfo.attrib & _A_SUBDIR)) { // 파일인 경우에만 출력
            
            printf("  %s\n", fileinfo.name); // 갖고있는 파일 출력
        }
    }

    _findclose(handle); // 핸들 닫기
}

#include "create_file.h"
#include "list_directory_file.h"

int create_file(SOCKET srsock) {
	char file_name[BUF_SIZE] = "";
	char buffer[BUF_SIZE] = "";
	FILE* file;
	char user_dir[BUF_SIZE];

	snprintf(user_dir, sizeof(user_dir), "./%s", user_ID);
	list_directory_files(user_dir); // 디렉토리의 파일 목록을 출력

	printf("Input File Name: ");
	fgets(file_name, BUF_SIZE, stdin);
	file_name[strcspn(file_name, "\n")] = 0;

	sprintf(buffer, "%s %s", file_name, user_ID);
	send(srsock, buffer, strlen(buffer), 0);

	char file_path[BUF_SIZE] = "";
	sprintf(file_path, "./%s/%s", user_ID, file_name);

	file = fopen(file_path, "rb");
	if (file == NULL) {
		printf("Send File Open Error: %s\n", file_name);
		sprintf(buffer, "NO DATA");
		send(srsock, buffer, strlen(buffer), 0);
		return 0;
	}

	while (!feof(file)) {
		int bytes_read = fread(buffer, 1, BUF_SIZE, file);
		if (bytes_read <= 0)
			break;
		int bytes_sent = send(srsock, buffer, bytes_read, 0);
		if (bytes_sent != bytes_read) {
			printf("File Send Error\n");
			fclose(file);
			return 0;
		}
	}
	fclose(file);
	printf("=== File uploaded successfully ===\n"); // 성공 메시지 추가
	return 1;
}
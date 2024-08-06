#include "recv_download.h"

int recvDownload(SOCKET srsock) {
	char file_name[BUF_SIZE];
	char recvmsg[BUF_SIZE] = "";
	FILE* file;

	int string = recv(srsock, file_name, BUF_SIZE - 1, 0);
	file_name[string] = '\0';
	char file_path[BUF_SIZE] = "";
	snprintf(file_path, BUF_SIZE, "./%s/%s", user_ID, file_name);

	int bytes_received = recv(srsock, recvmsg, BUF_SIZE, 0);
	if (bytes_received <= 0) {
		printf("NO DATA\n");
		return 0;
	}

	if (strcmp(recvmsg, "NO DATA") == 0) {
		printf("No Data\n");
		return 0;
	}

	file = fopen(file_path, "wb");
	if (file == NULL) {
		perror("File Open Error");
		return 0;
	}

	while (1) {
		fwrite(recvmsg, 1, bytes_received, file);
		if (bytes_received != BUF_SIZE) {
			break;
		}

		bytes_received = recv(srsock, recvmsg, BUF_SIZE, 0);
		if (bytes_received <= 0) {
			if (bytes_received == 0) {
				break;
			}
			else {
				perror("recv error");
				fclose(file);
				return 0;
			}
		}

		if (strcmp(recvmsg, "NO DATA") == 0) {
			printf("No Data\n");
			fclose(file);
			return 0;
		}
	}
	printf("=== File downloaded successfully ===\n"); // 성공 메시지 추가
	fclose(file);
	return 1;
}
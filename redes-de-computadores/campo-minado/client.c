#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "common.h"

#define BUFSZ 1024

int main(int argc, char **argv) {
	struct sockaddr_storage storage;
	if (0 != addrparse(argv[1], argv[2], &storage)) {
		exit(EXIT_FAILURE);
	}

	int s;
	s = socket(storage.ss_family, SOCK_STREAM, 0);
	if (s == -1) {
		logexit("socket");
	}
	struct sockaddr *addr = (struct sockaddr *)(&storage);
	if (0 != connect(s, addr, sizeof(storage))) {
		logexit("connect");
	}

	char addrstr[BUFSZ];
	addrtostr(addr, addrstr, BUFSZ);

	Message originalData;
    originalData.type = 2;
    originalData.coordinates[0] = 2;
    originalData.coordinates[1] = 3;

    // Fill in the board with some data
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            originalData.board[i][j] = i * COLS + j;
        }
    }

	send_message(s, &originalData);

	char buffer[sizeof(Message)];
	unsigned total = 0;
	while(1) {
		int count = recv(s, buffer + total, BUFSZ - total, 0);
		if (count == 0) {
			break;
		}
		total += count;
	}
	close(s);

	puts(buffer);

	exit(EXIT_SUCCESS);
}

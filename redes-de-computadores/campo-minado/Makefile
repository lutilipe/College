CC = gcc
CFLAGS = -Wall -I.
BIN_DIR = bin

CLIENT_SRC = client.c common.c
SERVER_SRC = server.c common.c

# List of object files
CLIENT_OBJ = $(CLIENT_SRC:.c=.o)
SERVER_OBJ = $(SERVER_SRC:.c=.o)

# Targets
all: client server

client: $(CLIENT_OBJ)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^

server: $(SERVER_OBJ)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$@ $^

# Compile source files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean rule
clean:
	rm -f $(BIN_DIR)/* *.o

.PHONY: all clean

CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

TARGET = projectileMotion
SRC = projectileMotion.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LDFLAGS)

clean:
	rm -f $(TARGET)

.PHONY: all clean


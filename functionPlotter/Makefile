CC = gcc
CFLAGS = -Wall -Wextra -g

TARGET = functionPlotter
SRC = functionPlotter.c

LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET)


CC      = gcc
CFLAGS  = -O0 -Wall -Wextra -std=c11
TARGET  = sorting_app

SRCS    = src/main.c src/utils.c src/basic_sort.c src/advance_sort.c
OBJS    = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	@echo "Build berhasil -> ./$(TARGET)"

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
	@echo "Cleaned."

.PHONY: all run clean
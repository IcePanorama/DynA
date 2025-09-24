CFLAGS =-std=c99 -Wpedantic -Wextra -Werror -Wall -Wstrict-aliasing=3 -g
CFLAGS += -Wwrite-strings -Wvla -Wcast-align=strict -Wstrict-prototypes
CFLAGS += -Wstringop-overflow=4 -Wshadow -fanalyzer

TARGET = DynATest
SRC_DIR = src
INCL_DIR = include
SRC = $(SRC_DIR)/main.c \
      $(SRC_DIR)/dyna.c
INCL = $(INCL_DIR)/dyna.h

FMT = clang-format
STYLE = GNU
FMT_FLAGS = -style=$(STYLE)

all: format
	$(CC) -c $(CFLAGS) $(SRC) -I$(INCL_DIR)/
	$(CC) -o $(TARGET) *.o

full: clean format all
	valgrind ./$(TARGET)

clean:
	rm -f *.o $(TARGET)

format:
	$(FMT) $(FMT_FLAGS) -i $(SRC) $(INCL)

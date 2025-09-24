CFLAGS =-std=c99 -Wpedantic -Wextra -Werror -Wall -Wstrict-aliasing=3 -g
CFLAGS += -Wwrite-strings -Wvla -Wcast-align=strict -Wstrict-prototypes
CFLAGS += -Wstringop-overflow=4 -Wshadow -fanalyzer

TEST_TARGET = DynATest
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
	$(CC) -o $(TEST_TARGET) *.o

full: clean format all
	valgrind ./$(TEST_TARGET)

clean:
	rm -f *.o $(TEST_TARGET)

format:
	$(FMT) $(FMT_FLAGS) -i $(SRC) $(INCL)

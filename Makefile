CC  := gcc
INC := src
SRC := test
OBJ := build

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%, $(SOURCES))

all: env $(OBJECTS)

env:
	mkdir -p build

$(OBJ)/%: $(SRC)/%.c
	$(CC) -I $(INC) $< -o $@

clean :
	rm -r build
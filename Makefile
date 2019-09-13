EXE = chip8
SRC_DIR = source
OBJ_DIR = build

SRC = $(wildcard $(SRC_DIR)/*.c) \
	  $(wildcard $(SRC_DIR)/linux/*.c)

OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))

CFLAGS += -Wall -Iinclude

$(OBJ_DIR)/%.o: %.c
	@mkdir -p '$(@D)'
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJ_DIR)/$(EXE): $(OBJ)
	$(CC) -o $@ $(CFLAGS) $(OBJ)

.PHONY: clean
clean:
	rm -f $(OBJ) $(OBJ_DIR)/$(EXE)
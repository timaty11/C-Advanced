SRC_DIR := src
OBJ_DIR := obj

BIN := pathfinder
LIB := libmx.a
LIBDIR := libmx/
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC=clang
CPPFLAGS=-Iinc -I libmx/inc -MMD -MP
CFLAGS=-std=c11 -Wall -Wextra -Werror -Wpedantic

all: $(LIB) | $(BIN)

$(LIB):
	$(MAKE) -C $(LIBDIR)

$(BIN): $(OBJ) 
	$(CC) $(LDFLAGS) $^ $(LIBDIR)$(LIB) $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

uninstall: clean
	@$(RM) -f $(BIN) $(LIB)
	$(MAKE) -C $(LIBDIR) uninstall

clean:
	@$(RM) -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBDIR) clean

reinstall: uninstall all


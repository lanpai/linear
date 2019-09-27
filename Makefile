BINARY = linear

BUILD_DIR = build
OBJ_DIR = obj

LIB =

ifeq ($(OS),Windows_NT)
	LIB =
	BINARY := $(BINARY).exe
	RUN_PREFIX = start
endif

output: main.o
	@mkdir -p $(BUILD_DIR)
	cd $(OBJ_DIR); $(CC) -Wall main.o -o ../$(BUILD_DIR)/$(BINARY) $(LIB)

main.o: main.c
	@mkdir -p $(OBJ_DIR)
	cd $(OBJ_DIR); $(CC) -Wall -c ../main.c

run:
	$(RUN_PREFIX) $(BUILD_DIR)/$(BINARY)

clean:
	rm -rf $(OBJ_DIR) $(BUILD_DIR)

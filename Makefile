CC=gcc
.PHONY = clean all debug release

SRCDIR:=src
SRC:=$(wildcard $(SRCDIR)/*.c)

DEBUG_DIR:=debug
DEBUG_CFLAGS:=-Wall -g -O0 -fsanitize=address -s -I./include
DEBUG_OBJ:=$(SRC:$(SRCDIR)/%.c=$(DEBUG_DIR)/obj/%.o)

RELEASE_DIR:=release
RELEASE_CFLAGS:=-Wall -s -I./include
RELEASE_OBJ:=$(SRC:$(SRCDIR)/%.c=$(RELEASE_DIR)/obj/%.o)

all: debug release 

$(DEBUG_OBJ): $(DEBUG_DIR)/obj/%.o : $(SRCDIR)/%.c
	$(CC) $(DEBUG_CFLAGS) -c $< -o $@
	@echo "Built debug objs"

debug: $(DEBUG_OBJ)
	ar rcs $(DEBUG_DIR)/libmosaic.a $(DEBUG_OBJ)

$(RELEASE_OBJ): $(RELEASE_DIR)/obj/%.o : $(SRCDIR)/%.c
	$(CC) $(RELEASE_CFLAGS) -c $< -o $@
	@echo "Build release objs"

release: $(RELEASE_OBJ)
	ar rcs $(RELEASE_DIR)/libmosaic.a $(RELEASE_OBJ)

test: debug src/test/test.c
	$(CC) $(DEBUG_CFLAGS) -o test -Isrc -Ldebug src/test/test.c -lasan -lmosaic -lm 
clean:
	--	rm $(DEBUG_OBJ) debug/libmosaic.a
	--	rm $(RELEASE_OBJ) release/libmosaic.a
	--	rm test


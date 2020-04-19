# ------------------------------------------------
# Generic Makefile
# Author: Eugene Gromadko
# ------------------------------------------------
# TODO: Header dependencies
# ------------------------------------------------
CC 			= gcc
CFLAGS 	= -std=c90 -Wall


INCDIR  = include/
SRCDIR 	= src/
OBJDIR	= obj/
BINDIR	= bin/


SOURCES  = $(wildcard $(SRCDIR)*.c)
INCLUDES = $(wildcard $(INCDIR)*.h)
OBJECTS  = $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SOURCES))


APP_NAME	= military_commisariat
BIN		  	= $(addprefix $(BINDIR), $(APP_NAME))



.PHONY: build
build: directories $(BIN)
directories:
	mkdir -p $(OBJDIR) $(BINDIR)


$(BIN): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@


$(OBJECTS): $(OBJDIR)%.o : $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@



.PHONY: run
run:
	./$(BIN)



.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(BINDIR)



.PHONY: memcheck
memcheck:
	valgrind --leak-check=full $(BIN)

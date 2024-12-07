# Compiler and flags
CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -pedantic

# Directories
SRCDIR = src
INCDIR = include
OBJDIR = obj
LIBDIR = lib


# Library names
LIBRARY = $(LIBDIR)/libwijson.a

# Source and object files
SRC_FILES = $(wildcard $(SRCDIR)/*.c)
OBJ_FILES = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRC_FILES))


# Default target
all: $(LIBRARY)

# Rule to create the static library for your project
$(LIBRARY): $(OBJ_FILES)
	@mkdir -p $(LIBDIR)
	ar rcs $@ $^

# Rule to compile object files
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Ensure obj directory exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Rule to build and run tests
test: $(LIBRARY)
	$(MAKE) -C test


# Clean up
clean:
	rm -rf $(OBJDIR) $(LIBRARY) $(TEST_EXECUTABLES) $(LIBDIR)
	$(MAKE) -C test clean

.PHONY: test clean all

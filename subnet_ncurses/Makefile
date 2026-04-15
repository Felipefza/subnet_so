# Variables
CC = gcc
CFLAGS = -Wall -Iinclude -MMD -O2 -lm -lncurses -lpanel -lmenu
OBJDIR = build
SRCDIR = src
TARGET = $(OBJDIR)/program

# Source and Object Files
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEPS = $(OBJ:.o=.d)

# Default Target
all: $(TARGET)

# Build the Final Executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Pattern Rule for Object Files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

# Include Dependency Files
-include $(DEPS)

# Clean Target
clean:
	rm -r $(OBJDIR)/*.o $(OBJDIR)/*.d $(TARGET)

# Phony Targets
.PHONY: all clean

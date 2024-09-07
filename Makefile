CC = gcc
CFLAGS = -Wall -Wextra -Iinclude/ -I/opt/homebrew/include -L/opt/homebrew/lib -lSDL2
SRCDIR = src
BUILDDIR = build
BINDIR = bin
TARGET = $(BINDIR)/app

SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(BUILDDIR)/%.o, $(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Building project..."
	mkdir -p $(BUILDDIR) $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.c
	@echo "Compiling binary $(TARGET)..."
	$(CC) $(CFLAGS) -c -o $@ $<

run: $(TARGET)
	@echo "Launching executable $(TARGET)..."
	./$(TARGET)
	

clean:
	rm -rf $(BUILDDIR)/*.o $(TARGET)

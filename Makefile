CC = gcc
CFLAGS =
LDFLAGS = -lX11 -lm
OBJFILES = main.o gfx.o
TARGET = main
all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) $(TARGET) *~
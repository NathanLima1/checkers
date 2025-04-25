CC = gcc
CFLAGS = -Wall -O2 -I./src
OBJDIR = obj
LIBDIR = lib

folders = obj
OBJS = $(OBJDIR)/dfs.o $(OBJDIR)/utils.o $(OBJDIR)/graph.o
SRCS = src/main.c

TARGET = tp1

all: $(TARGET)

$(TARGET): $(folders) $(OBJS) $(SRCS)
	$(CC) $(CFLAGS) -o $@ $(SRCS) $(OBJS)

$(folders):
	mkdir -p $(folders)

$(OBJDIR)/dfs.o: src/dfs.c src/dfs.h src/header.h
	$(CC) $(CFLAGS) -c src/dfs.c -o $@

$(OBJDIR)/utils.o: src/utils.c src/utils.h src/header.h
	$(CC) $(CFLAGS) -c src/utils.c -o $@

clean:
	rm -f $(OBJDIR)/*.o $(TARGET)
	rm -r $(folders)

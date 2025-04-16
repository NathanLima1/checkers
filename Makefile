CC = gcc
CFLAGS = -Wall -O2 -I./src
OBJDIR = obj
LIBDIR = lib

OBJS = $(OBJDIR)/dfs.o $(OBJDIR)/utils.o
SRCS = src/checkers.c

TARGET = cluster

all: $(TARGET)

$(TARGET): $(OBJS) $(SRCS)
	$(CC) $(CFLAGS) -o $@ $(SRCS) $(OBJS)

$(OBJDIR)/dfs.o: src/dfs.c src/dfs.h src/header.h
	$(CC) $(CFLAGS) -c src/dfs.c -o $@

$(OBJDIR)/utils.o: src/utils.c src/utils.h src/header.h
	$(CC) $(CFLAGS) -c src/utils.c -o $@

clean:
	rm -f $(OBJDIR)/*.o $(TARGET)

# Variables
COMPILADORC = gcc
FLAGSC = -Wall -ansi -march=core2 -O2 -g
OBJDIR = obj
SRCDIR = src
EXTLIBDIR = lib
OBJS = $(OBJDIR)/utils.o $(OBJDIR)/dfs.o
LINKING = -lsvd -lm
EXECNAME = cluster

ifeq ($(shell getconf LONG_BIT),32)
 LINKDIR = -L $(EXTLIBDIR)/i386
else
 LINKDIR = -L $(EXTLIBDIR)/x86-64
endif

# Compilation rules
$(OBJDIR)/dfs.o : $(SRCDIR)/dfs.c $(SRCDIR)/header.h
	mkdir -p $(OBJDIR)
	$(COMPILADORC) $(FLAGSC) -c $(SRCDIR)/dfs.c -o $(OBJDIR)/dfs.o

$(OBJDIR)/utils.o : $(SRCDIR)/utils.c $(SRCDIR)/header.h
	mkdir -p $(OBJDIR)
	$(COMPILADORC) $(FLAGSC) -c $(SRCDIR)/utils.c -o $(OBJDIR)/utils.o

# Linking
all : $(OBJS)
	$(COMPILADORC) $(FLAGSC) $(OBJS) $(SRCDIR)/checkers.c -o $(EXECNAME) $(LINKDIR) $(LINKING)

clean:
	rm -rf $(OBJDIR) $(EXECNAME)

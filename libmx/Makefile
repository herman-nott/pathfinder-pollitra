LIBNAME = libmx.a

CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic
CC	= clang
OBJDIR = obj
SRCDIR = src
INCDIR = inc

SRC = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRC))

all: $(LIBNAME)

$(LIBNAME): $(OBJS)
	ar rcs $(LIBNAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(SRCDIR)
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I $(INCDIR) -c $< -o $@ 

clean:
	rm -f $(OBJS)
	rm -rf $(OBJDIR)
	rm -f $(LIBNAME)

uninstall: clean
	rm -f $(LIBNAME)

reinstall: uninstall all
 

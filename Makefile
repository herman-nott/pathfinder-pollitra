NAME	= pathfinder

FLGS	= -std=c11 -Wall -Wextra -Werror -Wpedantic
LDFLAGS	= -Llibmx -lmx
CC	= clang

SRCD	= src
INCD	= inc
OBJD	= obj
LIBD 	= libmx
LIBINCD	= $(LIBD)/inc

SRCF	= $(wildcard $(SRCD)/*.c)
OBJF	= $(patsubst $(SRCD)/%.c, $(OBJD)/%.o, $(SRCF))

LIBMX	= $(LIBD)/libmx.a

all: $(NAME)

$(NAME): $(OBJF) $(LIBMX)
	$(CC) $(OBJF) -o $(NAME) $(LDFLAGS)

$(LIBMX):
	$(MAKE) -C $(LIBD) || { echo "Failed to build libmx"; exit 1; }
	
$(OBJD)/%.o: $(SRCD)/%.c | $(OBJD)
	$(CC) $(FLGS) -I $(INCD) -I $(LIBINCD) -c $< -o $@

$(OBJD):
	mkdir -p $(OBJD)

clean:
	@$(MAKE) clean -C $(LIBD)
	rm -rf $(OBJD)
	rm -f $(NAME)

uninstall: clean
	@$(MAKE) uninstall -C $(LIBD)

reinstall: uninstall all

.PHONY: all clean uninstall reinstall

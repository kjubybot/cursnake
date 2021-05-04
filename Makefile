NAME = snake

CC = gcc
RM = rm -rf
LDLIBS = -lcurses
CFLAGS = -MMD -g

OBJ =\
	 main.o\
	 snake.o\
	 game.o

OBJDIR = obj/

all: $(NAME)

$(NAME): $(OBJDIR) $(addprefix $(OBJDIR),$(OBJ))
	$(CC) $(CFLAGS) $(LDLIBS) -o $(NAME) $(addprefix $(OBJDIR),$(OBJ))

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)%.o: %.c
	$(CC) $(CFLAGS) $(LDLIBS) -c -o $@ $<

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

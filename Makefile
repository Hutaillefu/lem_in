PROG = lem-in

LIBFT = ./libft
INCLUDES = ./includes

FLAGS = -Wall -Werror -Wextra

TOOLS_FILES = ./srcs/line_checker.c \
	      ./srcs/mem_tools.c \
	      ./srcs/bit_tools.c \
	      ./srcs/parser.c \
	      ./srcs/pathfinding.c \
		  ./srcs/free_tools.c \
		  ./srcs/free_list_tools.c \
		  ./srcs/getter.c

PROG_FILE = ./srcs/lem_in.c

TOOLS_OBJS = $(TOOLS_FILES:.c=.o)
PROG_OBJ = $(PROG_FILE:.c=.o)

all : $(PROG)

$(PROG): $(TOOLS_OBJS) $(PROG_OBJ)
	make -C $(LIBFT)
	gcc $(FLAGS) -o $(PROG) -I $(INCLUDES) $(TOOLS_OBJS) $(PROG_OBJ) $(LIBFT)/libft.a

%.o : %.c
	gcc $(FLAGS) -o $@ -c $< -I $(INCLUDES)

clean:
	make -C $(LIBFT) clean
	rm -rf $(TOOLS_OBJS)
	rm -rf $(PROG_OBJ)

fclean: clean
	make -C $(LIBFT) fclean
	rm -rf $(PROG)

re: fclean all

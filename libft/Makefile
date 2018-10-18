# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: htaillef <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/09 14:46:26 by htaillef          #+#    #+#              #
#    Updated: 2017/11/10 18:13:09 by htaillef         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

PART1 = ft_memset.c  \
	  	ft_bzero.c   \
	  	ft_memcpy.c  \
	  	ft_memccpy.c \
	  	ft_memmove.c \
	  	ft_memchr.c  \
	  	ft_memcmp.c  \
	  	ft_strlen.c  \
	  	ft_strdup.c  \
	  	ft_strcpy.c  \
		ft_strncpy.c \
		ft_strcat.c  \
		ft_strncat.c \
		ft_strlcat.c \
		ft_strchr.c  \
	  	ft_strrchr.c \
	  	ft_strstr.c  \
	  	ft_strnstr.c \
	 	ft_strcmp.c  \
	  	ft_strncmp.c \
	  	ft_atoi.c    \
	  	ft_isalpha.c \
	  	ft_isdigit.c \
	  	ft_isalnum.c \
	  	ft_isascii.c \
	  	ft_isprint.c \
	  	ft_toupper.c \
	  	ft_tolower.c

PART2 = ft_memalloc.c   \
		ft_memdel.c     \
		ft_strnew.c     \
		ft_strdel.c     \
		ft_strclr.c     \
		ft_striter.c    \
		ft_striteri.c   \
		ft_strmap.c     \
		ft_strmapi.c    \
		ft_strequ.c     \
		ft_strnequ.c    \
		ft_strsub.c     \
		ft_strjoin.c    \
		ft_strtrim.c    \
		ft_putchar_fd.c \
		ft_putchar.c    \
		ft_putstr_fd.c  \
		ft_putstr.c     \
		ft_putendl_fd.c \
		ft_putendl.c    \
		ft_putnbr_fd.c  \
		ft_putnbr.c     \
		ft_itoa.c       \
		ft_strsplit.c

PART3 = ft_lstnew.c    \
		ft_lstdelone.c \
		ft_lstdel.c    \
		ft_lstadd.c    \
		ft_lstpop.c    \
		ft_lstpoplast.c    \
		ft_lstpush.c    \
		ft_lstiter.c   \
		ft_lstmap.c	\
		get_next_line.c \
		ft_lstgetindex.c \
		ft_lstlen.c

FLAGS = -Wall -Wextra -Werror

OBJ1 = $(PART1:.c=.o)
OBJ2 = $(PART2:.c=.o)
OBJ3 = $(PART3:.c=.o)

all : $(NAME)

$(NAME): 
	@gcc $(FLAGS) -c $(PART1) $(PART2) $(PART3)
	ar -rc $(NAME) $(OBJ1) $(OBJ2) $(OBJ3)

%.o : %.c
	@gcc $(FLAGS) -o $@ -c $<

clean:
	@rm -rf $(OBJ1) $(OBJ2) $(OBJ3)

fclean: clean
	rm -rf $(NAME)

re: fclean all

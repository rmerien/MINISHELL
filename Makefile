# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmerien <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/03 15:45:35 by rmerien           #+#    #+#              #
#    Updated: 2019/05/02 09:55:51 by rmerien          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

INCLUDES	=	-I .

CFLAGS		+=	-Wall -Werror -Wextra

SRCS		=	srcs/main.c					\
				srcs/write_prompt.c			\
				srcs/env_manip.c			\
				srcs/env_manip2.c			\
				srcs/parsing.c				\
				srcs/line_split1.c			\
				srcs/free_functions.c		\
				srcs/exe_file.c				\
				srcs/get_line.c				\
				srcs/aux.c					\
				srcs/count_arglen.c			\
				srcs/count_args.c			\
				srcs/fill_args.c			\
				srcs/lib/ft_strcmp.c		\
				srcs/lib/ft_abs.c			\
				srcs/lib/ft_strchr.c		\
				srcs/lib/ft_strjoin.c		\
				srcs/lib/ft_strlen.c		\
				srcs/lib/ft_strdel.c		\
				srcs/lib/ft_strdup.c		\
				srcs/lib/ft_strnew.c		\
				srcs/lib/ft_memalloc.c		\
				srcs/lib/ft_memdel.c		\
				srcs/lib/ft_putendl.c		\
				srcs/lib/ft_atoi.c			\
				srcs/lib/ft_lentoc.c		\
				srcs/lib/ft_strsub.c		\
				srcs/lib/ft_strcat.c		\
				srcs/lib/ft_strcpy.c		\
				srcs/builtin/ft_cd.c		\
				srcs/builtin/ft_echo.c		\
				srcs/builtin/ft_exit.c		\
				srcs/builtin/ft_setenv.c	\
				srcs/builtin/ft_unsetenv.c	\
				srcs/builtin/ft_env.c

OBJS		=	$(SRCS:.c=.o)

all : $(NAME)

%.o : %.c
	@gcc -c $< $(CFLAGS) $(INCLUDES) -o $@

$(NAME) : $(OBJS)
	@gcc $(OBJS) -o $(NAME)
	@echo "Ready"

clean :
	@rm -f $(OBJS)
	@echo "Cleaned"

fclean : clean
	@rm -f $(NAME)
	@echo "Function cleaned"

re : fclean all

.PHONY : fclean clean all re

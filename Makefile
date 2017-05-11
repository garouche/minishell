# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: garouche <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/21 18:36:31 by garouche          #+#    #+#              #
#    Updated: 2017/05/11 13:00:28 by garouche         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
SRC			=	exec.c main.c tools.c unset_env.c cd.c exit.c tools2.c \
				tools3.c tools.c env.c set_env.c
OBJ			=	$(SRC:.c=.o)
CFLAGS		=	-Wall -Werror -Wextra
LIBDIR		=	libft/
LIBC		=	$(LIBDIR)libft.a
.PHONY		:	all clean re fclean

all			:	$(NAME)

$(NAME)		:	$(LIBC) $(OBJ)
				ar r $(LIBC) $(OBJ)
				gcc $(CFLAGS) -o $(NAME) $(LIBC)
$(LIBC)		:	$(LIBDIR)
				make -C $(LIBDIR)

clean		:
				rm -f $(OBJ)
				make -C $(LIBDIR) fclean

re			:	fclean all

fclean		:	clean
				rm -f $(NAME)

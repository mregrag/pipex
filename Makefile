# **************************************************************************** #
#                                                                              #
                                                       :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/14 05:50:00 by mregrag           #+#    #+#              #
#    Updated: 2024/02/17 12:03:04 by mregrag          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC		= cc

CFLAGS	= -Wall -Wextra -Werror

NAME	= pipex

RM		= rm -rf

SRCS	:= pipex.c\
			pipex_utils1.c\
			pipex_utils2.c\
			error.c\
			ft_split.c

OBJS	:= ${SRCS:.c=.o}

all     : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $(NAME)

%.o     : %.c pipex.h
	$(CC) $(CFLAGS) -c $< -o $@

clean   :
	$(RM) $(OBJS)

fclean  : clean
	$(RM) $(NAME)

re       : fclean all

.PHONY   : all clean fclean re

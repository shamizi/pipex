# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shamizi <shamizi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/11 14:26:39 by shamizi           #+#    #+#              #
#    Updated: 2021/10/11 15:53:50 by shamizi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =pipex

SRCS= src/path.c \
	  src/ft_split.c \
	  src/utils.c

OBJS =$(SRCS:.c=.o)


CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

RM = rm -rf

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

$(NAME):	$(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
clean: 
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)

re: fclean all

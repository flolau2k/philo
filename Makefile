# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/12 11:17:07 by flauer            #+#    #+#              #
#    Updated: 2023/07/31 21:38:32 by flauer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		philo

CC =		cc
CFLAGS =	-g -Wall -Wextra -Werror

INCLUDES =	-Iinclude -pthread

OBJDIR =	obj
SRCDIR =	src
INCDIR =	include

FILES =		philo.c helpers.c time.c init.c main.c mutexes.c waiter.c cleanup.c
HEADER_F =	philo.h

SRC =		$(addprefix $(SRCDIR)/, $(FILES))
OBJ =		$(addprefix $(OBJDIR)/, $(FILES:%.c=%.o))
HEADERS =	$(addprefix $(INCDIR)/, $(HEADER_F))

all: $(NAME)

$(NAME): $(LIBFT) $(LIBMLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(INCLUDES) -o $(NAME)
	@echo "built $(NAME)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS) | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	/bin/rm -rf $(OBJDIR)

fclean: clean
	/bin/rm -rf $(NAME)

re:	fclean all

.PHONY =	all clean fclean re

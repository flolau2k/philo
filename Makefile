# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flauer <flauer@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/12 11:17:07 by flauer            #+#    #+#              #
#    Updated: 2023/07/21 14:38:30 by flauer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =		philo

CC =		cc
CFLAGS =	-g -Wall -Wextra -Werror

INCLUDES =	-Iinclude

OBJDIR =	obj
SRCDIR =	src
INCDIR =	include

FILES =		philo.c
HEADER_F =	philo.h

SRC =		$(addprefix $(SRCDIR)/, $(FILES))
OBJ =		$(addprefix $(OBJDIR)/, $(FILES:%.c=%.o))
HEADERS =	$(addprefix $(INCDIR)/, $(HEADER_F))

all: $(NAME)

$(NAME): $(LIBFT) $(LIBMLX) $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "built $(NAME)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS) | $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

$(OBJDIR):
	@mkdir -p $(OBJDIR)

clean:
	make -C libft clean
	/bin/rm -rf $(OBJDIR)

fclean: clean
	make -C libft fclean
	/bin/rm -rf $(NAME)

re:	fclean all

.PHONY =	all clean fclean re

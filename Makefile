# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/04 11:53:01 by tguillem          #+#    #+#              #
#    Updated: 2016/03/10 15:18:34 by tguillem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -g -Wall -Wextra -Werror -I./includes
PRGFLAGS = -lft
CC = gcc

NAME = ft_ls
LIB = libft
SRC = main.c ft_ls.c error.c spaces.c stat.c print.c display.c sort.c utils.c \
	  perms.c destroyer.c recursive.c parsing.c
SRCDIR = src
OUTDIR = out
SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJ = $(addprefix $(OUTDIR)/, $(SRC:.c=.o))
all: $(NAME)

$(NAME): mkOut $(OBJ)
	(cd $(LIB) && $(MAKE))
	$(CC) -o $(NAME) $(CFLAGS) -I./libft -L./libft $(OBJ) $(PRGFLAGS)
$(OUTDIR)/%.o: $(SRCDIR)/%.c
	$(CC) -I $(LIB) -o $@ -c $? $(CFLAGS)

mkOut:
	@mkdir -p $(OUTDIR)

clean:
	@(cd $(LIB) && $(MAKE) $@)
	@rm -f $(OBJ)
	@rm -rf $(OUTDIR)

fclean: clean
	@(cd $(LIB) && $(MAKE) $@)
	@rm -f $(NAME)

.PHONY: clean fclean re

re: fclean all

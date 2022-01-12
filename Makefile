# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lbrandy <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/25 14:21:29 by lbrandy           #+#    #+#              #
#    Updated: 2021/07/27 16:05:27 by lbrandy          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CFLAGS = -Wall -Wextra -Werror
CC = gcc
SRCS = main.c utils.c pars_argv.c actions_philo.c \
	   filling.c simulation.c error_handling.c
OBJDIR = obj/
OBJS = $(addprefix $(OBJDIR), $(SRCS:.c=.o))

all: $(NAME)

$(NAME):$(OBJDIR) $(OBJS)
	$(CC) $(CFLAGS) $(LIBFT) $(SRCS) -o $(NAME)

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

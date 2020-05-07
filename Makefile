# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/13 18:19:52 by jrignell          #+#    #+#              #
#    Updated: 2020/05/07 16:22:29 by jrignell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -Wall -Wextra -Werror
CC = gcc

INC_DIR := ./includes
SRC_DIR := ./minishell_srcs
OBJ_DIR := ./obj

SRC :=	main.c \
		sh_env.c \
		sh_exit.c \
		minishell.c \
		sh_change_dir.c \
		sh_del_struct.c \
		sh_init_struct.c \
		sh_form_struct.c \
		sh_trim_command.c \
		sh_builtin_exec.c \
		sh_check_builtin.c \
		sh_display_prompt.c \
		sh_read_more_input.c
		
OBJ :=	$(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all: $(NAME)

$(OBJ_DIR):
	@/bin/mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ -c $<

$(NAME): $(OBJ_DIR) $(OBJ)
	@make -C libft/printf_srcs/
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) libft/printf_srcs/libftprintf.a -ltermcap

clean:
	@/bin/rm -f $(OBJ)
	@make -C libft/printf_srcs/ clean
	@make -C libft/ clean

fclean: clean
	@/bin/rm -f $(NAME)
	@/bin/rm -f $(OBJ)
	@make -C libft/printf_srcs/ fclean
	@make -C libft/ fclean
	
sh: $(OBJ_DIR) $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) libft/printf_srcs/libftprintf.a -ltermcap
	@make clean

re: fclean all

.PHONY: all clean re fclean
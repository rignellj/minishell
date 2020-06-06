# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/13 18:19:52 by jrignell          #+#    #+#              #
#    Updated: 2020/06/06 17:02:27 by jrignell         ###   ########.fr        #
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
		sh_init.c \
		sh_exit.c \
		minishell.c \
		sh_read_line.c \
		sh_change_dir.c \
		sh_del_struct.c \
		sh_init_struct.c \
		sh_del_command.c \
		sh_form_struct.c \
		sh_trim_command.c \
		sh_builtin_exec.c \
		sh_command_parse.c \
		sh_check_builtin.c \
		sh_display_prompt.c \
		sh_read_more_input.c \
		sh_put_args_to_array.c \
		sh_init_signal_handlers.c
		
OBJ :=	$(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

all: $(NAME)

# .SILENT:

$(OBJ_DIR):
	@/bin/mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -I $(INC_DIR) -o $@ -c $<

$(NAME): $(OBJ_DIR) $(OBJ)
	@echo "\\033[1;33mBuilding libft..\\033[0;39m"
	@make -C libft/printf_srcs/
	@echo "\\033[1;33mBuilding shell..\\033[0;39m"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) libft/printf_srcs/libftprintf.a -ltermcap
	@echo "\\033[1;32mDONE\\033[0;39m"
	@echo "\n\\033[1;37mLaunch ./minishell\\033[0;39m"

clean:
	@echo "\\033[1;31mCleaning shell object files..\\033[0;39m"
	@/bin/rm -f $(OBJ)
	@echo "\\033[1;31mCleaning ft_printf and libft object files..\\033[0;39m"
	@make -C libft/printf_srcs/ clean
	@make -C libft/ clean

fclean: clean
	@echo "\n\\033[1;37mCleaning executables..\\033[0;39m"
	@/bin/rm -f $(NAME)
	@make -C libft/printf_srcs/ fclean
	@make -C libft/ fclean
	
sh: $(OBJ_DIR) $(OBJ)
	@echo "\\033[1;33mBuilding project..\\033[0;39m"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) libft/printf_srcs/libftprintf.a -ltermcap
	@echo "\\033[1;32mDONE\\033[0;39m\n"
	@make clean

re: fclean all

.PHONY: all clean re fclean

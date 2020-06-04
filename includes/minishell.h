/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 19:38:34 by jrignell          #+#    #+#             */
/*   Updated: 2020/05/26 14:39:01 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/printf_srcs/includes/ft_printf.h"
# include <termios.h>

/*
********************************************************************************
**                         KEYS                                               **
********************************************************************************
*/

# define LEFT 0x445B1B
# define RIGHT 0x435B1B
# define DOWN 0x425B1B
# define UP 0x415B1B
# define ENTER 0xA
# define ESC 0x1B
# define DEL 0x7E335B1B
# define SPACE 0x20
# define BSPACE 0x7F
# define ASTERISK 0x2A
# define MINUS 0x2D

/*
********************************************************************************
**                         STRUCTS                                            **
********************************************************************************
*/

typedef struct termios	t_termios;

typedef struct	s_shell
{
	int			ac;
	int			term_fd;
	int			file_fd;
	int			i;
	pid_t		child_status;
	char		**av;
	char		**env;
	char		**commands; //doesn't need to be freed -> minishell function handles this
	char		**backslash;
	char		**built_ins;
	char		*exec_path;
	char		*user_command;
	t_termios	original_term_mode;
	t_termios	current_term_mode;
}				t_shell;

/*
********************************************************************************
**                         GLOBALS                                            **
********************************************************************************
*/

t_shell			*g_shell;

/*
********************************************************************************
**                                                                            **
**                         MOST IMPORTANT FUNCTIONS                           **
**                                                                            **
********************************************************************************
*/

void			sh_init(int ac, char *av[], char *env[], t_shell *d);
void			sh_init_signal_handlers(void);
void			minishell(t_shell *info);
char			*sh_read_line(t_shell *d);
char			*sh_read_more_input(t_shell *d);
int				sh_error(char *error);
int				sh_exit(t_shell *d, char const *error);
void			sh_form_struct(t_shell *d);
int				sh_display_prompt(t_shell *data);
int				sh_trim_command(t_shell *d);
int				sh_builtin_exec(t_shell *d, char **commands);
void			sh_init_struct(t_shell *data);
int				sh_check_builtin(t_shell *d, char *bic);
int				sh_change_dir(t_shell *d);
int				sh_env(t_shell *d, size_t len);
void			sh_del_command(t_shell *d, char *line, char **c);
void			sh_del_struct(t_shell *d);

#endif

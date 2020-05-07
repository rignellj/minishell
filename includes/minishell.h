/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 19:38:34 by jrignell          #+#    #+#             */
/*   Updated: 2020/05/07 19:10:52 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/printf_srcs/includes/ft_printf.h"

/*
********************************************************************************
**                                                                            **
**                         DEV                                                **
**                                                                            **
********************************************************************************
*/
/*
********************************************************************************
**                                                                            **
**                         STRUCTS                                            **
**                                                                            **
********************************************************************************
*/

typedef struct	s_shell
{
	int			ac;
	int			fd;
	int			i;
	char		**av;
	char		**env;
	char		**commands; //doesn't need to be freed -> minishell function handles this
	char		**backslash;
	char		**built_ins;
	char		*exec_path;
	char		*user_command;
}				t_shell;


/*
********************************************************************************
**                                                                            **
**                         MOST IMPORTANT FUNCTIONS                           **
**                                                                            **
********************************************************************************
*/

void			minishell(t_shell *info);
char			*sh_read_line(t_shell *d);
char			*sh_read_more_input(t_shell *d);
int				sh_error(char *error);
int				sh_exit(t_shell *d);
void			sh_form_struct(t_shell *d);
int				sh_display_prompt(t_shell *data);
int				sh_trim_command(t_shell *d);
int				sh_builtin_exec(t_shell *d, char **commands);
void			sh_init_struct(t_shell *data);
int				sh_check_builtin(t_shell *d, char *bic);
int				sh_change_dir(t_shell *d);
int				sh_env(t_shell *d, size_t len);
void			sh_del_struct(t_shell *d);

#endif

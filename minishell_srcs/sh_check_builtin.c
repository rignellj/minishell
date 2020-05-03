/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_check_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 14:46:55 by jrignell          #+#    #+#             */
/*   Updated: 2020/05/02 17:18:15 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
********************************************************************************
** char *bic stands for builtin command                                       **
********************************************************************************
*/

static int	sh_echo(t_shell *d, char *ptr)
{
	
	ptr ? ft_printf("%s\n", ++ptr): ft_putchar('\n');
	return (1);
	d->ac = d->ac;//del
}

static int	sh_cd(t_shell *d, char *p)
{
	size_t	i;
	
	i = 0;
	if (p && d->commands[1] && *d->commands[1] != '$' && *d->commands[1] != '~')
		return (chdir(d->commands[1]) + 1);
	while (d->env[i])
	{
		if (ft_strncmp(d->env[i], "HOME", 4) == 0)
			return (chdir(ft_strchr(d->env[i], '/')) + 1);
		i++;
	}
	return (1);
}

int		sh_check_builtin(t_shell *d, char *bic)
{
	size_t	i;
	char	*ptr;

	i = 1;
	if ((ft_strcmp(bic, "echo") == 0) && (ptr = ft_strchr(d->user_command, 'o')))
		return (sh_echo(d, ++ptr));
	else if ((ft_strcmp(bic, "cd") == 0) && (ptr = ft_strchr(d->user_command, 'd')))
		return (sh_cd(d, ++ptr));
	else if (ft_strnstr(bic, "env", 8) && (ptr = ft_strchr(d->user_command, 'v')))
		return (sh_env(d, ++ptr, ft_strlen(bic)));
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 13:13:15 by jrignell          #+#    #+#             */
/*   Updated: 2020/06/06 20:59:17 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static int	sh_unsetenv(t_shell *sh)
{
	size_t	i;
	size_t	len;
	char	*join;

	if (!sh->commands[1])
		return (sh_error(ft_strdup("unsetenv: not enough arguments\n")) + 1);
	len = ft_arraylen((const void **)sh->commands);
	while (--len)
	{
		i = 0;
		join = ft_strjoin(sh->commands[len], "=");
		while (sh->env[i])
		{
			if (!ft_strncmp(join, sh->env[i], ft_strlen(join)))
			{
				ft_bzero(sh->env[i], sizeof(sh->env[i]));
				break ;
			}
			i++;
		}
		ft_strdel(&join);
	}
	return (1);
}

static int	sh_print_env(t_shell *sh)
{
	size_t	i;

	i = 0;
	while (sh->env[i])
	{
		if (*sh->env[i])
			ft_printf("%s\n", sh->env[i]);
		i++;
	}
	return (1);
}

static int	sh_setenv_new(t_shell *sh)
{
	char	*join;

	join = ft_joindel(ft_strjoin(sh->commands[1], "="),
	ft_strdup(sh->commands[2]));
	sh->env = ft_array_push(sh->env, join);
	ft_strdel(&join);
	return (1);
}

static int	sh_setenv(t_shell *sh)
{
	size_t	i;

	if ((i = ft_arraylen((const void **)sh->commands)) != 3)
	{
		i < 3 ? sh_error(ft_strdup("setenv: not enough arguments\n")) :
		sh_error(ft_strdup("setenv: too many arguments\n"));
		return (1);
	}
	i = 0;
	while (sh->env[i])
	{
		if (!ft_strncmp(sh->env[i], sh->commands[1], ft_strlen(sh->commands[1]))
			&& sh->env[i][ft_strlen(sh->commands[1])] == '=')
		{
			ft_strdel(&sh->env[i]);
			sh->env[i] = ft_joindel(ft_strjoin(sh->commands[1], "="),
			ft_strdup(sh->commands[2]));
			return (1);
		}
		i++;
	}
	return (sh_setenv_new(sh));
}

int			sh_env(t_shell *sh, size_t len)
{
	if (len == 3)
		return (sh_print_env(sh));
	if (len == 6)
		return (sh_setenv(sh));
	if (len == 8)
		return (sh_unsetenv(sh));
	return (1);
}

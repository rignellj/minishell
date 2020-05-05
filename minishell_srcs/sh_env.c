/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 13:13:15 by jrignell          #+#    #+#             */
/*   Updated: 2020/05/05 16:06:10 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static int	sh_unsetenv(t_shell *d)
{
	size_t	i;
	size_t	len;
	char	*join;

	if (!d->commands[1])
		return (sh_error(ft_strdup("unsetenv: not enough arguments\n")) + 1);
	len = ft_arraylen((const void **)d->commands);
	while (--len)
	{
		i = 0;
		join = ft_strjoin(d->commands[len], "=");
		while (d->env[i])
		{
			if (!ft_strncmp(join, d->env[i], ft_strlen(join)))
			{
				ft_bzero(d->env[i], sizeof(d->env[i]));
				break ;
			}
			i++;
		}
		ft_strdel(&join);
	}
	return (1);
}

static int	sh_print_env(t_shell *d)
{
	size_t	i;

	i = 0;
	while (d->env[i])
	{
		if (*d->env[i])
			ft_printf("%s\n", d->env[i]);
		i++;
	}
	return (1);
}

static int	sh_setenv_new(t_shell *d)
{
	char	*join;

	join = ft_joindel(ft_strjoin(d->commands[1], "="),
	ft_strdup(d->commands[2]));
	d->env = ft_array_push(d->env, join);
	ft_strdel(&join);
	return (1);
}

static int	sh_setenv(t_shell *d)
{
	size_t	i;

	if ((i = ft_arraylen((const void **)d->commands)) != 3)
	{
		i < 3 ? sh_error(ft_strdup("setenv: not enough arguments\n")) :
		sh_error(ft_strdup("setenv: too many arguments\n"));
		return (1);
	}
	i = 0;
	while (d->env[i])
	{
		if (!ft_strncmp(d->env[i], d->commands[1], ft_strlen(d->commands[1]))
			&& d->env[i][ft_strlen(d->commands[1])] == '=')
		{
			ft_strdel(&d->env[i]);
			d->env[i] = ft_joindel(ft_strjoin(d->commands[1], "="),
			ft_strdup(d->commands[2]));
			return (1);
		}
		i++;
	}
	return (sh_setenv_new(d));
}

int			sh_env(t_shell *d, size_t len)
{
	if (len == 3)
		return (sh_print_env(d));
	if (len == 6)
		return (sh_setenv(d));
	if (len == 8)
		return (sh_unsetenv(d));
	return (1);
}

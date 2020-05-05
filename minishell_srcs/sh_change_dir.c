/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_change_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 19:31:43 by jrignell          #+#    #+#             */
/*   Updated: 2020/05/05 16:05:38 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sh_update_oldpwd(t_shell *d)
{
	char	*env_pwd;
	char	*join;
	size_t	i;

	if (!(env_pwd = ft_strchr(ft_arraystr((const char **)d->env, "PWD="), '/')))
		return ;
	i = 0;
	while (d->env[i])
	{
		if (ft_strncmp(d->env[i], "OLDPWD=", 7) == 0)
		{
			ft_strdel(&d->env[i]);
			d->env[i] = ft_strjoin("OLDPWD=", env_pwd);
			return ;
		}
		i++;
	}
	join = ft_strjoin("OLDPWD=", env_pwd);
	d->env = ft_array_push(d->env, join);
	ft_strdel(&join);
}

static int	sh_change_to_oldpwd(t_shell *d, char *c)
{
	char	*pwd;

	if (*c == '-' && (pwd = ft_arraystr((const char **)d->env, "OLDPWD=")))
	{
		sh_update_oldpwd(d);
		return (chdir(ft_strchr(pwd, '/')) + 1);
	}
	return (1);
}

static int	sh_change_to_home(t_shell *d)
{
	char	*home;

	if (!(home = ft_arraystr((const char **)d->env, "HOME=")))
		return (1);
	if (!(home = ft_strchr(home, '/')))
		return (1);
	sh_update_oldpwd(d);
	return (chdir(home) + 1);
}

int			sh_change_dir(t_shell *d)
{
	if (!d->commands[1])
		return (sh_change_to_home(d));
	if (!ft_strncmp(d->commands[1], "-", 1))
		return (sh_change_to_oldpwd(d, d->commands[1]));
	sh_update_oldpwd(d);
	chdir(d->commands[1]);
	return (1);
}

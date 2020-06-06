/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_change_dir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 19:31:43 by jrignell          #+#    #+#             */
/*   Updated: 2020/06/06 20:58:11 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sh_update_oldpwd(t_shell *sh)
{
	char	*env_pwd;
	char	*join;
	size_t	i;

	if (!(env_pwd = ft_strchr(ft_arraystr((const char **)sh->env, "PWD="), '/')))
		return ;
	i = 0;
	while (sh->env[i])
	{
		if (ft_strncmp(sh->env[i], "OLDPWD=", 7) == 0)
		{
			ft_strdel(&sh->env[i]);
			sh->env[i] = ft_strjoin("OLDPWD=", env_pwd);
			return ;
		}
		i++;
	}
	join = ft_strjoin("OLDPWD=", env_pwd);
	sh->env = ft_array_push(sh->env, join);
	ft_strdel(&join);
}

static int	sh_change_to_oldpwd(t_shell *sh, char *c)
{
	char	*pwd;

	if (*c == '-' && (pwd = ft_arraystr((const char **)sh->env, "OLDPWD=")))
	{
		sh_update_oldpwd(sh);
		return (chdir(ft_strchr(pwd, '/')) + 1);
	}
	return (1);
}

static int	sh_change_to_home(t_shell *sh)
{
	char	*home;

	if (!(home = ft_arraystr((const char **)sh->env, "HOME=")))
		return (1);
	if (!(home = ft_strchr(home, '/')))
		return (1);
	sh_update_oldpwd(sh);
	return (chdir(home) + 1);
}

int			sh_change_dir(t_shell *sh)
{
	if (!sh->commands[1])
		return (sh_change_to_home(sh));
	if (!ft_strncmp(sh->commands[1], "-", 1))
		return (sh_change_to_oldpwd(sh, sh->commands[1]));
	sh_update_oldpwd(sh);
	chdir(sh->commands[1]);
	return (1);
}

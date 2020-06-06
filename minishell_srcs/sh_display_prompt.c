/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_display_prompt.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 15:13:34 by jrignell          #+#    #+#             */
/*   Updated: 2020/06/06 20:58:56 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static char	*sh_home(t_shell *sh)
{
	size_t	i;

	i = 0;
	while (sh->env[i])
	{
		if (ft_strncmp(sh->env[i], "HOME=", 5) == 0)
			return (ft_strchr(sh->env[i], '/'));
		i++;
	}
	return (NULL);
}

static void	sh_update_pwd(t_shell *sh, char cwd[1024])
{
	char	*join;
	size_t	i;

	i = 0;
	while (sh->env[i])
	{
		if (ft_strncmp(sh->env[i], "PWD=", 4) == 0)
		{
			ft_strdel(&sh->env[i]);
			sh->env[i] = ft_strjoin("PWD=", cwd);
			return ;
		}
		i++;
	}
	join = ft_strjoin("PWD=", cwd);
	sh->env = ft_array_push(sh->env, join);
	ft_strdel(&join);
}

int			sh_display_prompt(t_shell *sh)
{
	char	cwd[1024];
	char	*ptr;
	int		home;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (ft_printf("%s➢%s ", CBREDB, CRESET));
		sh_update_pwd(sh, cwd);
	if ((ptr = ft_strrchr(cwd, '/')) == NULL)
		return (ft_printf("%s➢%s ", CBREDB, CRESET));
	if (!sh_home(sh))
		return (ft_printf("%s%s%s %s➢%s ",
		CCYANB, ++ptr, CRESET, CBREDB, CRESET));
		home = !ft_strcmp(cwd, sh_home(sh)) ? 1 : 0;
	if (home)
		return (ft_printf("%s~%s %s➢%s ", CCYANB, CRESET, CBREDB, CRESET));
	if (*(ptr + 1) == '\0')
		return (ft_printf("%s%s%s %s➢%s ",
		CCYANB, ptr, CRESET, CBREDB, CRESET));
		return (ft_printf("%s%s%s %s➢%s ",
		CCYANB, ++ptr, CRESET, CBREDB, CRESET));
}

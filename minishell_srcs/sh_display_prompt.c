/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_display_prompt.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/28 15:13:34 by jrignell          #+#    #+#             */
/*   Updated: 2020/05/03 18:37:19 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*sh_home(t_shell *d)
{
	size_t	i;

	i = 0;
	while (d->env[i])
	{
		if (ft_strncmp(d->env[i], "HOME", 4) == 0)
			return (ft_strchr(d->env[i], '/'));
		i++;
	}
	return (NULL);
}

int			sh_display_prompt(t_shell *d)
{
	char	cwd[1024];
	char	*ptr;
	int		home;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (ft_printf("%s$>%s ", CBRED, CRESET));
	if ((ptr = ft_strrchr(cwd, '/')) == NULL)
		return (ft_printf("$> "));
	if (!sh_home(d))
		return (ft_printf("%s%s%s %s$>%s ", CCYANB, ++ptr, CRESET, CBRED, CRESET));
	home = !ft_strcmp(cwd, sh_home(d)) ? 1 : 0;
	if (home)
		return (ft_printf("%s~%s %s$>%s ", CCYANB, CRESET, CBRED, CRESET));
	if (*(ptr + 1) == '\0')
		return (ft_printf("%s%s%s %s$>%s ", CCYANB, ptr, CRESET, CBRED, CRESET));
	return (ft_printf("%s%s%s %s$>%s ", CCYANB, ++ptr, CRESET, CBRED, CRESET));
}

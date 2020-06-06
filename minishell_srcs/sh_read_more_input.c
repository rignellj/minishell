/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_read_more_input.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 16:21:44 by jrignell          #+#    #+#             */
/*   Updated: 2020/06/06 21:00:51 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sh_parse_quotes(t_shell *sh)
{
	size_t	i;
	int		pair;
	char	*line;
	char	*new_command;

	i = 0;
	pair = 0;
	while (sh->user_command[i])
	{
		if (sh->user_command[i++] == '"')
			pair++;
	}
	if (pair % 2 != 0)
	{
		get_next_line(0, &line);
		new_command = ft_strjoin(sh->user_command, "\n");
		new_command = ft_joindel(new_command, line);
		ft_strdel(&sh->user_command);
		sh->user_command = new_command;
		sh_read_more_input(sh);
	}
}

char		*sh_read_more_input(t_shell *sh)
{
	size_t	i;

	i = 0;
	while (sh->commands[i])
	{
		sh_parse_quotes(sh);
		i++;
	}
	return (NULL);
	
}

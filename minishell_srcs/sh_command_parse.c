/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_command_parse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 14:51:43 by jrignell          #+#    #+#             */
/*   Updated: 2020/06/06 20:41:17 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static int	sh_even_quote(char *ptr)
{
	size_t	s_quote;
	size_t	d_quote;
	size_t	i;

	s_quote = 0;
	d_quote = 0;
	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == SQUOTE)
			s_quote++;
		else if (ptr[i] == DQUOTE)
			d_quote++;
		if (i > 0 && ptr[i - 1] == ESCC && ptr[i] == DQUOTE)
			d_quote--;
		else if (i > 0 && ptr[i - 1] == ESCC && ptr[i] == SQUOTE)
			s_quote--;
		i++;
	}
	if (s_quote % 2 == 0 && d_quote % 2 == 0)
		return (EVEN);
	else
		return (UNEVEN);
}

static void	sh_combine_new_and_old_command(t_shell *sh, char *line)
{
	char	*tmp;

	tmp = ft_strjoin(sh->user_command, "\n");
	free(sh->user_command);
	sh->user_command = ft_joindel(tmp, line);
}

void		sh_command_parse(t_shell *sh)
{
	char	*line;
	int		even_or_uneven_quotes;

	even_or_uneven_quotes = UNEVEN;
	while (even_or_uneven_quotes == UNEVEN)
	{
		if ((even_or_uneven_quotes = sh_even_quote(sh->user_command)) == UNEVEN)
			line = sh_read_line(sh);
		if (even_or_uneven_quotes == UNEVEN)
			sh_combine_new_and_old_command(sh, line);
	}
	sh_put_args_to_array(sh);
}

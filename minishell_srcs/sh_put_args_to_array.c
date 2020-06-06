/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_put_args_to_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 16:59:43 by jrignell          #+#    #+#             */
/*   Updated: 2020/06/06 22:39:53 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>//

static size_t	sh_skip_white_space(char const *str)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *)str;
	while (ft_isspace(ptr[i]))
	{
		i++;
	}
	return (i);
}

static size_t	sh_skip_arguments(char const *str, int quote)
{
	size_t	skip;

	skip = 1;
	while (str[skip] && (int)str[skip] != quote)
		skip++;
	return (skip);
}

static size_t	sh_skip_characters(char const *str)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *)str;
	while (ft_isprint(ptr[i]) && ptr[i] != ' ')
	{
		if (ptr[i] == SQUOTE || ptr[i] == DQUOTE)
			i += sh_skip_arguments(&ptr[i], (int)ptr[i]);
		i++;
	}
	return (i);
}

static size_t	sh_count_args(char const *str)
{
	char	*ptr;
	size_t	num_args;

	num_args = 0;
	ptr = (char *)str;
	while (ptr && *ptr)
	{
		ptr += sh_skip_white_space(ptr);
		ptr += sh_skip_characters(ptr);
		num_args++;
		if (*ptr == '\0')
			break;
		ptr += sh_skip_white_space(ptr);
	}
	return (num_args);
}

void	sh_put_args_to_array(t_shell *sh)
{
	char	**command_array;
	size_t	num_args;
	size_t	i;
	size_t	j;
	size_t	word_len;

	num_args = sh_count_args(sh->user_command);
	// ft_printf("args: %d\n", num_args);
	if (!(command_array = (char **)malloc(sizeof(*command_array) * num_args + 1)))
		sh_exit(sh, "Malloc error. Exiting..\n");
	i = 0;
	command_array[num_args] = 0;
	while (num_args--)
	{
		sh->user_command += sh_skip_white_space(sh->user_command);
		word_len = sh_skip_characters(sh->user_command);
		// ft_printf("word_len: %d\n", word_len);
		if (!(command_array[i] = (char *)ft_memalloc(word_len + 1)))
			sh_exit(sh, "Malloc error. Exiting..\n");
		j = 0;
		while (word_len--)
			command_array[i][j++] = *sh->user_command++;
		sh->user_command += sh_skip_white_space(sh->user_command);
		i++;
	}
	sh->commands = command_array;
}

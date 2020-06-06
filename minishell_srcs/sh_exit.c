/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 15:16:00 by jrignell          #+#    #+#             */
/*   Updated: 2020/06/06 17:31:52 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int		sh_exit(t_shell *sh, char const *error)
{
	char	*str;

	if (error == NULL)
	{
		sh->i = 0;
		return (0);
	}
	else
	{
		str = ft_strdup(error);
		ft_dprintf(STDERR_FILENO, "%s", str);
		ft_strdel(&str);
		exit(EXIT_FAILURE);
	}
}

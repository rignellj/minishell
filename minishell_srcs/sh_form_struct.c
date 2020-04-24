/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_form_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 20:27:38 by jrignell          #+#    #+#             */
/*   Updated: 2020/04/24 21:01:10 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	sh_form_struct(t_shell *d)
{
	int		i;

	i = 0;
	while (d->env[i] && (ft_strncmp(d->env[i], "PATH", 4)) != 0)
		i++;
	d->paths = ft_strsplit(d->env[i], ':');
	ft_printf("%a", d->paths);
}

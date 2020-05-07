/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 17:01:46 by jrignell          #+#    #+#             */
/*   Updated: 2020/05/07 19:27:18 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int		main(int ac, char *av[], char *env[])
{
	t_shell	data;
	
	ft_bzero(&data, sizeof(t_shell));
	data.ac = ac;
	data.av = av;
	data.env = ft_arraydup((const char **)env);
	minishell(&data);
	while (1)
		;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 17:01:46 by jrignell          #+#    #+#             */
/*   Updated: 2020/04/24 20:33:43 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			main(int ac, char *av[], char *env[])
{
	t_shell	data;

	data.ac = ac;
	data.av = av;
	data.env = ft_arraydup((const char **)env);
	minishell(&data);
	// while(1);
	return (0);
}

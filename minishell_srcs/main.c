/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 17:01:46 by jrignell          #+#    #+#             */
/*   Updated: 2020/04/24 20:04:19 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			main(int ac, char *av[], char *env[])
{
	t_shell	info;

	info.ac = ac;
	info.av = av;
	info.env = ft_arraydup((const char **)env);
	ft_printf("%a", info.env);
	minishell(&info);
	// while(1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 17:01:46 by jrignell          #+#    #+#             */
/*   Updated: 2020/04/23 19:49:29 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int			main(int ac, char *av[])
{
	ac--;
	ac++;
	av++;
	av--;
	ft_printf("minishell project\n");
	return (0);
}

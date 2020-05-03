/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 20:37:08 by jrignell          #+#    #+#             */
/*   Updated: 2020/05/03 15:43:19 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (!(sub = ft_memalloc(sizeof(*sub) * (len + 1))))
		return (NULL);
	i = 0;
	while (len--)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}

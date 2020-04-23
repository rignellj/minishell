/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 15:15:46 by jrignell          #+#    #+#             */
/*   Updated: 2020/04/12 14:43:33 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	unsigned int	i;
	unsigned int	j;

	if (!*needle)
		return ((char*)haystack);
	i = 0;
	while (haystack[i] != '\0')
	{
		if (needle[0] == haystack[i])
		{
			j = 1;
			while (needle[j] == haystack[i + j] && needle[j] != '\0')
				++j;
			if (needle[j] == '\0')
				return ((char*)&haystack[i]);
		}
		++i;
	}
	return (NULL);
}

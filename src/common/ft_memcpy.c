/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhiedi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 13:53:51 by fhiedi            #+#    #+#             */
/*   Updated: 2024/04/10 13:57:24 by fhiedi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*from;
	char	*to;

	from = (char *)src;
	to = dst;
	while (n-- > 0)
		*to++ = *from++;
	return (dst);
}

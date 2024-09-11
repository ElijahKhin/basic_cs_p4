/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhiedi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:29:08 by fhiedi            #+#    #+#             */
/*   Updated: 2024/04/12 13:10:24 by fhiedi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *_new)
{
	t_list	*temp;

	temp = ft_lstlast((*lst));
	if (!temp)
		(*lst) = _new;
	else
		temp->next = _new;
}

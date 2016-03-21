/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_array.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 11:52:02 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/21 16:24:33 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		array_cpy(t_array **src, t_array *cpy)
{
	(*src)->data = cpy->data;
}

static void		swap_array(t_array **array1, t_array **array2)
{
	t_array	tmp;

	tmp = **array1;
	array_cpy(array1, *array2);
	array_cpy(array2, &tmp);
}

static void		internal_sort(t_array **lst, int (*cmp)(void *array1, void
			*array2, int type, int revert))
{
	t_array *tmp1;
	t_array *tmp2;

	tmp1 = *lst;
	while (tmp1)
	{
		tmp2 = tmp1->next;
		while (tmp2)
		{
			if (cmp(tmp1, tmp2, 0, 0) > 0)
				swap_array(&tmp1, &tmp2);
			tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next;
	}
}

t_array			*sort_array(t_array *lst)
{
	t_array	*result;

	if (!lst)
		return (NULL);
	result = lst;
	internal_sort(&result, &cmp_alpha);
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 11:52:02 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/11 12:25:30 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void		file_cpy(t_file **src, t_file *cpy)
{
	(*src)->name = cpy->name;
	(*src)->path = cpy->path;
	(*src)->date = cpy->date;
	(*src)->datensec = cpy->datensec;
	(*src)->st_mode = cpy->st_mode;
	(*src)->st_nlink = cpy->st_nlink;
	(*src)->st_uid = cpy->st_uid;
	(*src)->st_gid = cpy->st_gid;
	(*src)->st_size = cpy->st_size;
	(*src)->st_blocks = cpy->st_blocks;
	(*src)->st_rdev = cpy->st_rdev;
}

static void		swap_file(t_file **file1, t_file **file2)
{
	t_file	tmp;

	tmp = **file1;
	file_cpy(file1, *file2);
	file_cpy(file2, &tmp);
}

static void		internal_sort(t_file **lst, int (*cmp)(void *file1, void
			*file2, int type))
{
	t_file *tmp1;
	t_file *tmp2;

	tmp1 = *lst;
	while (tmp1)
	{
		tmp2 = tmp1->next;
		while (tmp2)
		{
			if (cmp(tmp1, tmp2, 1) > 0)
				swap_file(&tmp1, &tmp2);
			tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next;
	}
}

t_file			*sort_file(t_file *lst, t_args *args)
{
	t_file	*result;

	if (!lst)
		return (NULL);
	result = lst;
	if (args->t)
		internal_sort(&result, &cmp_time);
	else
		internal_sort(&result, &cmp_alpha);
	if (args->r)
		internal_sort(&result, &cmp_revert);
	return (result);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 11:52:14 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/11 12:43:33 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		cmp_alpha(void *data1, void *data2, int type)
{
	char	*str1;
	char	*str2;

	if (type == 1)
	{
		str1 = ((t_file*)data1)->name;
		str2 = ((t_file*)data2)->name;
	}
	else
	{
		str1 = ((t_array*)data1)->data;
		str2 = ((t_array*)data2)->data;
	}
	return (ft_strcmp(str1, str2));
}

int		cmp_revert(void *data1, void *data2, int type)
{
	char	*str1;
	char	*str2;

	if (type == 1)
	{
		str1 = ((t_file*)data1)->name;
		str2 = ((t_file*)data2)->name;
	}
	else
	{
		str1 = ((t_array*)data1)->data;
		str2 = ((t_array*)data2)->data;
	}
	return (ft_strcmp(str2, str1));
}

int		cmp_time(void *data1, void *data2, int type)
{
	t_file	*file1;
	t_file	*file2;

	file1 = ((t_file*)data1);
	file2 = ((t_file*)data2);
	if (file1->date < file2->date)
		return (1);
	if (file2->date < file1->date)
		return (-1);
	if (file1->datensec < file2->datensec)
		return (1);
	if (file2->datensec < file1->datensec)
		return (-1);
	return (cmp_alpha(file1, file2, type));
}

t_args	*init_args(void)
{
	t_args *ret;

	if (!(ret = (t_args*)malloc(sizeof(t_args))))
		return (NULL);
	ret->a = 0;
	ret->r = 0;
	ret->upper_r = 0;
	ret->l = 0;
	ret->t = 0;
	return (ret);
}

int		need_total_print(t_file *files, t_args *args, int mdir)
{
	int	count;

	if (!mdir)
		return (0);
	count = 0;
	while (files)
	{
		if (files->name[0] != '.')
			count++;
		files = files->next;
	}
	return (count || args->a);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 11:52:14 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/10 09:00:41 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		cmp_alpha(t_file *file1, t_file *file2)
{
	return (ft_strcmp(file1->name, file2->name));
}

int		cmp_time(t_file *file1, t_file *file2)
{
	if (file1->date < file2->date)
		return (1);
	if (file2->date < file1->date)
		return (-1);
	if (file1->datensec < file2->datensec)
		return (1);
	if (file2->datensec < file1->datensec)
		return (-1);
	return (cmp_alpha(file1, file2));
}

int		count_digit(int i)
{
	int result;

	result = 0;
	while (i)
	{
		i /= 10;
		result++;
	}
	return (result);
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

int		need_total_print(t_file *files, t_args *args, int multi_dir)
{
	int	count;

	if (!multi_dir)
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

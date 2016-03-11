/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 09:03:02 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/11 18:58:49 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	destroy_array(t_array *array)
{
	t_array	*to_del;
	t_array	*tmp;

	if (array)
	{
		tmp = array;
		while (tmp)
		{
			to_del = tmp;
			tmp = tmp->next;
			free(to_del);
		}
	}
}

void	destroy_files(t_file *files)
{
	t_file	*to_del;
	t_file	*tmp;

	if (files)
	{
		tmp = files;
		while (tmp)
		{
			to_del = tmp;
			tmp = tmp->next;
			free(to_del->name);
			free(to_del->path);
			to_del->next = NULL;
			free(to_del);
		}
	}
}

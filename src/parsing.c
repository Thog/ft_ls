/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 15:11:45 by tguillem          #+#    #+#             */
/*   Updated: 2016/04/14 09:17:43 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int				compute_options(char *str, t_args *args)
{
	if (*str == 'l')
		args->l = 1;
	else if (*str == 'R')
		args->upper_r = 1;
	else if (*str == 'a')
		args->a = 1;
	else if (*str == 'r')
		args->r = 1;
	else if (*str == 't')
		args->t = 1;
	else if (*str == '-' && !*(str + 1))
		return (0);
	else if (*str == '1')
		args->l = 0;
	else
		ls_usage(*str, &args);
	return (1);
}

static int				compute_flags(char *str, t_args *args)
{
	int result;

	result = 2;
	while (*str && (result = compute_options(str, args)))
		str++;
	return (result == 0);
}

int						prepare_args(char *str, t_args *args, t_array **lst,
		int force_file)
{
	if (*str == '-' && *(str + 1) && !force_file)
		return (compute_flags(str + 1, args));
	else if (*str)
	{
		*lst = array_init(*lst, str);
		return (1);
	}
	else if (!*str)
	{
		ft_putstr_fd("ls: fts_open: No such file or directory\n", 2);
		free(args);
		free(*lst);
		exit(1);
	}
	return (-1);
}

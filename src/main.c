/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 11:50:21 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/10 13:30:35 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

t_array	*array_init(t_array *root, char *str)
{
	t_array		*result;
	t_array		*tmp;

	tmp = root;
	if (!(result = (t_array*)malloc(sizeof(t_array))))
		return (NULL);
	result->data = str;
	result->next = NULL;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = result;
		return (root);
	}
	return (result);
}

void	compute_options(char c, t_args *args)
{
	if (c == 'l')
		args->l = 1;
	else if (c == 'R')
		args->upper_r = 1;
	else if (c == 'a')
		args->a = 1;
	else if (c == 'r')
		args->r = 1;
	else if (c == 't')
		args->t = 1;
	else if (c == '1' || c == '-')
		;
	else
		ls_usage(c, &args);
}

int		prepare_args(char *str, t_args *args, t_array **lst, int option)
{
	if (*str == '-' && *(str + 1) && !option)
	{
		return (prepare_args(str + 1, args, lst, 1));
	}
	else if (option == 1)
	{
		while (*str)
		{
			compute_options(*str, args);
			str++;
		}
		return (0);
	}
	else if (*str)
	{
		*lst = array_init(*lst, str);
		return (1);
	}
	return (-1);
}

void	compute_args(int ac, char **av, t_args **args, t_array **lst)
{
	t_array	*paths;
	t_args	*ret;
	int		i;

	paths = NULL;
	ret = init_args();
	i = 1;
	while (i < ac)
	{
		if (prepare_args(av[i], ret, &paths, 0) && !*lst)
			*lst = paths;
		i++;
	}
	if (!*lst)
		*lst = array_init(NULL, ".");
	*args = ret;
}

int		main(int ac, char **av)
{
	t_args		*args;
	t_array		*paths;

	args = NULL;
	paths = NULL;
	compute_args(ac, av, &args, &paths);
	start_ls(args, paths);
	destroy_array(paths);
	if (args)
		free(args);
	return (0);
}

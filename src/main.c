/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tguillem <tguillem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 11:50:21 by tguillem          #+#    #+#             */
/*   Updated: 2016/03/10 16:12:26 by tguillem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	compute_args(int ac, char **av, t_args **args, t_array **lst)
{
	t_array	*paths;
	t_args	*ret;
	int		i;
	int		force_file;

	paths = NULL;
	ret = init_args();
	i = 1;
	force_file = 0;
	while (i < ac)
	{
		if (prepare_args(av[i], ret, &paths, force_file) && !*lst)
		{
			force_file = 1;
			*lst = paths;
		}
		i++;
	}
	if (!*lst)
		*lst = array_init(NULL, ".");
	*args = ret;
}

int			main(int ac, char **av)
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

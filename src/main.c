
#include "ft_ls.h"
#include <stdio.h>
void	compute_options(char c, t_args *args)
{
	if (c == 'l')
		args->l = 1;
	else if (c == 'R')
		args->R = 1;
	else if (c == 'a')
		args->a = 1;
	else if (c == 'r')
		args->r = 1;
	else if (c == 't')
		args->t = 1;
}

int		prepare_args(char *str, t_args *args, t_list **lst, int option)
{
	if (*str == '-' && !option)
	{
		return (prepare_args(str + 1, args, lst, 1));
	}
	else if (option)
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
		ft_lstadd(lst, ft_lstnew(str, ft_strlen(str)));
		return (1);
	}
	return (-1);
}

void	compute_args(int ac, char **av, t_args **args, t_list **lst)
{
	t_list	*paths;
	t_args	*ret;
	int		i;

	i = 1;
	if (ac == 1)
		paths = ft_lstnew(".", 1);
	else
	{
		ret = (t_args*)malloc(sizeof(t_args));
		while (i < ac)
		{
			if (!*lst && prepare_args(av[i], ret, &paths, 0))
				*lst = paths;

			i++;
		}
	}

	*args = ret;
}

int		main(int ac, char **av)
{
	t_args		*args;
	t_list		*paths;

	compute_args(ac, av, &args, &paths);
		printf("%s\n", (char*)paths->content);
	return (0);
}

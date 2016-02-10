#include "ft_ls.h"
#include <stdio.h>

void	start_ls(t_args *args, t_array *paths)
{
	t_array	*tmp;
	//char	*str;

	tmp = paths;
	while (tmp && args)
	{
		printf("%s\n", tmp->data);
		//str = (char*)(tmp->content);
		//ft_putstr(str);
		//ft_putchar('\n');
		tmp = tmp->next;
	}
}

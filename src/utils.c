#include "ft_ls.h"

int		cmp_alpha(t_file *file1, t_file *file2)
{
	return (ft_strcmp(file1->name, file2->name));
}

int		cmp_time(t_file *file1, t_file *file2)
{
	return (file1->date < file2->date);
}

t_args	*init_args(void)
{
	t_args *ret;

	if(!(ret = (t_args*)malloc(sizeof(t_args))))
		return (NULL);
	ret->a = 0;
	ret->r = 0;
	ret->R = 0;
	ret->l = 0;
	ret->t = 0;
	return (ret);
}

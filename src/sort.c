#include "ft_ls.h"

static void	file_cpy(t_file **src, t_file *cpy)
{
	(*src)->name = cpy->name;
	(*src)->path = cpy->path;
	(*src)->date = cpy->date;
	(*src)->st_mode = cpy->st_mode;
	(*src)->st_nlink = cpy->st_nlink;
	(*src)->st_uid = cpy->st_uid;
	(*src)->st_gid = cpy->st_gid;
	(*src)->st_size = cpy->st_size;
	(*src)->st_blocks = cpy->st_blocks;
}

static void	swap_file(t_file **file1, t_file **file2)
{
	t_file	tmp;

	tmp = **file1;
	file_cpy(file1, *file2);
	file_cpy(file2, &tmp);
}

static void	reverse_sort(t_file **file)
{
	t_file	*tmp1;
	t_file	*tmp2;
	t_file	*tmp3;

	tmp1= *file;
	tmp2 = NULL;
	while (tmp1)
	{
		tmp3 = tmp2;
		tmp2 = tmp1;
		tmp1 = tmp1->next;
		tmp2->next = tmp3;
	}
	*file = tmp2;
}
static void	internal_sort(t_file **lst, int (*cmp)(t_file *file1, t_file *file2))
{
	t_file *tmp1;
	t_file *tmp2;

	tmp1 = *lst;
	while (tmp1)
	{
		tmp2 = tmp1->next;
		while (tmp2)
		{
			if (cmp(tmp1, tmp2) > 0)
			{
				swap_file(&tmp1, &tmp2);
			}
			tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next;
	}
}

t_file		*sort_file(t_file *lst, t_args *args)
{
	t_file	*result;

	if (!lst)
		return (NULL);
	result = lst;
	internal_sort(&result, &cmp_alpha);
	if (args->t)
		internal_sort(&result, &cmp_time);
	if (args->r)
		reverse_sort(&result);
	return (result);
}

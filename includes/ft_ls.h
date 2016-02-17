#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <unistd.h>
# include <errno.h>
//# include <uuid/uuid.h>
# include "libft.h"

# define MAJOR(x)((int32_t)(((u_int32_t)(x) >> 24) & 0xff))
# define MINOR(x)((int32_t)((x) & 0xffffff))
typedef struct		s_args
{
	int				l;
	int				R;
	int				a;
	int				r;
	int				t;
}					t_args;

typedef struct		s_array
{
	char			*data;
	struct s_array	*next;
}					t_array;

typedef struct		s_file
{
	char			*name;
	char			*path;
	time_t			date;
	mode_t			st_mode;
	nlink_t			st_nlink;
	uid_t			st_uid;
	gid_t			st_gid;
	off_t			st_size;
	quad_t			st_blocks;
	dev_t			st_rdev;
	struct s_file	*next;
}					t_file;

typedef struct		s_space
{
	int				total;
	int				size;
	int				user;
	int				link;
	int				group;
	int				min;
	int				maj;
}					t_space;

t_array		*array_init(t_array *root, char *data);
t_file		*file_stat(char *name, char *path, t_args *arg);
t_space		*get_spaces(t_args *args, t_file *file);
int			add_file(t_file **files, char *name, char *path, t_args *args);
void		compute_args(int ac, char **av, t_args **args, t_array **lst);
void		display_files(t_file *files, t_args *args, int is_dir);
void		simple_files_display(t_file *files, t_args *args);
void		long_files_display(t_file *files, t_args *args, int is_dir);
void		print_nbr(int nlink, int space);
void		print_str(char *str, int space);
void		print_majmin(t_file *file, t_space *spaces);
void		print_permissions(t_file *file);
void		print_date(time_t date);
void		start_ls(t_args *args, t_array *paths);
void		ft_error(char *str);
#endif

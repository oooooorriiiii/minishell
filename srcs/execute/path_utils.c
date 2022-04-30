//
// Created by ymori on 2/2/22.
//

#include "execute.h"
#include "utils.h"
#include <sys/stat.h>

bool	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == -1)
		return (false);
	if (S_ISDIR(path_stat.st_mode))
		return (true);
	return (false);
}

bool	is_executable(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) == -1)
		return (false);
	if ((path_stat.st_mode & S_IXUSR) != S_IXUSR)
		return (false);
	if ((path_stat.st_mode & S_IRUSR) != S_IRUSR)
		return (false);
	return (true);
}

bool	is_cmd_exist(const char *path, char **res)
{
	struct stat	path_stat;

	if (!path)
		return (false);
	if (lstat(path, &path_stat) == -1)
		return (false);
	if (S_ISDIR(path_stat.st_mode))
		return (false);
	free_str(res);
	*res = ft_strdup(path);
	return (true);
}

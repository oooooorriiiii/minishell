#include "get_next_line.h"

static int	set_up_line(ssize_t read_size, char **loaded_str, \
						char **line, int fd)
{
	char	*tmp;
	size_t	i;

	i = 0;
	while (loaded_str[fd][i] != '\n' && loaded_str[fd][i] != '\0')
		i++;
	if (loaded_str[fd][i] == '\n')
	{
		*line = ft_substr(loaded_str[fd], 0, i);
		tmp = ft_strdup(&loaded_str[fd][i + 1]);
		free(loaded_str[fd]);
		loaded_str[fd] = tmp;
		if (loaded_str[fd][0] == '\0')
			str_free(&loaded_str[fd]);
	}
	else
	{
		*line = ft_strdup(loaded_str[fd]);
		str_free(&loaded_str[fd]);
		if (read_size == 0 && loaded_str[fd] == NULL)
			return (0);
	}
	return (1);
}

static int	end_process(ssize_t read_size, char **loaded_str, \
						char **line, int fd)
{
	if (read_size < 0)
		return (-1);
	else if (read_size == 0 && loaded_str[fd] == NULL)
	{
		*line = ft_strdup("");
		return (0);
	}
	else
		return (set_up_line(read_size, loaded_str, line, fd));
}

static void	update_loaded_str(char **loaded_str, char *buf_str)
{
	char	*tmp;

	tmp = ft_strjoin(*loaded_str, buf_str);
	free(*loaded_str);
	*loaded_str = tmp;
}

int	get_next_line(int fd, char **line)
{
	static char	*loaded_str[OPEN_MAX];
	char		*buf_str;
	ssize_t		read_size;

	buf_str = malloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || fd >= OPEN_MAX || !line || !buf_str)
		return (-1);
	read_size = read(fd, buf_str, BUFFER_SIZE);
	while (read_size > 0)
	{
		buf_str[read_size] = '\0';
		if (loaded_str[fd] == NULL)
			loaded_str[fd] = ft_strdup(buf_str);
		else
			update_loaded_str(&loaded_str[fd], buf_str);
		read_size = read(fd, buf_str, BUFFER_SIZE);
		if (ft_memchr(loaded_str[fd], '\n', read_size))
			break ;
	}
	free(buf_str);
	return (end_process(read_size, loaded_str, line, fd));
}

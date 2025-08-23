#include "../push_swap.h"

static char	*read_line_content(int fd, char *line)
{
	char	c;
	int		i;
	int		bytes_read;

	i = 0;
	bytes_read = read(fd, &c, 1);
	while (bytes_read > 0)
	{
		if (c == '\n')
			break ;
		if (i < 999)
			line[i++] = c;
		bytes_read = read(fd, &c, 1);
	}
	line[i] = '\0';
	if (bytes_read <= 0 && i == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char	*line;

	if (fd < 0)
		return (NULL);
	line = malloc(1000);
	if (!line)
		return (NULL);
	return (read_line_content(fd, line));
}

static void	trim_trailing_spaces(char *instruction)
{
	int	len;
	int	i;

	if (!instruction)
		return ;
	len = ft_strlen(instruction);
	i = len - 1;
	while (i >= 0)
	{
		if (instruction[i] == '\n' || instruction[i] == '\r'
			|| instruction[i] == ' ' || instruction[i] == '\t')
			instruction[i] = '\0';
		else
			break ;
		i--;
	}
}

static void	trim_leading_spaces(char *instruction)
{
	int	i;
	int	j;

	i = 0;
	while (instruction[i] && (instruction[i] == ' ' || instruction[i] == '\t'))
		i++;
	if (i > 0)
	{
		j = 0;
		while (instruction[i])
			instruction[j++] = instruction[i++];
		instruction[j] = '\0';
	}
}

char	*clean_instruction(char *instruction)
{
	if (!instruction)
		return (NULL);
	trim_trailing_spaces(instruction);
	trim_leading_spaces(instruction);
	return (instruction);
}

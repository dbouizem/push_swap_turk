#include "../push_swap.h"

char	*read_line_from_stdin(void)
{
	char	*line;
	char	buffer;
	int		i;
	int		bytes_read;

	line = malloc(1000);
	if (!line)
		return (NULL);
	i = 0;
	bytes_read = read(0, &buffer, 1);
	while (bytes_read > 0 && buffer != '\n')
	{
		if (i < 999)
			line[i++] = buffer;
		bytes_read = read(0, &buffer, 1);
	}
	line[i] = '\0';
	if (bytes_read <= 0 && i == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*clean_instruction(char *instruction)
{
	int	len;
	int	i;
	int	j;

	if (!instruction)
		return (NULL);
	len = ft_strlen(instruction);
	i = len - 1;
	while (i >= 0 && (instruction[i] == '\n' || instruction[i] == '\r'
			|| instruction[i] == ' ' || instruction[i] == '\t'))
	{
		instruction[i] = '\0';
		i--;
	}
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
	return (instruction);
}

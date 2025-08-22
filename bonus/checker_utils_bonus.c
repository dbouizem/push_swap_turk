
#include "../push_swap.h"

// Version simple de get_next_line pour le checker
char	*get_next_line(int fd)
{
	char		*line;
	char		c;
	int			i;
	int			bytes_read;

	if (fd < 0)
		return (NULL);

	line = malloc(1000);
	if (!line)
		return (NULL);

	i = 0;
	while ((bytes_read = read(fd, &c, 1)) > 0)
	{
		if (c == '\n')
			break;
		if (i < 999)
			line[i++] = c;
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

	if (!instruction)
		return (NULL);

	len = ft_strlen(instruction);

	// Enlever les caractères de fin de ligne
	for (i = len - 1; i >= 0; i--)
	{
		if (instruction[i] == '\n' || instruction[i] == '\r' ||
			instruction[i] == ' ' || instruction[i] == '\t')
			instruction[i] = '\0';
		else
			break;
	}

	// Enlever les espaces au début
	i = 0;
	while (instruction[i] && (instruction[i] == ' ' || instruction[i] == '\t'))
		i++;

	// Si on a des espaces au début, décaler le contenu
	if (i > 0)
	{
		int j = 0;
		while (instruction[i])
			instruction[j++] = instruction[i++];
		instruction[j] = '\0';
	}

	return (instruction);
}

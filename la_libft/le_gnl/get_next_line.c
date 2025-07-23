/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlamber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:23:34 by anlamber          #+#    #+#             */
/*   Updated: 2025/04/07 14:24:26 by anlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_strcpy_part(char *dst, const char *src, size_t start)
{
	while (*src)
		dst[start++] = *src++;
}

char	*ft_strdup2(const char *s)
{
	size_t	len;
	size_t	i;
	char	*dup;

	len = 0;
	while (s[len])
		len++;
	dup = (char *)malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i <= len)
	{
		dup[i] = s[i];
		i++;
	}
	return (dup);
}

static char	*read_until_newline(int fd, char *tot_text)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr2(tot_text, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		tot_text = ft_strjoin2(tot_text, buffer);
	}
	free(buffer);
	return (tot_text);
}

char	*get_next_line(int fd)
{
	static char	*tot_text;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	tot_text = read_until_newline(fd, tot_text);
	if (!tot_text)
		return (NULL);
	if (tot_text[0] == '\0')
	{
		free(tot_text);
		tot_text = NULL;
		return (NULL);
	}
	line = extract_line(tot_text);
	tot_text = update_text(tot_text);
	return (line);
}

/*int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Erreur d'ouverture de fichier");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("→ %s", line);
		free(line);
	}
	close(fd);
	return (0);
}*/

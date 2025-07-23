/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlamber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 14:29:19 by anlamber          #+#    #+#             */
/*   Updated: 2025/04/10 14:29:21 by anlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen2(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len])
		len++;
	return (len);
}

char	*ft_strchr2(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin2(char *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*joined;

	if (!s1)
		s1 = ft_strdup2("");
	if (!s2)
		s2 = "";
	len1 = ft_strlen2(s1);
	len2 = ft_strlen2(s2);
	joined = malloc(len1 + len2 + 1);
	if (!joined)
		return (NULL);
	ft_strcpy_part(joined, s1, 0);
	ft_strcpy_part(joined, s2, len1);
	joined[len1 + len2] = '\0';
	free(s1);
	return (joined);
}

char	*extract_line(char *tot_text)
{
	size_t	len;
	char	*line;
	size_t	i;

	if (!tot_text || !tot_text[0])
		return (NULL);
	len = 0;
	while (tot_text[len] && tot_text[len] != '\n')
		len++;
	if (tot_text[len] == '\n')
		len++;
	line = malloc(len + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (i < len)
	{
		line[i] = tot_text[i];
		i++;
	}
	line[len] = '\0';
	return (line);
}

char	*update_text(char *tot_text)
{
	size_t	i;
	size_t	j;
	char	*new_text;

	if (!tot_text)
		return (NULL);
	i = 0;
	while (tot_text[i] && tot_text[i] != '\n')
		i++;
	if (!tot_text[i])
	{
		free(tot_text);
		return (NULL);
	}
	i++;
	new_text = malloc(ft_strlen2(tot_text + i) + 1);
	if (!new_text)
		return (NULL);
	j = 0;
	while (tot_text[i])
		new_text[j++] = tot_text[i++];
	new_text[j] = '\0';
	free(tot_text);
	return (new_text);
}

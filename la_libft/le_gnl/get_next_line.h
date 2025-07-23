/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlamber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:28:52 by anlamber          #+#    #+#             */
/*   Updated: 2025/04/02 16:29:39 by anlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

void	ft_strcpy_part(char *dst, const char *src, size_t start);
char	*ft_strdup2(const char *s);
char	*get_next_line(int fd);
size_t	ft_strlen2(const char *s);
char	*ft_strchr2(const char *s, int c);
char	*ft_strjoin2(char *s1, char const *s2);
char	*extract_line(char *tot_text);
char	*update_text(char *tot_text);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherman <aherman@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:31:04 by aherman           #+#    #+#             */
/*   Updated: 2023/09/20 13:58:09 by aherman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	c[4];

	c[0] = 0;
	c[1] = 0;
	c[2] = ft_strlen(s1);
	c[3] = ft_strlen(s2);
	if (!s1)
		s1 = ft_strdup("\0");
	s3 = malloc(sizeof(char) * (c[2] + c[3] + 1));
	if (s3 == NULL)
		return (NULL);
	else
	{
		while (s1[c[0]])
		{
			s3[c[1]++] = s1[c[0]++];
		}
	}
	c[0] = 0;
	while (s2[c[0]])
		s3[c[1]++] = s2[c[0]++];
	s3[c[1]] = '\0';
	return (s3);
}

int	ft_strncmp(const char *s1, const char *s2, size_t size)
{
	size_t	c1;

	c1 = 0;
	while (s1[c1] == s2[c1] && c1 != size && s1[c1] != '\0' && s2[c1] != '\0')
		c1++;
	if (c1 == size)
		return (0);
	return (((unsigned char *)s1)[c1] - ((unsigned char *)s2)[c1]);
}

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	c1;

	c1 = 0;
	while (s[c1])
	{
		ft_putchar_fd(s[c1], fd);
		c1++;
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

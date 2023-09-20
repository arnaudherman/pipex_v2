/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_need.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherman <aherman@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:05:03 by aherman           #+#    #+#             */
/*   Updated: 2023/09/20 11:28:21 by aherman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*ft_strdup(char *src)
{
	size_t	c[2];
	char	*s1;

	c[0] = 0;
	c[1] = 0;
	while (src[c[0]])
		c[0]++;
	s1 = malloc(sizeof(char) * (c[0] + 1));
	if (!s1)
		return (NULL);
	while (c[1] < c[0])
	{
		s1[c[1]] = src[c[1]];
		c[1]++;
	}
	s1[c[1]] = '\0';
	return (s1);
}

void	ft_free(void **s1)
{
	int	c1;

	c1 = 0;
	if (!s1)
		return ;
	while (s1[c1])
	{
		free(s1[c1]);
		c1++;
	}
	free(s1);
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

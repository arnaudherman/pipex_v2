/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_childs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherman <aherman@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 22:05:46 by aherman           #+#    #+#             */
/*   Updated: 2023/09/21 18:21:41 by aherman          ###   ########.fr       */
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

void	ft_free_char(char **str)
{
	int	c1;

	c1 = 0;
	while (str[c1])
	{
		free(str[c1]);
		c1++;
	}
	free(str);
}

void	ft_error(int flag)
{
	if (flag == 1)
		ft_putendl_fd("Error: command does not exist", 2);
	else
		perror("Error");
	exit(1);
}

void	child_one(t_info *info, char **envp)
{
	close(info->_pipe[0]);
	dup2(info->fd1, STDIN_FILENO);
	dup2(info->_pipe[1], STDOUT_FILENO);
	close(info->fd1);
	close(info->_pipe[1]);
	execve(info->cmd1, info->split1, envp);
	ft_error(-1);
}

void	child_two(t_info *info, char **envp)
{
	int	status;

	dup2(info->fd2, STDOUT_FILENO);
	dup2(info->_pipe[0], STDIN_FILENO);
	close(info->_pipe[1]);
	close(info->fd2);
	waitpid(info->p_id_c1, &status, 0);
	execve(info->cmd2, info->split2, envp);
	ft_error(-1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherman <aherman@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:23:39 by aherman           #+#    #+#             */
/*   Updated: 2023/09/20 11:21:48 by aherman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h> 
# include "../ft_printf/include/ft_printf.h"

typedef struct s_info
{
	int		_pipe[2];
	int		fd1;
	int		fd2;
	char	*cmd1;
	char	*cmd2;
	char	**split1;
	char	**split2;
	pid_t	p_id_c1;
	pid_t	p_id_c2;
}	t_info;

void	ft_error(int flag);
void	child_one(t_info *info, char **envp);
void	child_two(t_info *info, char **envp);
int		find_index_envp(char **envp);
char	*ft_getpath(char **envp, char *prog);
void	ft_free_char(char **str);
void	pipex(t_info *info, char **envp);

int	ft_strncmp(const char *s1, const char *s2, size_t size);
char	*ft_strcat(char *dest, const char *src);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strdup(char *src);
void	ft_free(void **s1);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_free_void(void **v1);
size_t	ft_strlen(const char *s);
char	**ft_split(char const *s, char c);

char	*ft_strjoin(char const *s1, char const *s2);

#endif
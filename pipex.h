/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mregrag <mregrag@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 02:05:48 by mregrag           #+#    #+#             */
/*   Updated: 2024/02/17 22:34:05 by mregrag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		openfile(char *filename, int mode);
void	pipex(char **argv, char **env);
void	msg(char *haed, char *msg, char *cmd, int n);
void	error(char *msg);
void	ft_free_tab(char **tab);
void	run_command(char *cmd, char **env);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
char	*get_path_command(char *cmd, char **envp);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*find_path(char **env);
char	*ft_strchr(const char *s, int c);
#endif

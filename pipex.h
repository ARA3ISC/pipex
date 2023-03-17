/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 23:09:54 by maneddam          #+#    #+#             */
/*   Updated: 2023/03/18 00:20:42 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include "ft_printf/ft_printf.h"

typedef struct s_data
{
	int fds[2];
	int fd_infile;
	int fd_outfile;
	int first_child;
	int second_child;
}				t_data;

void	print_error(char *msg, int nb);

char	**ft_split(char *s, char c);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
bool	check_cmds_args(char **env, char *cmd);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 23:09:40 by maneddam          #+#    #+#             */
/*   Updated: 2023/03/19 15:16:47 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_paths(char **env)
{
	int i = 0;
	char **paths;

	while (env[i])
	{
		if (env[i][0] == 'P' && env[i][3] == 'H')
		{
			env[i] = ft_strchr(env[i], '/');
			paths = ft_split(env[i], ':');
			return paths;
		}
		i++;
	}
	return NULL;
}

char **check_flags(char *cmd)
{
	char **new_cmd;

	new_cmd = ft_split(cmd, 32);
	return new_cmd;
}

void	check_cmds(char **env, char *cmd)
{
	char **paths;
	char **cmd_flags;
	char *f_cmd;
	int i = 0;

	paths = get_paths(env);
	cmd_flags = check_flags(cmd);

	if (access(cmd_flags[0], X_OK) == 0)
		execve(cmd_flags[0], cmd_flags, NULL);
	else
	{
		while (paths[i])
		{
			paths[i] = ft_strjoin(paths[i], "/");
			f_cmd = ft_strjoin(paths[i], cmd_flags[0]);
			if (access(f_cmd, X_OK) == 0)
				execve(f_cmd, cmd_flags, NULL);
			i++;
		}
	}
	cmd_not_found(cmd);
}

void	first_event(t_data data, char *argv[], char **env)
{
	data.fd_infile = open(argv[1], O_RDWR | O_CREAT | O_TRUNC);
	if (data.fd_infile == -1)
		print_error();

	close(data.fds[0]);
	if (dup2(data.fd_infile, 0) == -1)
		print_error();

	if (dup2(data.fds[1], 1) == -1)
	{
		print_error();
	}
	check_cmds(env, argv[2]);
}

void	second_event(t_data data, char *argv[], char **env)
{
	data.fd_outfile = open(argv[4], O_RDWR | O_CREAT |  O_TRUNC, 644);
	if (data.fd_outfile == -1)
		print_error();

	close(data.fds[1]);
	if (dup2(data.fd_outfile, 1) == -1)
		print_error();

	if (dup2(data.fds[0], 0) == -1)
	{

		print_error();
	}
	check_cmds(env, argv[3]);
}

void	begin_processing(char *argv[], char **env)
{
	t_data data;

	if (pipe(data.fds) == -1)
		print_error();


	data.first_child = fork();
	if (data.first_child == -1)
		print_error();

	if (data.first_child == 0)
		first_event(data, argv, env);

	data.second_child = fork();
	if (data.second_child == -1)
		print_error();

	if (data.second_child == 0)
		second_event(data, argv, env);


	wait(NULL);
}

int main(int argc, char *argv[], char **env)
{
	if (argc == 5)
	{
		begin_processing(argv, env) ;
	}
	else
		ft_printf("invalid argument number\n");

}

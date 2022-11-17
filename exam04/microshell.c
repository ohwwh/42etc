#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

# define PIPE 1
# define BREAK 2
# define END 3

typedef struct s_node
{
	int end_type;
	char **args;
	int	pipe[2];
	struct s_node *prev;
	struct s_node *next;
} t_node;

char	ft_strlen(char *str)
{
	int	ret;

	ret = 0;
	while (str[ret])
		ret ++;
	return (ret);
}

char	*ft_strdup(char *str)
{
	char *ret;
	int	i;

	i = 0;
	ret = (char *)malloc(sizeof(ft_strlen(str)));
	while (str[i])
	{
		ret[i] = str[i];
		i ++;
	}
	ret[i] = 0;
	return (ret);
}

void	free_strings(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = 0;
		i ++;
	}
	free(str);
	str = 0;
}

void	delete_list(t_node *start)
{
	t_node	*del;

	while (start)
	{
		free_strings(start->args);
		del = start;
		start = start->next;
		free(del);
		del = 0;
	}
}

t_node	*create_cmd_node(char **argv, int size)
{
	t_node *ret;
	int		i;

	i = 0;
	if (!size)
		return (0);
	ret = (t_node *)malloc(sizeof(t_node));
	ret->next = 0;
	ret->args = (char **)malloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		ret->args[i] = ft_strdup(argv[i]);
		i ++;
	}
	ret->args[i] = 0;
	return (ret);
}

int	check_end(char **argv)
{
	if (!*argv)
		return (END);
	else if (!strcmp(*argv, "|"))
		return (PIPE);
	else
		return (BREAK);
}

int	size_args(char **argv)
{
	int	ret;

	ret = 0;
	while (argv[ret] && strcmp(argv[ret], "|") && strcmp(argv[ret], ";"))
		ret ++;
	return (ret);
}

t_node	*parse_args(char **argv)
{
	int		size;
	t_node	*init;
	t_node	*cmd;
	t_node	*prev;
	int		first;

	init = 0;
	first = 1;
	while (*argv)
	{
		if (**argv == ';')
		{
			argv ++;
			continue ;
		}
		size = size_args(argv);
		cmd = create_cmd_node(argv, size);
		argv += size;
		cmd->end_type = check_end(argv);
		if (*argv)
			argv ++;
		if (first == 1)
		{
			init = cmd;
			prev = init;
			init->prev = 0;
			first = 0;
		}
		else
		{
			prev->next = cmd;
			cmd->prev = prev;
			prev = cmd;
		}
	}
	return (init);
}

void	execute_pipe(t_node *init, char *envp[])
{
	pid_t	pid;
	int		i;

	i = 0;
	while (init)
	{
		if (init->end_type == PIPE)
			pipe(init->pipe);
		pid = fork();
		if (pid)
		{
			waitpid(pid, 0, 0);
			if (init->prev && init->prev->end_type == PIPE)
				close(init->prev->pipe[0]);
			if (init->end_type == PIPE)
				close(init->pipe[1]);
			init = init->next; 
		}
		else
		{
			if (init->prev && init->prev->end_type == PIPE)
			{
				dup2(init->prev->pipe[0], 0);
				close(init->prev->pipe[0]);
			}
			if (init->end_type == PIPE)
			{
				dup2(init->pipe[1], 1);
				close(init->pipe[1]);
			}
			if (execve(init->args[0], init->args, envp) == -1)
				exit(-1);
			exit(0);
		}
		i ++;
	}

}

int main(int argc, char *argv[], char *envp[])
{
	t_node	*init;
	
	if (argc == 1)
		return (0);
	init = parse_args(&argv[1]);
	execute_pipe(init, envp);
	delete_list(init);
	//system("leaks microshell");
}

//./microshell /bin/ls "|" /usr/bin/grep micro ";" /bin/ls "|" /usr/bin/grep micro ";" /bin/ls "|" /usr/bin/grep micro ";" /bin/ls "|" /usr/bin/grep micro ";"
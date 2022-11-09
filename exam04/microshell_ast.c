#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

# define SMCOLON 0
# define PIPE 1
# define CMD 2

typedef struct s_node
{
	int type;
	char **args;
	int	pipe[2];
	struct s_node *next;
	struct s_node *left;
	struct s_node *right;
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

t_node	*create_pipe_node(void)
{
	t_node *ret;

	ret = (t_node *)malloc(sizeof(t_node));
	ret->type = PIPE;
	ret->next = 0;
	ret->left = 0;
	ret->right = 0;
	ret->args = 0;
	ret->pipe[0] = 0;
	ret->pipe[1] = 0;
	return (ret);
}

t_node	*create_cmd_node(char **args, int length)
{
	t_node *ret;
	int		i;

	i = 0;
	ret = (t_node *)malloc(sizeof(t_node));
	ret->type = CMD;
	ret->next = 0;
	ret->left = 0;
	ret->right = 0;
	ret->args = (char **)malloc(sizeof(char *) * (length + 1));
	while (i < length)
	{
		ret->args[i] = ft_strdup(args[i]);
		i ++;
	}
	ret->args[i] = 0;
	return (ret);
}

void	delete_tree(t_node *root)
{
	if (!root)
		return ;
	delete_tree(root->left);
	delete_tree(root->right);
	if (root->type == CMD)
		free_strings(root->args);
	free(root);
	root = 0;
}

void	delete_whole_trees(t_node *init)
{
	while (init)
	{
		delete_tree(init);
		init = init->next;
	}
}

t_node	*parse_args(char **argv)
{
	int		length;
	char	**start;
	t_node	*init;
	t_node	*pipe;
	t_node	*tmp;

	length = 0;
	init = create_pipe_node();
	tmp = init;
	start = argv;
	while (*argv)
	{
		start = argv;
		pipe = tmp;
		while (1)
		{
			if (!*argv || !strcmp(*argv, "|") || !strcmp(*argv, ";"))
			{
				if (!pipe->left)
					pipe->left = create_cmd_node(start, length);
				if (!*argv || !strcmp(*argv, ";"))
				{
					pipe->right = 0;
					length = 0;
					break ;
				}
				pipe->right = create_pipe_node();
				pipe = pipe->right;
				start = argv + 1;
				length = 0;
			}
			else
				length ++;
			argv ++;
		}
		if (*argv)
		{
			tmp->next = create_pipe_node();
			tmp = tmp->next;
			argv ++;
		}
		else
			tmp->next = 0;
	}
	return (init);
}

void	execute_pipe(t_node *init, char *envp[])
{
	pid_t	pid;
	t_node	*former;
	int		i;

	i = 0;
	former = 0;
	while (init)
	{
		pid = fork();
		if (pid)
		{
			waitpid(pid, 0, 0);
			former = init;
			init = init->right;
		}
		else
		{
			if (former)
			{
				dup2(former->pipe[0], 0);
				close(former->pipe[0]);
			}
			if (init->right)
			{
				pipe(init->left->pipe);
				dup2(init->left->pipe[1], 1);
				close(init->left->pipe[1]);
			}
			printf("%d: pipe?\n", i);
			if (execve(init->left->args[0], init->left->args, envp) == -1)
				printf("%d: pipe!\n", i);
			exit(0);
		}
		i ++;
	}
}

int main(int argc, char *argv[], char *envp[])
{
	t_node	*init;
	t_node	*tmp;

	init = parse_args(&argv[1]);
	tmp = init;
	while (tmp)
	{
		execute_pipe(tmp, envp);
		tmp = tmp->next;
	}
	delete_whole_trees(init);
	//system("leaks microshell");
}
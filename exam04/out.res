/bin/ls
microshell
microshell.c
microshell.dSYM
microshell_ast
microshell_ast.c
microshell_ast.dSYM
out.res
test.sh

/bin/cat microshell.c
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
	struct s_node *next_pipe;
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
		if (start->type == CMD)
			free_strings(start->args);
		del = start;
		start = start->next;
		free(del);
		del = 0;
	}
}

void	delete_whole_list(t_node *init)
{
	while (init)
	{
		delete_list(init);
		init = init->next_pipe;
	}
}

t_node	*create_pipe_node(void)
{
	t_node *ret;

	ret = (t_node *)malloc(sizeof(t_node));
	ret->type = PIPE;
	ret->next_pipe = 0;
	ret->next = 0;
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
	if (!length)
		return (0);
	ret = (t_node *)malloc(sizeof(t_node));
	ret->type = CMD;
	ret->next_pipe = 0;
	ret->next = 0;
	ret->args = (char **)malloc(sizeof(char *) * (length + 1));
	while (i < length)
	{
		ret->args[i] = ft_strdup(args[i]);
		i ++;
	}
	ret->args[i] = 0;
	return (ret);
}

t_node	*parse_args(char **argv)
{
	int		length;
	char	**start;
	t_node	*init;
	t_node	*pipe_root;
	t_node	*pipe;

	if (!*argv)
		return (0);
	length = 0;
	init = create_pipe_node();
	pipe_root = init;
	pipe = pipe_root;
	start = argv;
	while (*argv)
	{
		start = argv;
		while (1)
		{
			if (!*argv || !strcmp(*argv, "|") || !strcmp(*argv, ";"))
			{
				pipe->next = create_cmd_node(start, length);
				pipe = pipe->next;
				if (!*argv || !strcmp(*argv, ";"))
				{
					pipe = 0;
					length = 0;
					if (*argv)
						argv ++;
					break ;
				}
				start = argv + 1;
				length = 0;
			}
			else
				length ++;
			argv ++;
		}
		if (*argv)
		{
			pipe_root->next_pipe = create_pipe_node();
			pipe = pipe_root->next_pipe;
			pipe_root = pipe_root->next_pipe;
		}
		else
			pipe = 0;
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
			init = init->next; 
		}
		else
		{
			if (former)
			{
				dup2(former->pipe[0], 0);
				close(former->pipe[0]);
			}
			if (init->next)
			{
				pipe(init->pipe);
				dup2(init->pipe[1], 1);
				close(init->pipe[1]);
			}
			if (execve(init->args[0], init->args, envp) == -1)
				exit (-1);
			exit(0);
		}
		i ++;
	}
}

int main(int argc, char *argv[], char *envp[])
{
	t_node	*init;
	t_node	*tmp;
	
	if (argc == 1)
		return (0);
	init = parse_args(&argv[1]);
	tmp = init;
	while (tmp)
	{
		execute_pipe(tmp, envp);
		tmp = tmp->next_pipe;
	}
	delete_whole_list(init);
	//system("leaks microshell");
}
/bin/ls microshell.c
microshell.c

/bin/ls salut

;

; ;

; ; /bin/echo OK
OK

; ; /bin/echo OK ;
OK

; ; /bin/echo OK ; ;
OK

; ; /bin/echo OK ; ; ; /bin/echo OK
OK
OK

/bin/ls | /usr/bin/grep microshell

/bin/ls | /usr/bin/grep microshell | /usr/bin/grep micro

/bin/ls | /usr/bin/grep microshell | /usr/bin/grep micro | /usr/bin/grep shell | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro

/bin/ls | /usr/bin/grep microshell | /usr/bin/grep micro | /usr/bin/grep shell | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell

/bin/ls ewqew | /usr/bin/grep micro | /bin/cat -n ; /bin/echo dernier ; /bin/echo

/bin/ls | /usr/bin/grep micro | /bin/cat -n ; /bin/echo dernier ; /bin/echo ftest ;

/bin/echo ftest ; /bin/echo ftewerwerwerst ; /bin/echo werwerwer ; /bin/echo qweqweqweqew ; /bin/echo qwewqeqrtregrfyukui ;
ftest
ftewerwerwerst
werwerwer
qweqweqweqew
qwewqeqrtregrfyukui

/bin/ls ftest ; /bin/ls ; /bin/ls werwer ; /bin/ls microshell.c ; /bin/ls subject.fr.txt ;
leaks.res
microshell
microshell.c
microshell.dSYM
microshell_ast
microshell_ast.c
microshell_ast.dSYM
out.res
test.sh
microshell.c

/bin/ls | /usr/bin/grep micro ; /bin/ls | /usr/bin/grep micro ; /bin/ls | /usr/bin/grep micro ; /bin/ls | /usr/bin/grep micro ;

/bin/cat subject.fr.txt | /usr/bin/grep a | /usr/bin/grep b ; /bin/cat subject.fr.txt ;

/bin/cat subject.fr.txt | /usr/bin/grep a | /usr/bin/grep w ; /bin/cat subject.fr.txt ;

/bin/cat subject.fr.txt | /usr/bin/grep a | /usr/bin/grep w ; /bin/cat subject.fr.txt

/bin/cat subject.fr.txt ; /bin/cat subject.fr.txt | /usr/bin/grep a | /usr/bin/grep b | /usr/bin/grep z ; /bin/cat subject.fr.txt

; /bin/cat subject.fr.txt ; /bin/cat subject.fr.txt | /usr/bin/grep a | /usr/bin/grep b | /usr/bin/grep z ; /bin/cat subject.fr.txt

blah | /bin/echo OK
OK

blah | /bin/echo OK ;
OK


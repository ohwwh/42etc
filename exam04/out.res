/bin/ls
microshell
microshell.c
microshell.dSYM
microshell_ast
microshell_ast.c
microshell_ast.dSYM
out.res
test.sh
test2.sh

/bin/cat microshell.c
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

# define SMCOLON 0
# define PIPE 1
# define CMD 2
# define BREAK 3
# define END 4

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
	t_node	*tmp;
	
	if (argc == 1)
		return (0);
	init = parse_args(&argv[1]);
	tmp = init;
	execute_pipe(tmp, envp);
	delete_list(tmp);
	//system("leaks microshell");
}

//./microshell /bin/ls "|" /usr/bin/grep micro ";" /bin/ls "|" /usr/bin/grep micro ";" /bin/ls "|" /usr/bin/grep micro ";" /bin/ls "|" /usr/bin/grep micro ";"
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
microshell
microshell.c
microshell.dSYM
microshell_ast
microshell_ast.c
microshell_ast.dSYM

/bin/ls | /usr/bin/grep microshell | /usr/bin/grep micro
microshell
microshell.c
microshell.dSYM
microshell_ast
microshell_ast.c
microshell_ast.dSYM

/bin/ls | /usr/bin/grep microshell | /usr/bin/grep micro | /usr/bin/grep shell | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro
microshell
microshell.c
microshell.dSYM
microshell_ast
microshell_ast.c
microshell_ast.dSYM

/bin/ls | /usr/bin/grep microshell | /usr/bin/grep micro | /usr/bin/grep shell | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell
microshell
microshell.c
microshell.dSYM
microshell_ast
microshell_ast.c
microshell_ast.dSYM

/bin/ls ewqew | /usr/bin/grep micro | /bin/cat -n ; /bin/echo dernier ; /bin/echo
dernier


/bin/ls | /usr/bin/grep micro | /bin/cat -n ; /bin/echo dernier ; /bin/echo ftest ;
     1	microshell
     2	microshell.c
     3	microshell.dSYM
     4	microshell_ast
     5	microshell_ast.c
     6	microshell_ast.dSYM
dernier
ftest

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
test2.sh
microshell.c

/bin/ls | /usr/bin/grep micro ; /bin/ls | /usr/bin/grep micro ; /bin/ls | /usr/bin/grep micro ; /bin/ls | /usr/bin/grep micro ;
microshell
microshell.c
microshell.dSYM
microshell_ast
microshell_ast.c
microshell_ast.dSYM
microshell
microshell.c
microshell.dSYM
microshell_ast
microshell_ast.c
microshell_ast.dSYM
microshell
microshell.c
microshell.dSYM
microshell_ast
microshell_ast.c
microshell_ast.dSYM
microshell
microshell.c
microshell.dSYM
microshell_ast
microshell_ast.c
microshell_ast.dSYM

/bin/cat subject.fr.txt | /usr/bin/grep a | /usr/bin/grep b ; /bin/cat subject.fr.txt ;

/bin/cat subject.fr.txt | /usr/bin/grep a | /usr/bin/grep w ; /bin/cat subject.fr.txt ;

/bin/cat subject.fr.txt | /usr/bin/grep a | /usr/bin/grep w ; /bin/cat subject.fr.txt

/bin/cat subject.fr.txt ; /bin/cat subject.fr.txt | /usr/bin/grep a | /usr/bin/grep b | /usr/bin/grep z ; /bin/cat subject.fr.txt

; /bin/cat subject.fr.txt ; /bin/cat subject.fr.txt | /usr/bin/grep a | /usr/bin/grep b | /usr/bin/grep z ; /bin/cat subject.fr.txt

blah | /bin/echo OK
OK

blah | /bin/echo OK ;
OK


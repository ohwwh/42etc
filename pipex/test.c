#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "./libohw/includes/get_next_line.h"

int	main(int argc, char *argv[], char *envp[])
{
	int	pid;
	int	fd1;
	int	fd2;
	int	fd[2];
	int	fd_child[2];
	char	*str;
	char	**grep;
	char	**wc;
	int	pipe1;
	int	pipe2;
	int	status;

	grep = (char **)malloc(sizeof(char *) * 3);
	grep[0] = strdup("/usr/bin/grep");
	grep[1] = strdup("a1");
	grep[2] = 0;
	wc = (char **)malloc(sizeof(char *) * 3);
	wc[0] = strdup("/usr/bin/wc");
	wc[1] = strdup("-w");
	wc[2] = 0;
	fd1 = open("./infile", O_RDONLY);
	pipe1 = pipe(fd);
	printf("%d, %d, %d\n", fd[0], fd[1], pipe1);
	dup2(fd1, 0);
	close(fd1);
	pid = fork();
	if (pid > 0)
	{
		printf("parent\n");
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execve("/usr/bin/grep", grep, envp);
	}
	else
	{
		printf("child\n");
		fd1 = open("./outfile", O_WRONLY);
		dup2(fd[0], 0);
		dup2(fd1, 1);
		close(fd1);
		close(fd[1]);
		close(fd[0]);
		waitpid(pid, &status, 0);
		execve("/usr/bin/wc", wc, envp);
	}
}
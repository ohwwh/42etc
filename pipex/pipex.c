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
	int	fd[2];
	char	**grep;
	char	**wc;
	int	pipe1;
	int	status;
	int	k;

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
	dup2(fd1, 0); //fd1을 복제해서 0(표준입력)에다가 덮어씌운다
	close(fd1);
	pid = fork();
	if (pid > 0)
	{
		printf("parent\n");
		//fd1 = open("./outfile", O_WRONLY);
		fd1 = open("./outfile", O_WRONLY | O_APPEND);
		dup2(fd[0], 0); //읽기용 파이프 = 파이프출구, 이곳을 통해 입력받을 수 있음
		dup2(fd1, 1);
		close(fd1);
		close(fd[1]); //안쓰는 쓰기용 파이프 = 파이프입구는 반드시 닫아준다
		//close(fd[0]); 
		waitpid(pid, &status, 0);
		execve("/usr/bin/wc", wc, envp);
	}
	else
	{
		printf("child\n");
		dup2(fd[1], 1); //파이프 입구, 여기로 출력할 수 있음
		//close(fd[0]); //안쓰는 출구는 굳이 안닫아줘도 잘 되고 있다.
		//close(fd[1]);
		execve("/usr/bin/grep", grep, envp);
	}
}
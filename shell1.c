#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>
#include <sys/wait.h>

#define MAXLINE 4096
#define PROGRAMNAME "countnames"

void err_sys(const char* c) {
	perror(c);
	exit(1);
}

void err_ret(const char* c, ...) {
	va_list var_arg;
	va_start(var_arg, c);
	fprintf(stderr, c, var_arg);
	va_end(var_arg);
}

int main(int argc, char* argv[])
{
	char	buf[MAXLINE];
	pid_t	pid;
	int		status;

	printf("%% ");	/* print prompt (printf requires %% to print %) */
	while (fgets(buf, MAXLINE, stdin) != NULL) {
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0; /* replace newline with null */

		if ((pid = fork()) < 0) {
			err_sys("fork error");
		} else if (pid == 0) {		/* child */
			// int num = getppid() - getpid();  /* Meant to subtract child pid from parent pid to get exact process number,
												/*	Uncomment if necessary */
			execvp(PROGRAMNAME, argv);
			/*err_ret("couldn't execute: %s", buf); // Meant to print an error if previous instruction failed, but I think it will print an error anyway.
			exit(127);*/							// Uncomment if necessary.
		}

		/* parent */
		if ((pid = waitpid(pid, &status, 0)) < 0)
			err_sys("waitpid error");
		printf("%% ");
	}
	exit(0);
}

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
	char *args[100];

	printf("%% ");	/* print prompt (printf requires %% to print %) */
	while (fgets(buf, MAXLINE, stdin) != NULL) {
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0; /* replace newline with null */


		// Tokenize the input
		/* 
			./countnames names.txt names1.txt

			args: [./countnames, names.txt, names1.txt, NULL]

		*/
		int i = 0;
		char *token = strtok(buf, " ");
		while( token != NULL)
		{
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;

		// for each input file
		// fork and then exec the countnames program with the file as an argument

		for (int j = 1; j < i; j++) {

			pid_t pid = fork();

			if(pid == 0)
			{
				char *child_argv[] = {args[0], args[j], NULL};
				execvp(child_argv[0], child_argv);
				exit(1);
			}
		}


		

		/* parent wait untill all children are finished*/
		while (wait(NULL) > 0);
		printf("%% ");
	}
	exit(0);
}

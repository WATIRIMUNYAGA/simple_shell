#include "shell.h"

void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

/**
 * help_env - Displays information on the shellby builtin command 'env'.
 */
void help_env(void)
{
	char *msgm = "env: env\n\tPrints the current environment.\n";

	write(STDOUT_FILENO, msgm, _strlen(msgm));
}

/**
 * help_setenv - Displays information on the shellby builtin command 'setenv'.
 */
void help_setenv(void)
{
	char *msgm = "setenv: setenv [VARIABLE] [VALUE]\n\tInitializes a new";

	write(STDOUT_FILENO, msgm, _strlen(msgm));
	msgm = "environment variable, or modifies an existing one.\n\n";
	write(STDOUT_FILENO, msgm, _strlen(msgm));
	msgm = "\tUpon failure, prints a message to stderr.\n";
	write(STDOUT_FILENO, msgm, _strlen(msgm));
}

/**
 * help_unsetenv - Displays information on the shellby builtin command
 * 'unsetenv'.
 */
void help_unsetenv(void)
{
	char *msgm = "unsetenv: unsetenv [VARIABLE]\n\tRemoves an ";

	write(STDOUT_FILENO, msgm, _strlen(msgm));
	msgm = "environmental variable.\n\n\tUpon failure, prints a ";
	write(STDOUT_FILENO, msgm, _strlen(msgm));
	msgm = "message to stderr.\n";
	write(STDOUT_FILENO, msgm, _strlen(msgm));
}

#include "shell.h"

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);

/**
 * help_all - Displays all possible builtin shellby commands.
 */
void help_all(void)
{
	char *msgom = "Shellby\nThese shell commands are defined internally.\n";

	write(STDOUT_FILENO, msgom, _strlen(msgom));
	msgom = "Type 'help' to see this list.\nType 'help name' to find ";
	write(STDOUT_FILENO, msgom, _strlen(msgom));
	msgom = "out more about the function 'name'.\n\n  alias   \t";
	write(STDOUT_FILENO, msgom, _strlen(msgom));
	msgom = "alias [NAME[='VALUE'] ...]\n  cd    \tcd   ";
	write(STDOUT_FILENO, msgom, _strlen(msgom));
	msgom = "[DIRECTORY]\n  exit    \texit [STATUS]\n  env     \tenv";
	write(STDOUT_FILENO, msgom, _strlen(msgom));
	msgom = "\n  setenv  \tsetenv [VARIABLE] [VALUE]\n  unsetenv\t";
	write(STDOUT_FILENO, msgom, _strlen(msgom));
	msgom = "unsetenv [VARIABLE]\n";
	write(STDOUT_FILENO, msgom, _strlen(msgom));
}

/**
 * help_alias - Displays information on the shellby builtin command 'alias'.
 */
void help_alias(void)
{
	char *msgom = "alias: alias [NAME[='VALUE'] ...]\n\tHandles aliases.\n";

	write(STDOUT_FILENO, msgom, _strlen(msgom));
	msgom = "\n\talias: Prints a list of all aliases, one per line, in ";
	write(STDOUT_FILENO, msgom, _strlen(msgom));
	msgom = "the format NAME='VALUE'.\n\talias name [name2 ...]:prints";
	write(STDOUT_FILENO, msgom, _strlen(msgom));
	msgom = " the aliases name, name2, etc. one per line, in the ";
	write(STDOUT_FILENO, msgom, _strlen(msgom));
	msgom = "form NAME='VALUE'.\n\talias NAME='VALUE' [...]: Defines";
	write(STDOUT_FILENO, msgom, _strlen(msgom));
	msgom = " an alias for each NAME whose VALUE is given. If NAME ";
	write(STDOUT_FILENO, msgom, _strlen(msgom));
	msgom = "is already an alias, replace its value with VALUE.\n";
	write(STDOUT_FILENO, msgom, _strlen(msgom));
}

/**
 * help_cd - Displays information on the shellby builtin command 'cd'.
 */
void help_cd(void)
{
	char *msgom = "cd: cd [DIRECTORY]\n\tChanges the current directory of the";

	write(STDOUT_FILENO, msgom, _strlen(msgom));
	msgom = " process to DIRECTORY.\n\n\tIf no argument is given, the ";
	write(STDOUT_FILENO, msgom, _strlen(msgom));
	msgom = "command is interpreted as cd $HOME. If the argument '-' is";
	write(STDOUT_FILENO, msgom, _strlen(msgom));
	msgom = " given, the command is interpreted as cd $OLDPWD.\n\n";
	write(STDOUT_FILENO, msgom, _strlen(msgom));
	msgom = "\tThe environment variables PWD and OLDPWD are updated ";
	write(STDOUT_FILENO, msgom, _strlen(msgom));
	msgom = "after a change of directory.\n";
	write(STDOUT_FILENO, msgom, _strlen(msgom));
}

/**
 * help_exit - Displays information on the shellby builtin command 'exit'.
 */
void help_exit(void)
{
	char *msgom = "exit: exit [STATUS]\n\tExits the shell.\n\n\tThe ";

	write(STDOUT_FILENO, msgom, _strlen(msgom));
	msgom = "STATUS argument is the integer used to exit the shell.";
	write(STDOUT_FILENO, msgom, _strlen(msgom));
	msgom = " If no argument is given, the command is interpreted as";
	write(STDOUT_FILENO, msgom, _strlen(msgom));
	msgom = " exit 0.\n";
	write(STDOUT_FILENO, msgom, _strlen(msgom));
}

/**
 * help_help - Displays information on the shellby builtin command 'help'.
 */
void help_help(void)
{
	char *msgom = "help: help\n\tSee all possible Shellby builtin commands.\n";

	write(STDOUT_FILENO, msgom, _strlen(msgom));
	msgom = "\n      help [BUILTIN NAME]\n\tSee specific information on each ";
	write(STDOUT_FILENO, msgom, _strlen(msgom));
	msgom = "builtin command.\n";
	write(STDOUT_FILENO, msgom, _strlen(msgom));
}

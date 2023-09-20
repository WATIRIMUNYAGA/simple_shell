/*
 * File: helpere.c
 * Auth: Esther
 *       Mary
 */

#include "shell.h"

void free_args(char **args, char **front);
char *get_pid(void);
char *get_env_value(char *beginning, int len);
void variable_replacement(char **args, int *exe_ret);

/**
 * free_args - Frees up memory taken by args.
 * @args: A null-terminated double pointer containing commands/arguments.
 * @front: A double pointer to the beginning of args.
 */
void free_args(char **args, char **front)
{
	size_t ie;

	for (ie = 0; args[ie] || args[ie + 1]; ie++)
		free(args[ie]);

	free(front);
}

/**
 * get_pid - Gets the current process ID.
 * Description: Opens the stat file, a space-delimited file containing
 *              information about the current process. The PID is the
 *              first word in the file. The function reads the PID into
 *              a buffer and replace the space at the end with a \0 byte.
 *
 * Return: The current process ID or NULL on failure.
 */
char *get_pid(void)
{
	size_t ie = 0;
	char *buffer;
	ssize_t mfile;

	mfile = open("/proc/self/stat", O_RDONLY);
	if (mfile == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(mfile);
		return (NULL);
	}
	read(mfile, buffer, 120);
	while (buffer[ie] != ' ')
		ie++;
	buffer[ie] = '\0';

	close(mfile);
	return (buffer);
}

/**
 * get_env_value - Gets the value corresponding to an environmental variable.
 * @beginning: The environmental variable to search for.
 * @len: The length of the environmental variable to search for.
 *
 * Return: If the variable is not found - an empty string.
 *         Otherwise - the value of the environmental variable.
 *
 * Description: Variables are stored in the format VARIABLE=VALUE.
 */
char *get_env_value(char *beginning, int len)
{
	char **mvar_addr;
	char *mreplacement = NULL, *mtemp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beginning, len);

	mvar_addr = _getenv(var);
	free(var);
	if (mvar_addr)
	{
		mtemp = *mvar_addr;
		while (*mtemp != '=')
			mtemp++;
		mtemp++;
		mreplacement = malloc(_strlen(mtemp) + 1);
		if (mreplacement)
			_strcpy(mreplacement, mtemp);
	}

	return (mreplacement);
}

/**
 * variable_replacement - Handles variable replacement.
 * @line: A double pointer containing the command and arguments.
 * @exe_ret: A pointer to the return value of the last executed command.
 *
 * Description: Replaces $$ with the current PID, $? with the return value
 *              of the last executed program, and envrionmental variables
 *              preceded by $ with their corresponding value.
 */
void variable_replacement(char **line, int *exe_ret)
{
	int jm, ke = 0, len;
	char *mreplacement = NULL, *mold_line = NULL, *mnew_line;

	mold_line = *line;
	for (jm = 0; mold_line[jm]; jm++)
	{
		if (mold_line[jm] == '$' && mold_line[jm + 1] &&
				mold_line[jm + 1] != ' ')
		{
			if (mold_line[jm + 1] == '$')
			{
				mreplacement = get_pid();
				ke = jm + 2;
			}
			else if (mold_line[jm + 1] == '?')
			{
				mreplacement = _itoa(*exe_ret);
				ke = jm + 2;
			}
			else if (mold_line[jm + 1])
			{
				/* extract the variable name to search for */
				for (ke = jm + 1; mold_line[ke] &&
						mold_line[ke] != '$' &&
						mold_line[ke] != ' '; ke++)
					;
				len = ke - (jm + 1);
				mreplacement = get_env_value(&mold_line[jm + 1], len);
			}
			mnew_line = malloc(jm + _strlen(mreplacement)
					  + _strlen(&mold_line[ke]) + 1);
			if (!line)
				return;
			mnew_line[0] = '\0';
			_strncat(mnew_line, mold_line, jm);
			if (mreplacement)
			{
				_strcat(mnew_line, mreplacement);
				free(mreplacement);
				mreplacement = NULL;
			}
			_strcat(mnew_line, &mold_line[ke]);
			free(mold_line);
			*line = mnew_line;
			mold_line = mnew_line;
			jm = -1;
		}
	}
}

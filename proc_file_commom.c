#include "shell.h"

int cant_open(char *file_path);
int proc_file_commands(char *file_path, int *exe_ret);

/**
 * cant_open - If the file doesn't exist or lacks proper permissions, print
 * a cant open error.
 * @file_path: Path to the supposed file.
 *
 * Return: 127.
 */

int cant_open(char *file_path)
{
	char *merror, *mhist_str;
	int mlen;

	mhist_str = _itoa(hist);
	if (!mhist_str)
		return (127);

	mlen = _strlen(name) + _strlen(mhist_str) + _strlen(file_path) + 16;
	merror = malloc(sizeof(char) * (mlen + 1));
	if (!merror)
	{
		free(mhist_str);
		return (127);
	}

	_strcpy(merror, name);
	_strcat(merror, ": ");
	_strcat(merror, mhist_str);
	_strcat(merror, ": Can't open ");
	_strcat(merror, file_path);
	_strcat(merror, "\n");

	free(mhist_str);
	write(STDERR_FILENO, merror, mlen);
	free(merror);
	return (127);
}

/**
 * proc_file_commands - Takes a file and attempts to run the commands stored
 * within.
 * @file_path: Path to the file.
 * @exe_ret: Return value of the last executed command.
 *
 * Return: If file couldn't be opened - 127.
 *	   If malloc fails - -1.
 *	   Otherwise the return value of the last command ran.
 */
int proc_file_commands(char *file_path, int *exe_ret)
{
	ssize_t mfile, eread, i;
	unsigned int mline_size = 0;
	unsigned int mold_size = 120;
	char *line, **args, **front;
	char buffer[120];
	int ret;

	hist = 0;
	mfile = open(file_path, O_RDONLY);
	if (mfile == -1)
	{
		*exe_ret = cant_open(file_path);
		return (*exe_ret);
	}
	line = malloc(sizeof(char) * mold_size);
	if (!line)
		return (-1);
	do {
		eread = read(mfile, buffer, 119);
		if (eread == 0 && mline_size == 0)
			return (*exe_ret);
		buffer[eread] = '\0';
		mline_size += eread;
		line = _realloc(line, mold_size, mline_size);
		_strcat(line, buffer);
		mold_size = mline_size;
	} while (eread);
	for (i = 0; line[i] == '\n'; i++)
		line[i] = ' ';
	for (; i < mline_size; i++)
	{
		if (line[i] == '\n')
		{
			line[i] = ';';
			for (i += 1; i < mline_size && line[i] == '\n'; i++)
				line[i] = ' ';
		}
	}
	variable_replacement(&line, exe_ret);
	handle_line(&line, mline_size);
	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (0);
	if (check_args(args) != 0)
	{
		*exe_ret = 2;
		free_args(args, args);
		return (*exe_ret);
	}
	front = args;

	for (i = 0; args[i]; i++)
	{
		if (_strncmp(args[i], ";", 1) == 0)
		{
			free(args[i]);
			args[i] = NULL;
			ret = call_args(args, front, exe_ret);
			args = &args[++i];
			i = 0;
		}
	}

	ret = call_args(args, front, exe_ret);

	free(front);
	return (ret);
}

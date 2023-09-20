/*
 * File: errorse.c
 * Auth: Esther
 *       Mary
 */

#include "shell.h"

int num_len(int num);
char *_itoa(int num);
int create_error(char **args, int err);

/**
 * num_len - Counts the digit length of a number.
 * @num: The number to measure.
 *
 * Return: The digit length.
 */
int num_len(int num)
{
	unsigned int nume;
	int len = 1;

	if (num < 0)
	{
		len++;
		nume = num * -1;
	}
	else
	{
		nume = num;
	}
	while (nume > 9)
	{
		len++;
		nume /= 10;
	}

	return (len);
}

/**
 * _itoa - Converts an integer to a string.
 * @num: The integer.
 *
 * Return: The converted string.
 */
char *_itoa(int num)
{
	char *buffer;
	int len = num_len(num);
	unsigned int nume;

	buffer = malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (NULL);

	buffer[len] = '\0';

	if (num < 0)
	{
		nume = num * -1;
		buffer[0] = '-';
	}
	else
	{
		nume = num;
	}

	len--;
	do {
		buffer[len] = (nume % 10) + '0';
		nume /= 10;
		len--;
	} while (nume > 0);

	return (buffer);
}


/**
 * create_error - Writes a custom error message to stderr.
 * @args: An array of arguments.
 * @err: The error value.
 *
 * Return: The error value.
 */
int create_error(char **args, int err)
{
	char *errore;

	switch (err)
	{
	case -1:
		errore = error_env(args);
		break;
	case 1:
		errore = error_1(args);
		break;
	case 2:
		if (*(args[0]) == 'e')
			errore = error_2_exit(++args);
		else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
			errore = error_2_syntax(args);
		else
			errore = error_2_cd(args);
		break;
	case 126:
		errore = error_126(args);
		break;
	case 127:
		errore = error_127(args);
		break;
	}
	write(STDERR_FILENO, errore, _strlen(errore));

	if (errore)
		free(errore);
	return (err);

}

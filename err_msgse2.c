/*
 * File: err_msgse.c
 * Auth: Esther
 *       Mary
 */

#include "shell.h"

char *error_126(char **args);
char *error_127(char **args);

/**
 * error_126 - Creates an error message for permission denied failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_126(char **args)
{
	char *errore, *hist_stre;
	int len;

	hist_stre = _itoa(hist);
	if (!hist_stre)
		return (NULL);

	len = _strlen(name) + _strlen(hist_stre) + _strlen(args[0]) + 24;
	errore = malloc(sizeof(char) * (len + 1));
	if (!errore)
	{
		free(hist_stre);
		return (NULL);
	}

	_strcpy(errore, name);
	_strcat(errore, ": ");
	_strcat(errore, hist_stre);
	_strcat(errore, ": ");
	_strcat(errore, args[0]);
	_strcat(errore, ": Permission denied\n");

	free(hist_stre);
	return (errore);
}

/**
 * error_127 - Creates an error message for command not found failures.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_127(char **args)
{
	char *errore, *hist_stre;
	int len;

	hist_stre = _itoa(hist);
	if (!hist_stre)
		return (NULL);

	len = _strlen(name) + _strlen(hist_stre) + _strlen(args[0]) + 16;
	errore = malloc(sizeof(char) * (len + 1));
	if (!errore)
	{
		free(hist_stre);
		return (NULL);
	}

	_strcpy(errore, name);
	_strcat(errore, ": ");
	_strcat(errore, hist_stre);
	_strcat(errore, ": ");
	_strcat(errore, args[0]);
	_strcat(errore, ": not found\n");

	free(hist_stre);
	return (errore);
}

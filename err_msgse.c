/*
 * File: err_msgse.c
 * Auth: Esther
 *       Mary
 */

#include "shell.h"

char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
/**
 * error_env - Creates an error message for shellby_env errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_env(char **args)
{
	char *error, *hist_stre;
	int lene;

	hist_stre = _itoa(hist);
	if (!hist_stre)
		return (NULL);

	args--;
	lene = _strlen(name) + _strlen(hist_stre) + _strlen(args[0]) + 45;
	error = malloc(sizeof(char) * (lene + 1));
	if (!error)
	{
		free(hist_stre);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_stre);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": Unable to add/remove from environment\n");

	free(hist_stre);
	return (error);
}

/**
 * error_1 - Creates an error message for shellby_alias errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_1(char **args)
{
	char *error;
	int lene;

	lene = _strlen(name) + _strlen(args[0]) + 13;
	error = malloc(sizeof(char) * (lene + 1));
	if (!error)
		return (NULL);

	_strcpy(error, "alias: ");
	_strcat(error, args[0]);
	_strcat(error, " not found\n");

	return (error);
}

/**
 * error_2_exit - Creates an error message for shellby_exit errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_exit(char **args)
{
	char *errore, *hist_stre;
	int lene;

	hist_stre = _itoa(hist);
	if (!hist_stre)
		return (NULL);

	lene = _strlen(name) + _strlen(hist_stre) + _strlen(args[0]) + 27;
	errore = malloc(sizeof(char) * (lene + 1));
	if (!errore)
	{
		free(hist_stre);
		return (NULL);
	}

	_strcpy(errore, name);
	_strcat(errore, ": ");
	_strcat(errore, hist_stre);
	_strcat(errore, ": exit: Illegal number: ");
	_strcat(errore, args[0]);
	_strcat(errore, "\n");

	free(hist_stre);
	return (errore);
}

/**
 * error_2_cd - Creates an error message for shellby_cd errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_cd(char **args)
{
	char *errore, *hist_stre;
	int lene;

	hist_stre = _itoa(hist);
	if (!hist_stre)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
	lene = _strlen(name) + _strlen(hist_stre) + _strlen(args[0]) + 24;
	errore = malloc(sizeof(char) * (lene + 1));
	if (!errore)
	{
		free(hist_stre);
		return (NULL);
	}

	_strcpy(errore, name);
	_strcat(errore, ": ");
	_strcat(errore, hist_stre);
	if (args[0][0] == '-')
		_strcat(errore, ": cd: Illegal option ");
	else
		_strcat(errore, ": cd: can't cd to ");
	_strcat(errore, args[0]);
	_strcat(errore, "\n");

	free(hist_stre);
	return (errore);
}

/**
 * error_2_syntax - Creates an error message for syntax errores.
 * @args: An array of arguments passed to the command.
 *
 * Return: The errore string.
 */
char *error_2_syntax(char **args)
{
	char *errore, *hist_stre;
	int lene;

	hist_stre = _itoa(hist);
	if (!hist_stre)
		return (NULL);

	lene = _strlen(name) + _strlen(hist_stre) + _strlen(args[0]) + 33;
	errore = malloc(sizeof(char) * (lene + 1));
	if (!errore)
	{
		free(hist_stre);
		return (NULL);
	}

	_strcpy(errore, name);
	_strcat(errore, ": ");
	_strcat(errore, hist_stre);
	_strcat(errore, ": Syntax error: \"");
	_strcat(errore, args[0]);
	_strcat(errore, "\" unexpected\n");

	free(hist_stre);
	return (errore);
}

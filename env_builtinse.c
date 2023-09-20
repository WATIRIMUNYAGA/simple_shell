/*
 * File: env_builtine.c
 * Auth: Esther
 *       Mary
 */

#include "shell.h"

int shellby_env(char **args, char __attribute__((__unused__)) **front);
int shellby_setenv(char **args, char __attribute__((__unused__)) **front);
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front);

/**
 * shellby_env - Prints the current environment.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *	   Otherwise - 0.
 *
 * Description: Prints one variable per line in the
 *              format 'variable'='value'.
 */
int shellby_env(char **args, char __attribute__((__unused__)) **front)
{
	int indexm;
	char n = '\n';

	if (!environ)
		return (-1);

	for (indexm = 0; environ[indexm]; indexm++)
	{
		write(STDOUT_FILENO, environ[indexm], _strlen(environ[indexm]));
		write(STDOUT_FILENO, &n, 1);
	}

	(void)args;
	return (0);
}

/**
 * shellby_setenv - Changes or adds an environmental variable to the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the name of the new or existing PATH variable.
 *              args[2] is the value to set the new or changed variable to.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shellby_setenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_varm = NULL, **new_environe, *new_val2;
	size_t size;
	int indexm;

	if (!args[0] || !args[1])
		return (create_error(args, -1));

	new_val2 = malloc(_strlen(args[0]) + 1 + _strlen(args[1]) + 1);
	if (!new_val2)
		return (create_error(args, -1));
	_strcpy(new_val2, args[0]);
	_strcat(new_val2, "=");
	_strcat(new_val2, args[1]);

	env_varm = _getenv(args[0]);
	if (env_varm)
	{
		free(*env_varm);
		*env_varm = new_val2;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environe = malloc(sizeof(char *) * (size + 2));
	if (!new_environe)
	{
		free(new_val2);
		return (create_error(args, -1));
	}

	for (indexm = 0; environ[indexm]; indexm++)
		new_environe[indexm] = environ[indexm];

	free(environ);
	environ = new_environe;
	environ[indexm] = new_val2;
	environ[indexm + 1] = NULL;

	return (0);
}

/**
 * shellby_unsetenv - Deletes an environmental variable from the PATH.
 * @args: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of args.
 * Description: args[1] is the PATH variable to remove.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shellby_unsetenv(char **args, char __attribute__((__unused__)) **front)
{
	char **env_varm, **new_environe;
	size_t size;
	int indexm, indexm2;

	if (!args[0])
		return (create_error(args, -1));
	env_varm = _getenv(args[0]);
	if (!env_varm)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environe = malloc(sizeof(char *) * size);
	if (!new_environe)
		return (create_error(args, -1));

	for (indexm = 0, indexm2 = 0; environ[indexm]; indexm++)
	{
		if (*env_varm == environ[indexm])
		{
			free(*env_varm);
			continue;
		}
		new_environe[indexm2] = environ[indexm];
		indexm2++;
	}
	free(environ);
	environ = new_environe;
	environ[size - 1] = NULL;

	return (0);
}

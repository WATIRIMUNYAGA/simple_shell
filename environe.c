/*
 * File: environe.c
 * Auth: Esther
 *       Mary
 */

#include "shell.h"

char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/**
 * _copyenv - Creates a copy of the environment.
 *
 * Return: If an error occurs - NULL.
 *         O/w - a double pointer to the new copy.
 */
char **_copyenv(void)
{
	char **new_environm;
	size_t size;
	int indexm;

	for (size = 0; environ[size]; size++)
		;

	new_environm = malloc(sizeof(char *) * (size + 1));
	if (!new_environm)
		return (NULL);

	for (indexm = 0; environ[indexm]; indexm++)
	{
		new_environm[indexm] = malloc(_strlen(environ[indexm]) + 1);

		if (!new_environm[indexm])
		{
			for (indexm--; indexm >= 0; indexm--)
				free(new_environm[indexm]);
			free(new_environm);
			return (NULL);
		}
		_strcpy(new_environm[indexm], environ[indexm]);
	}
	new_environm[indexm] = NULL;

	return (new_environm);
}

/**
 * free_env - Frees the the environment copy.
 */
void free_env(void)
{
	int indexe;

	for (indexe = 0; environ[indexe]; indexe++)
		free(environ[indexe]);
	free(environ);
}

/**
 * _getenv - Gets an environmental variable from the PATH.
 * @var: The name of the environmental variable to get.
 *
 * Return: If the environmental variable does not exist - NULL.
 *         Otherwise - a pointer to the environmental variable.
 */
char **_getenv(const char *var)
{
	int indexe, mlen;

	mlen = _strlen(var);
	for (indexe = 0; environ[indexe]; indexe++)
	{
		if (_strncmp(var, environ[indexe], mlen) == 0)
			return (&environ[indexe]);
	}

	return (NULL);
}

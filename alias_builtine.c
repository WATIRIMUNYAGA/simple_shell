/*
 * File: builtine.c
 * Auth: Mary
 *       Esther
 */

#include "shell.h"

int shellby_alias(char **args, char __attribute__((__unused__)) **front);
void set_alias(char *var_name, char *value);
void print_alias(alias_t *alias);

/**
 * shellby_alias - Builtin command that either prints all aliases, specific
 * aliases, or sets an alias.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int shellby_alias(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *metemp = aliases;
	int ie, mrete = 0;
	char *value;

	if (!args[0])
	{
		while (metemp)
		{
			print_alias(metemp);
			metemp = metemp->next;
		}
		return (mrete);
	}
	for (ie = 0; args[ie]; ie++)
	{
		metemp = aliases;
		value = _strchr(args[ie], '=');
		if (!value)
		{
			while (metemp)
			{
				if (_strcmp(args[ie], metemp->name) == 0)
				{
					print_alias(metemp);
					break;
				}
				metemp = metemp->next;
			}
			if (!metemp)
				mrete = create_error(args + ie, 1);
		}
		else
			set_alias(args[ie], value);
	}
	return (mrete);
}

/**
 * set_alias - Will either set an existing alias 'name' with a new value,
 * 'value' or creates a new alias with 'name' and 'value'.
 * @var_name: Name of the alias.
 * @value: Value of the alias. First character is a '='.
 */
void set_alias(char *var_name, char *value)
{
	alias_t *metemp = aliases;
	int len, jm, ke;
	char *new_val;

	*value = '\0';
	value++;
	len = _strlen(value) - _strspn(value, "'\"");
	new_val = malloc(sizeof(char) * (len + 1));
	if (!new_val)
		return;
	for (jm = 0, ke = 0; value[jm]; jm++)
	{
		if (value[jm] != '\'' && value[jm] != '"')
			new_val[ke++] = value[jm];
	}
	new_val[ke] = '\0';
	while (metemp)
	{
		if (_strcmp(var_name, metemp->name) == 0)
		{
			free(metemp->value);
			metemp->value = new_val;
			break;
		}
		metemp = metemp->next;
	}
	if (!metemp)
		add_alias_end(&aliases, var_name, new_val);
}

/**
 * print_alias - Prints the alias in the format name='value'.
 * @alias: Pointer to an alias.
 */
void print_alias(alias_t *alias)
{
	char *alias_stringe;
	int len = _strlen(alias->name) + _strlen(alias->value) + 4;

	alias_stringe = malloc(sizeof(char) * (len + 1));
	if (!alias_stringe)
		return;
	_strcpy(alias_stringe, alias->name);
	_strcat(alias_stringe, "='");
	_strcat(alias_stringe, alias->value);
	_strcat(alias_stringe, "'\n");

	write(STDOUT_FILENO, alias_stringe, len);
	free(alias_stringe);
}
/**
 * replace_aliases - Goes through the arguments and replace any matching alias
 * with their value.
 * @args: 2D pointer to the arguments.
 *
 * Return: 2D pointer to the arguments.
 */
char **replace_aliases(char **args)
{
	alias_t *metemp;
	int ie;
	char *new_val;

	if (_strcmp(args[0], "alias") == 0)
		return (args);
	for (ie = 0; args[ie]; ie++)
	{
		metemp = aliases;
		while (metemp)
		{
			if (_strcmp(args[ie], metemp->name) == 0)
			{
				new_val = malloc(sizeof(char) * (_strlen(metemp->value) + 1));
				if (!new_val)
				{
					free_args(args, args);
					return (NULL);
				}
				_strcpy(new_val, metemp->value);
				free(args[ie]);
				args[ie] = new_val;
				ie--;
				break;
			}
			metemp = metemp->next;
		}
	}

	return (args);
}


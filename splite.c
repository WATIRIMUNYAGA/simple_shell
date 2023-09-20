/*
 * File: splite.c
 * Auth: Esther
 *       Mary
 */

#include "shell.h"

int token_len(char *str, char *delim);
int count_tokens(char *str, char *delim);
char **_strtok(char *line, char *delim);

/**
 * token_len - Locates the delimiter indexe marking the end
 *             of the first token contained within a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The delimiter indexe marking the end of
 *         the intitial token pointed to be str.
 */
int token_len(char *str, char *delim)
{
	int indexe = 0, mlen = 0;

	while (*(str + indexe) && *(str + indexe) != *delim)
	{
		mlen++;
		indexe++;
	}

	return (mlen);
}

/**
 * count_tokens - Counts the number of delimited
 *                words contained within a string.
 * @str: The string to be searched.
 * @delim: The delimiter character.
 *
 * Return: The number of words contained within str.
 */
int count_tokens(char *str, char *delim)
{
	int indexe, tokens = 0, len = 0;

	for (indexe = 0; *(str + indexe); indexe++)
		len++;

	for (indexe = 0; indexe < len; indexe++)
	{
		if (*(str + indexe) != *delim)
		{
			tokens++;
			indexe += token_len(str + indexe, delim);
		}
	}

	return (tokens);
}

/**
 * _strtok - Tokenizes a string.
 * @line: The string.
 * @delim: The delimiter character to tokenize the string by.
 *
 * Return: A pointer to an array containing the tokenized words.
 */
char **_strtok(char *line, char *delim)
{
	char **ptr;
	int indexe = 0, tokens, t, letters, l;

	tokens = count_tokens(line, delim);
	if (tokens == 0)
		return (NULL);

	ptr = malloc(sizeof(char *) * (tokens + 2));
	if (!ptr)
		return (NULL);

	for (t = 0; t < tokens; t++)
	{
		while (line[indexe] == *delim)
			indexe++;

		letters = token_len(line + indexe, delim);

		ptr[t] = malloc(sizeof(char) * (letters + 1));
		if (!ptr[t])
		{
			for (indexe -= 1; indexe >= 0; indexe--)
				free(ptr[indexe]);
			free(ptr);
			return (NULL);
		}

		for (l = 0; l < letters; l++)
		{
			ptr[t][l] = line[indexe];
			indexe++;
		}

		ptr[t][l] = '\0';
	}
	ptr[t] = NULL;
	ptr[t + 1] = NULL;

	return (ptr);
}

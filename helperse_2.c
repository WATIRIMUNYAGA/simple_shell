/*
 * File: helperse_2.c
 * Auth: Mary
 *       Esther
 */

#include "shell.h"

void handle_line(char **line, ssize_t read);
ssize_t get_new_len(char *line);
void logical_ops(char *line, ssize_t *new_len);

/**
 * handle_line - Partitions a line read from standard input as needed.
 * @line: A pointer to a line read from standard input.
 * @read: The length of line.
 *
 * Description: Spaces are inserted to separate ";", "||", and "&&".
 *              Replaces "#" with '\0'.
 */
void handle_line(char **line, ssize_t read)
{
	char *old_linen, *mnew_line;
	char previous_om, mcurrent, next;
	size_t i, jm;
	ssize_t new_leme;

	new_leme = get_new_len(*line);
	if (new_leme == read - 1)
		return;
	mnew_line = malloc(new_leme + 1);
	if (!mnew_line)
		return;
	jm = 0;
	old_linen = *line;
	for (i = 0; old_linen[i]; i++)
	{
		mcurrent = old_linen[i];
		next = old_linen[i + 1];
		if (i != 0)
		{
			previous_om = old_linen[i - 1];
			if (mcurrent == ';')
			{
				if (next == ';' && previous_om != ' ' && previous_om != ';')
				{
					mnew_line[jm++] = ' ';
					mnew_line[jm++] = ';';
					continue;
				}
				else if (previous_om == ';' && next != ' ')
				{
					mnew_line[jm++] = ';';
					mnew_line[jm++] = ' ';
					continue;
				}
				if (previous_om != ' ')
					mnew_line[jm++] = ' ';
				mnew_line[jm++] = ';';
				if (next != ' ')
					mnew_line[jm++] = ' ';
				continue;
			}
			else if (mcurrent == '&')
			{
				if (next == '&' && previous_om != ' ')
					mnew_line[jm++] = ' ';
				else if (previous_om == '&' && next != ' ')
				{
					mnew_line[jm++] = '&';
					mnew_line[jm++] = ' ';
					continue;
				}
			}
			else if (mcurrent == '|')
			{
				if (next == '|' && previous_om != ' ')
					mnew_line[jm++]  = ' ';
				else if (previous_om == '|' && next != ' ')
				{
					mnew_line[jm++] = '|';
					mnew_line[jm++] = ' ';
					continue;
				}
			}
		}
		else if (mcurrent == ';')
		{
			if (i != 0 && old_linen[i - 1] != ' ')
				mnew_line[jm++] = ' ';
			mnew_line[jm++] = ';';
			if (next != ' ' && next != ';')
				mnew_line[jm++] = ' ';
			continue;
		}
		mnew_line[jm++] = old_linen[i];
	}
	mnew_line[jm] = '\0';

	free(*line);
	*line = mnew_line;
}

/**
 * get_new_len - Gets the new length of a line partitioned
 *               by ";", "||", "&&&", or "#".
 * @line: The line to check.
 *
 * Return: The new length of the line.
 *
 * Description: Cuts short lines containing '#' comments with '\0'.
 */

ssize_t get_new_len(char *line)
{
	size_t i;
	ssize_t new_leme = 0;
	char mcurrent, enext;

	for (i = 0; line[i]; i++)
	{
		mcurrent = line[i];
		enext = line[i + 1];
		if (mcurrent == '#')
		{
			if (i == 0 || line[i - 1] == ' ')
			{
				line[i] = '\0';
				break;
			}
		}
		else if (i != 0)
		{
			if (mcurrent == ';')
			{
				if (enext == ';' && line[i - 1] != ' ' && line[i - 1] != ';')
				{
					new_leme += 2;
					continue;
				}
				else if (line[i - 1] == ';' && enext != ' ')
				{
					new_leme += 2;
					continue;
				}
				if (line[i - 1] != ' ')
					new_leme++;
				if (enext != ' ')
					new_leme++;
			}
			else
				logical_ops(&line[i], &new_leme);
		}
		else if (mcurrent == ';')
		{
			if (i != 0 && line[i - 1] != ' ')
				new_leme++;
			if (enext != ' ' && enext != ';')
				new_leme++;
		}
		new_leme++;
	}
	return (new_leme);
}
/**
 * logical_ops - Checks a line for logical operators "||" or "&&".
 * @line: A pointer to the character to check in the line.
 * @new_len: Pointer to new_len in get_new_len function.
 */
void logical_ops(char *line, ssize_t *new_len)
{
	char previous_om, mcurrent, enext;

	previous_om = *(line - 1);
	mcurrent = *line;
	enext = *(line + 1);

	if (mcurrent == '&')
	{
		if (enext == '&' && previous_om != ' ')
			(*new_len)++;
		else if (previous_om == '&' && enext != ' ')
			(*new_len)++;
	}
	else if (mcurrent == '|')
	{
		if (enext == '|' && previous_om != ' ')
			(*new_len)++;
		else if (previous_om == '|' && enext != ' ')
			(*new_len)++;
	}
}

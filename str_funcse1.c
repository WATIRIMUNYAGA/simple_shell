/*
 * File: str_funcse.c
 * Auth: Esther
 *       Brian
 */

#include "shell.h"

int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);

/**
 * _strlen - Returns the length of a string.
 * @s: A pointer to the characters string.
 *
 * Return: The mlength of the character string.
 */
int _strlen(const char *s)
{
	int mlength = 0;

	if (!s)
		return (mlength);
	for (mlength = 0; s[mlength]; mlength++)
		;
	return (mlength);
}

/**
 * _strcpy - Copies the string pointed to by src, including the
 *           terminating null byte, to the buffer pointed by des.
 * @dest: Pointer to the destination of copied string.
 * @src: Pointer to the src of the source string.
 *
 * Return: Pointer to dest.
 */
char *_strcpy(char *dest, const char *src)
{
	size_t ie;

	for (ie = 0; src[ie] != '\0'; ie++)
		dest[ie] = src[ie];
	dest[ie] = '\0';
	return (dest);
}

/**
 * _strcat - Concantenates two strings.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 *
 * Return: Pointer to destination string.
 */
char *_strcat(char *dest, const char *src)
{
	char *mdestTemp;
	const char *msrcTemp;

	mdestTemp = dest;
	msrcTemp =  src;

	while (*mdestTemp != '\0')
		mdestTemp++;

	while (*msrcTemp != '\0')
		*mdestTemp++ = *msrcTemp++;
	*mdestTemp = '\0';
	return (dest);
}

/**
 * _strncat - Concantenates two strings where n number
 *            of bytes are copied from source.
 * @dest: Pointer to destination string.
 * @src: Pointer to source string.
 * @n: n bytes to copy from src.
 *
 * Return: Pointer to destination string.
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t mdest_lene = _strlen(dest);
	size_t ie;

	for (ie = 0; ie < n && src[ie] != '\0'; ie++)
		dest[mdest_lene + ie] = src[ie];
	dest[mdest_lene + ie] = '\0';

	return (dest);
}

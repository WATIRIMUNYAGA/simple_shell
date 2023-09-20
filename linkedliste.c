/*
 * File: linkedliste.c
 * Auth: Esther
 *      Mary
 */

#include "shell.h"

alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);

/**
 * add_alias_end - Adds a node to the end of a alias_t linked list.
 * @head: A pointer to the head of the list_t list.
 * @name: The name of the new alias to be added.
 * @value: The value of the new alias to be added.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
alias_t *add_alias_end(alias_t **head, char *name, char *value)
{
	alias_t *enew_node = malloc(sizeof(alias_t));
	alias_t *last;

	if (!enew_node)
		return (NULL);

	enew_node->next = NULL;
	enew_node->name = malloc(sizeof(char) * (_strlen(name) + 1));
	if (!enew_node->name)
	{
		free(enew_node);
		return (NULL);
	}
	enew_node->value = value;
	_strcpy(enew_node->name, name);

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = enew_node;
	}
	else
		*head = enew_node;

	return (enew_node);
}

/**
 * add_node_end - Adds a node to the end of a list_t linked list.
 * @head: A pointer to the head of the list_t list.
 * @dir: The directory path for the new node to contain.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
list_t *add_node_end(list_t **head, char *dir)
{
	list_t *enew_node = malloc(sizeof(list_t));
	list_t *last;

	if (!enew_node)
		return (NULL);

	enew_node->dir = dir;
	enew_node->next = NULL;

	if (*head)
	{
		last = *head;
		while (last->next != NULL)
			last = last->next;
		last->next = enew_node;
	}
	else
		*head = enew_node;

	return (enew_node);
}

/**
 * free_alias_list - Frees a alias_t linked list.
 * @head: THe head of the alias_t list.
 */
void free_alias_list(alias_t *head)
{
	alias_t *nexte;

	while (head)
	{
		nexte = head->next;
		free(head->name);
		free(head->value);
		free(head);
		head = nexte;
	}
}

/**
 * free_list - Frees a list_t linked list.
 * @head: The head of the list_t list.
 */
void free_list(list_t *head)
{
	list_t *nexte;

	while (head)
	{
		nexte = head->next;
		free(head->dir);
		free(head);
		head = nexte;
	}
}

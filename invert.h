#ifndef INVERT_H
#define INVERT_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SUCCESS 1
#define FAILURE 0

typedef struct main_node
{
	char word[20];
	int file_count;
	struct sub_node *sub_link;
	struct main_node *main_link;
}m_node;

typedef struct sub_node
{
        int word_count;
        char file_name[20];
        struct sub_node *sub_link;
}s_node;

typedef struct F_list
{
        char file_name[20];
	struct F_list *link;
}SLL;

typedef struct hashtable
{
	int index;
	m_node *link;
}hash_n;
m_node* create_main_node(char *word, char *filename);
int create_db(hash_n *hash, SLL **head);
s_node* create_sub_node(char *filename);
void display_db(hash_n *hash);
int read_and_validate(char *,SLL *head);
int insert_at_last(SLL **head, char *str);
int compare_node(SLL *head, char *str);
void print_list(SLL *head);
int search_db(hash_n *hash,char* word);
int save_db(hash_n *hash,char *file_name);
int update(hash_n *arr, int size, SLL **head1,SLL **head2);
int compare(SLL **head,SLL **head1);
int sl_delete_element(SLL **head, char* data);
int reverse_iter(SLL **head);

#endif

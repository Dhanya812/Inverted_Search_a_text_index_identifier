#include "invert.h"

int compare_list(SLL **head1, char *data) 		//compare list
{
	SLL *update = *head1;
	if(*head1 == NULL)
	{
		insert_at_last(head1, data);
		return SUCCESS;
	}
	while(update != NULL)
	{
		if(strcmp(update->file_name, data) == 0)
		{
			return FAILURE;
		}
		update = update->link;
	}
	insert_at_last(head1, data);
	return SUCCESS;
}
int update(hash_n *arr, int size, SLL **head1,SLL **head2)		//update database
{
	char inp[20];
	printf("Enter the filename from which you want to backup the data to the database: ");
	scanf(" %s",inp);
	for(int i = 0; i < size; i++)
	{
		if(arr[i].link != NULL)
		{
			printf("Error: The database is not empty\n");
			return FAILURE;
		}
	}
	if(strcmp((strchr(inp, '.')), ".txt") != 0)		//checking .txt file
	{
		printf("The given input file is not a valid file, So you can not perform update database operation.\n");
                return FAILURE;
	}
	FILE *fp = fopen(inp, "r");
	if(fp == NULL)
	{
		printf("Error: Unable to open the file\n");
		return FAILURE;
	}
	char c = 0;
	fseek(fp,0,SEEK_SET);
	char ch = 0;
	ch = fgetc(fp);
	if(ch == '#')
	{
		printf("\n");
		fseek(fp,-2,SEEK_END);
		c = fgetc(fp);
		if(c != '#')
		{
			printf("The given input file is not a valid file, So you can not perform update database operation.\n");
			fclose(fp);
                        return FAILURE;
		}
		printf("The given input file is a valid file, you can perform the update database operation\n");
	}
	else
	{
		printf("The given input file is not a valid file, So you can not perform update database operation.\n");
		fclose(fp);
		return FAILURE;
	}
	rewind(fp);
	char line[30];
	int ind;
	rewind(fp);
	while(fscanf(fp, "%s", line) != EOF)
	{
		int count = 0;
		char *token = strtok(line, "#;");
		ind = atoi(token);
		token = strtok(NULL, "#;");
		char word[20];
		if(token != NULL)
		strcpy(word, token);
		token = strtok(NULL, "#;");
		if(token != NULL)
		count = atoi(token);
		token = strtok(NULL, "#;");
		char file[20];
		if(token != NULL)
		strcpy(file, token);
		m_node *new = create_main_node(word, file);
		if(new == NULL)
		{
			printf("The main_node not created\n");
			return FAILURE;
		}
		if(arr[ind].link == NULL)
		{
		arr[ind].link = new;
		}
		else
		{
			new->main_link = arr[ind].link;
			arr[ind].link = new;
		}
		m_node *temp = arr[ind].link;
		temp->file_count = count;
		s_node *temp1 = temp->sub_link;
		while(temp1 != NULL)
		{
			compare_list(head1, file);
			strcpy(temp1->file_name, file);
			token = strtok(NULL, "#;");
                        temp1->word_count = atoi(token);
			token = strtok(NULL, "#;");
			if(token == NULL)
			{
				temp1->sub_link = NULL;
				break;
			}
			else
			{
				strcpy(file, token);
				s_node *new1 = create_sub_node(file);
				temp1->sub_link = new1;
			}
                        temp1 = temp1->sub_link;
		}
	}
	*head2 = *head1;
	print_list(*head2);
	fclose(fp);
        return SUCCESS;
}


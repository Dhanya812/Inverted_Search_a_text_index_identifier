/*NAME:DHANYA GUDIGAR
DATE : 16-12-2024
PROJECT NAME : INVERTED SEARCH
brief : The purpose of storing an index is to optimize speed and performance in finding relevant documents for a search query. Without an index, the search engine would scan every document in the corpus, which would require considerable time and computing power.
Prerequisite: ● Hashing
	      ● Single linked list
*/
#include"invert.h"
#include<string.h>
int read_and_validate(char *str,SLL *head)		//read and validate function
{
//	SLL *head = NULL;
	if(strcmp(strchr(str,'.'),".txt") != 0) 	//check the files is .txt
	{
		printf("ERROR : the fileis not .txt file\n");
		return FAILURE;
	}
	else
	{
		printf("INFO : the file is .txt file\n");
	}
	FILE *fp = fopen(str,"r");                      //check the file ispresent
	if(fp == NULL)
	{
		printf("ERROR : the file is not present\n");
		return FAILURE;
	}
	else
	{
		printf("INFO : the file is present\n");
	}
	fseek(fp,0,SEEK_END);
	long size = ftell(fp);
	//printf("size is %ld\n",size);
	if(size == 0)                                 //check the file is empty or not
	{
		printf("ERROR : the file is empty\n");
		return FAILURE;
	}
	else
	{
		printf("INFO : the file is not empty\n");
	}
	if(compare_node(head,str) == FAILURE)           //check the file isexist in list
	{
		printf("ERROR : this file is already existing in the list\n");
		return FAILURE;
	}
	else
	{
		printf("INFO : this file is not existing in the list\n");
	}

	return SUCCESS;
}
int insert_at_last(SLL **head, char *str)		//insert at first
{
	SLL *new = malloc(sizeof(SLL));
	if(new == NULL)
	{
		return FAILURE;
	}
	strcpy(new->file_name,str);
	new->link = NULL;

	if(*head == NULL)
	{
		*head = new;
		return SUCCESS;
	}
	else
	{
		SLL *temp = *head;
		while(temp->link !=NULL)
		{
			temp = temp->link;
		}
		temp->link = new;
		return SUCCESS;
	}
}

int compare_node(SLL *head, char *str)		//comparing node
{
	//printf("entered cmpare\n");
		SLL *temp = head;
		while(temp != NULL)
		{
		//	printf("%s\n",str);
			if(strcmp(temp->file_name,str) == 0)
			{
				printf("%s and %s\n",temp->file_name,str);
				return FAILURE;
			}
			temp = temp->link;
		}
//	}
	return SUCCESS;
}

void print_list(SLL *head){		//print the list
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
	else
	{
		while (head)		
		{
			printf("%s -> ", head -> file_name);
			head = head -> link;
		}

		printf("NULL\n");
	}
}
int reverse_iter(SLL **head) 		//reverse the iteration
{ 
    if(*head == NULL)
    {
        return FAILURE;
    }
    {
    SLL *cur = *head;
    SLL *next = *head;
    SLL *prev = NULL;
    while(next != NULL)  
    {
        next = cur->link;
        cur ->link = prev;
        prev = cur;
        cur = next;
    }
    *head = prev;
    return SUCCESS;
    }
    
} 

int sl_delete_element(SLL **head, char* file_name) {  		//delete the element
    if (*head == NULL) {
        return FAILURE;
    }

    SLL *temp = *head;
    SLL *prev = NULL;

    while (temp != NULL) {
        if(strcmp(temp->file_name,file_name)==0)
       	{
            if (prev == NULL) { // Deleting the first node
                *head = temp->link;
            } else {
                prev->link = temp->link;
            }
            free(temp);
            return SUCCESS;
        }
        prev = temp;
        temp = temp->link;
    }

    return FAILURE;
}
int compare(SLL **head,SLL **head1)		//compare the original list and update list
{
	SLL *temp = *head;
	reverse_iter(head1);
	print_list(*head1);
	SLL *temp1 = *head1;
	while(temp1 != NULL || temp != NULL)
	{
		if(strcmp(temp->file_name,temp1->file_name) == 0)
		{
			sl_delete_element(head,temp1->file_name);
			temp = temp->link;
			temp1 = temp1->link;
		}
		else
			return SUCCESS;
		if(temp != NULL && temp1 ==NULL)
		{
			return SUCCESS;
		}
	}
	return FAILURE;
}
		
			
int main(int argc,char *argv[])
{
	SLL *head = NULL;
	SLL *head1 = NULL;
	hash_n hash[27] = {0};
	char word[20];
	char file_name[20];
	int size = 26;	
	for(int i=1;i<argc;i++)
	{
		printf("\t-----%s-----\n",argv[i]);
		if((read_and_validate(argv[i],head)) == FAILURE)   		//checking valiation
		{
			printf("ERROR : the validation failed\n\n");
		}
		else
		{

			printf("INFO : The %s file validation is successful\n\n",argv[i]);
			//		printf("repeated i = %d\n",i);
			insert_at_last(&head,argv[i]);
			//		printf("insert successful\n");
		}
	}
	//printf("loop exit\n");
	print_list(head);
	int opt;
	int flag = 0;
	int flag2 = 0;
	int flag1 = 0;
	while(1)
	{
		printf("------------------------------------------\n");
		printf("Enter the option to be performed in menu :\n");
		printf("------------------------------------------\n");
		printf("1.Create Database\n2.Display Database\n3.Search Database\n4.Save Database\n5.Update Database\n6.Exit\n");
		scanf("%d",&opt);
		switch(opt)
		{
			case 1:
				printf("----------Create Database------------\n");
				if(flag == 1)
				{
//					printf("hii\n");
//					print_list(head1);
				     compare(&head,&head1);
				     flag = 0 ;
				}
				if(flag2 == 0)
				{
				if(create_db(hash,&head) == SUCCESS)
				{
					printf("INFO : Created database successfully\n\n");
					flag2 = 1;
				}
				else

				{
					printf("ERROR : Failed to created database\n");
				}
				}
				else
					printf("ERROR : Creation is already done\n");
				break;
			case 2:
				printf("----------Display Database-----------\n");
				display_db(hash);
				break;
			case 3:
				printf("-----------Search Database---------\n");
				printf("Enter the word to be searched\n");
				scanf("%s",word);
				search_db(hash,word);
				printf("INFO : Search element successful\n");
				break;
			case 4:
				printf("-----------Save Database-----------\n");
				printf("Enter the file name\n");
				scanf("%s",file_name);
				save_db(hash,file_name);
				printf("INFO : Save database successful\n");
				break;
			case 5:
				printf("---------Update Database-----------\n");
				if(flag1 == 0)
				{
				//if((compare(&head,&head1) == FAILURE))
				if(update(hash,size,&head,&head1)== SUCCESS)
					//print_list(head1);
				{
				
					print_list(head1);
					flag1 = 1;
				flag = 1;
				printf("the update is successful\n");
				}
				else
					printf("the update is unsuccessful\n");
				}
				else
					printf("ERROR : Update is already performed\n");
				break;
			case 6:
				return 0;
			
		}
	//	print_list(head1);
	}
}

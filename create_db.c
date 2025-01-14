#include"invert.h"
#include<ctype.h>

m_node* create_main_node(char *word, char *file_name)   	//creating main node
{
	m_node *main_new = malloc(sizeof(m_node));
	if (!main_new)
	{
		return FAILURE;
	}

	/* if new node created, update data + link */
	strcpy(main_new->word,word);
	main_new->main_link = NULL;
	main_new->sub_link = create_sub_node(file_name);
	main_new->file_count = 1;
}
s_node* create_sub_node(char *file_name)		//creating subnode
{
	s_node *sub_new = malloc(sizeof(s_node));
	if(!sub_new)
	{
		return FAILURE;
	}
	sub_new->word_count = 1;
	strcpy(sub_new->file_name,file_name);
	sub_new->sub_link = NULL;
}

int create_db(hash_n *hash, SLL **head)
{
	SLL *temp = *head; 		//pointing the filelist using temp pointer
	while(temp != NULL)		//if fileexists
	{
		char word[20];		//create a word array
		FILE *fp = fopen(temp->file_name ,"r");  	//file pointer and open the file
		if(fp == NULL)
		{
			printf("ERROR : failed to open the file\n");
			return FAILURE;
		}
scan : while((fscanf(fp,"%s",word)) != EOF)   	//to scan a word from the file
       {
	       int ind;		
	       ind = tolower(word[0])-97;		//calculating the word index using first letter the word by converting it to lower case ASSCII value
	       if((ind < 0) || (ind >25))		//if index not in the alphabetic range with is 0 to 25 make index as 26
	       {
		       ind = 26;
		       if(hash[ind].link == NULL)		//if hash table index link is null create a main node for that word else create another main node and connect it to previous main node mainlink
		       {
			       hash[ind].link = create_main_node(word, temp->file_name);
		       }
		       else
		       {
			       goto label;
		       }

	       }
	       if((ind >= 0) && (ind <=25))		//if index inside the range
	       {
		       if(hash[ind].link == NULL)      //check the index link is null or not 
		       {
			       hash[ind].link = create_main_node(word, temp->file_name);	//if null create a main node
		       }
		       else
			       label:{						//label for hash index 26 is link is not NULL
				       int flag = 0;
				       m_node *prev_temp1 = NULL;	
				       m_node *temp1 = hash[ind].link;

				       while(temp1 != NULL)		//if index not null
				       {
					       if(strcmp(temp1->word,word) !=0)  	//compare the words is not matches
					       {
						       if(temp1->main_link == NULL)		//check main_link is null or not if null create main node
						       {
							       temp1->main_link = create_main_node(word, temp->file_name);
							       break;
						       }
					       }
					       else	if(strcmp(temp1->word,word) ==0)	//if word same
					       {
						       s_node *temp2 = temp1->sub_link;
						       s_node *prev = NULL;
						       while(temp2 !=NULL)		//check with sub_node
						       {
							       if (strcmp(temp2->file_name, temp->file_name) == 0)	//check file name same
							       {							//if same increment wordcount
								       temp2->word_count++;
								       goto scan;	//after increment go to scan new word
								       break;
							       }
							       prev = temp2;
							       temp2 = temp2->sub_link;

						       }
						       if(temp2 == NULL)	//if no subnode present create new subnode with input filename
						       {
							       s_node *new = create_sub_node(temp->file_name);
							       prev->sub_link = new;
							       temp1->file_count++;
							       break;
						       }
					       }
					       prev_temp1 = temp1;
					       temp1 = temp1->main_link;
				       }
			       }
	       }}	
       temp = temp->link;
	}
	return SUCCESS;
}














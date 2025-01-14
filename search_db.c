#include"invert.h"
#include<ctype.h>

int search_db(hash_n *hash,char* word)
{
	 printf("search function entered\n");
	 printf("%s\n",word);
	int ind;
	ind = tolower(word[0]) -97;
	if(ind<0 || ind>25)
	{
		ind = 26;
	}
	printf("index is %d\n",ind);
	
	if(hash[ind].link == NULL)
	{
		printf("ERROR : Word not found\n");
	}
	m_node *temp = hash[ind].link;
	while(temp != NULL)
	{
		if(strcmp(temp->word,word) == 0)
		{
			s_node *temp1 = temp->sub_link;
			printf("Word \"%s\" is present in %d files\n",word,temp->file_count);
			while(temp1 != NULL)
			{
				printf("%s\n",temp1->file_name);
				temp1 = temp1->sub_link;
			}
			return SUCCESS;
		}

		temp = temp->main_link;
	}
	printf("ERROR : Word not found\n");
}
				
	//char word[];
//	printf("function entered\n");
//}

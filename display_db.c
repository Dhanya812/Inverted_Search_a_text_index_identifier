#include"invert.h"
void display_db(hash_n *hash)			//display function
{
	//int ind=0;
	printf("------------------------------------------------------------\n");
	printf("INDEX\tWORD\tFILE_COUNT\tWORD_COUNT\tFILE_NAME\n");
	 printf("------------------------------------------------------------\n");
	for(int ind =0; ind<27;ind++)		
	{
		if(hash[ind].link != NULL)
		{
			m_node *temp = hash[ind].link;
			while(temp != NULL)
			{

				printf("%d\t",ind);
				printf("%s\t\t",temp->word);
				printf("%d\t\t",temp->file_count);
				s_node *temp1 = temp->sub_link;
				if(temp1 == NULL)
				{
					printf("No files \t0\n");
				}
				else
				{
					while(temp1 != NULL)
					{
						printf("%d\t%s\n",temp1->word_count,temp1->file_name);
						if(temp1->sub_link != NULL)
						{
							printf("\t\t\t\t\t");
						}
						temp1 = temp1->sub_link;
					}
				}
				temp = temp->main_link;
			}
		}
	}
	 printf("------------------------------------------------------------\n");
}

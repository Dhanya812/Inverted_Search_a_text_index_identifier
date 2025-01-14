#include "invert.h"

int save_db(hash_n *hash, char *file_name)
{
    printf("save function entered\n");
    printf("%s\n", file_name);

    if (strstr(file_name, ".txt")) 
    {
        printf("INFO : the file is .txt file\n");

        FILE *fp = fopen(file_name, "w");
        if (fp == NULL) 
	{
            printf("Error opening file: %s\n", file_name);
            return FAILURE;
        }

        for (int ind = 0; ind < 27; ind++) 
	{
            m_node *temp = hash[ind].link;
            while (temp != NULL) 
	    {
                fprintf(fp, "#%d;%s;%d", ind, temp->word, temp->file_count);
                s_node *temp1 = temp->sub_link;
                while (temp1 != NULL) 
		{
                    fprintf(fp, ";%s;%d", temp1->file_name, temp1->word_count);
                    temp1 = temp1->sub_link;
                }
                fprintf(fp, "#\n");
                temp = temp->main_link; // Move to the next main node
            }
	    
        }

        fclose(fp);
        return SUCCESS;
    }
    else
    {
        printf("ERROR : the file is not a .txt file\n");
        return FAILURE;
    }
}

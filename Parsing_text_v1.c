#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


char keyword[200][60];
char Input[150];
int Key_Num;

void ReadKeyword()
{
	FILE *ptr;
	char filepath[20];
	char buffer[60];
	int length;
	char tmpkeyword[60];
	int i;
	
	sprintf(filepath,"KeywordFile.txt"); 
	ptr=fopen(filepath,"r");
	//printf("%s\n",filepath); ##check the path
	
	if(ptr==NULL)
	{
    	printf("The file %s can't be open!'\n",filepath); 
    }
	else
	{
		printf("File %s is open\n",filepath);
		
		Key_Num = 0;
		
		while((fgets(buffer, 180, ptr))!=NULL)
		{
			length = strlen(buffer);
			strncpy(tmpkeyword,&buffer[0],length);
			tmpkeyword[length]='\0';
			
			//printf("%s:%d\n",tmpkeyword,length);
			
			if(tmpkeyword[0]=='\n')  //##key word can't be '/n'.
			{
				break;
			} 
			else if(tmpkeyword[length-1]!='\n') //##identify key word's format(\t)
			{
				strncpy( keyword[Key_Num], &tmpkeyword[0],length);
				keyword[Key_Num][length] = '\0';
				Key_Num++;
			}
			else
			{
				strncpy( keyword[Key_Num], &tmpkeyword[0],length-1);
				keyword[Key_Num][length-1] = '\0';	
				Key_Num++;
			}
			
		}
		
		for(i=0;i<Key_Num;i++) //Check the Key word
		{
			printf("%s\n",keyword[i]);
		}
	}

	fclose(ptr);
	

}

void putText()
{
	char input[150];
	
	fgets(Input, sizeof(Input) / sizeof(Input[0]), stdin);
}

void FilterText()
{
	int Num_Input;
	int i,x,y,z;
	int end=0;
	
	Num_Input = strlen(Input);
	
	for (i=0;i<Num_Input;i++)
	{
		for(x=0;x<Key_Num;x++)
		{
			y=0;
			end =0;

			while(keyword[x][y] != '\0' && end !=1)
			{
				if(Input[i+y]==keyword[x][y] && keyword[x][y+1]!='\0')
				{
					y++;
				}
				else if(Input[i+y]==keyword[x][y] && keyword[x][y+1]=='\0')
				{
					for(z=i;z<=i+y;z++)
					{
						Input[z]='x';
						end =1;
					}
				}
				else
				{
					end =1;
				}
			}
		}
	}
	//printf("Number of Input : %d\n",Num_Input);
}

main (int argc, char **argv)
{ 
	printf("\n!!! Welcome To Use Parser_text in C !!!\n");
	printf("=================START=================\n");
	printf("Loading Key Word File ...\n");
	ReadKeyword();
	printf("Please type the text...\n");
	putText();
	printf("Parsing text now...\n");
	FilterText();
	printf("%s\n",Input);
	printf("=================DONE==================\n\n");
	
	system("pause");
	
}

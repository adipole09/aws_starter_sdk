#include <wc.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

void gonw(){
	while(isspace(str[i]) == 0 && ispunct(str[i]) == 0 && str[i] != '\0')
	    i++;	

}
int count(char *str, char *w)
{
	//find the length	
	slen = strlen(str);
	wlen = strlen(w);
	
	//searching w in str
	i = j = wcount = 0;
	while(i < slen)
	{
		if(str[i] == w[0])
		{	
			//first letter matching
			for(j = 0; j< wlen; j++)
			{
				if(str[i+j] != w[j])
				{	
					//mismatch 
					gonw();
					break;

				}				

			}
			if(j == wlen)
			{
				//match found
				if(isspace(str[i+j])||ispunct(str[i+j])||str[i+j]=='\0')
				{
					wcount++;
					i += j;
					
				}
			}
			

		}
		else{
			gonw();	
		}
		i++;
		  

	}
	//returning wordcount
	return wcount;

}	









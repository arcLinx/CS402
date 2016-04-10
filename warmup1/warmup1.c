

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>
#include <ctype.h>
#include "cs402.h"
#include <locale.h>
#include "my402list.h"
/* ----------------------- Global ----------------------- */

typedef struct tfile{
	char operator[1];
	char description[24];
	long int timestamp;
	int amount;
	int balances;
	char newtimestamp[15];
	int amountpush;
	int balancespush;
	char outputamountprint[15];
	char outputbalanceprint[15];
}tfilevalues;
char buf[1030];

/* ----------------------- Print() ----------------------- */


void printheadline()
{
	int i;
	for (i=0; i< 80; i++)
	{
		if (i == 0 || i == 18 || i == 45 || i == 62 ||i == 79)
			fprintf(stdout, "+");
		else
			fprintf(stdout, "-");
	}
	fprintf(stdout,"\n");
}
void printheading()
{
	fprintf(stdout,"|       Date      | Description              |         Amount |        Balance |\n");
}

static
void printthedetails(My402List *pList)
{
    //My402ListElem *elem=NULL;
    //tfilevalues* ival;
    //float reference,bal;
    printheadline();
    printheading();
    printheadline();
    char* timedat;
	char timearray[20];
	char newtime[17];
	char newtime1[6];
	int i;
	My402ListElem *elem2= NULL;
	My402ListElem *elem5= NULL;
	My402ListElem *elem4= NULL;
    My402ListElem *elem1=NULL;
	My402ListElem *elem=NULL;
	My402ListElem *elem3=NULL;
	//tfilevalues* ival3;
	//tfilevalues* ival4;
	
    for (elem=My402ListFirst(pList); elem != NULL; elem=My402ListNext(pList, elem)) 
    {
		tfilevalues* ival;
		memset(newtime,0,sizeof(newtime));
		memset(newtime1,0,sizeof(newtime1));
		ival=(tfilevalues*)(elem->obj);
		timedat = ctime(&(ival->timestamp));
		strcpy(timearray,timedat);
		for (i=0; i <11; i++)
		{
			newtime[i]= timearray[i];
		}
		
		for ( i=0; i<4 ; i++ )
		{
			newtime1[i]=timearray[i+20];
		}
		strcat(newtime,newtime1);
		strcpy(ival->newtimestamp,newtime);
		
	}
	int bal=0;
	for (elem1=My402ListFirst(pList); elem1 != NULL; elem1=My402ListNext(pList, elem1)) 
    {
		tfilevalues* ival1;
		int reference=0;
		ival1=(tfilevalues*)(elem1->obj);
			reference = ival1->amount;
			
			if ((ival1->operator)[0] == '+')
				bal = bal + reference;
				
			else if ((ival1->operator)[0] == '-')
				bal = bal -reference;
						
			ival1->balances= bal;
		
			
						
	}
	// Code for terminating string \0 and printing the comma
	for (elem2=My402ListFirst(pList); elem2 != NULL; elem2=My402ListNext(pList, elem2)) 
    {
		tfilevalues* ival2;
		ival2=(tfilevalues*)(elem2->obj);
		int localint=0;
		int count =0;
		int c;
		for(c=0; c<strlen(ival2->description);c++)
		{
			if(ival2->description[c] == '\n')
				ival2->description[c]='\0';
		}
		localint = ival2->amount;
		while(localint!=0)
		{
			localint = localint/10;
			count ++;
		}
		ival2->amountpush = count;
		count=0;localint=ival2->balances;
		while(localint!=0)
		{
			localint = localint/10;
			count ++;
		}
		ival2->balancespush = count;
			
		
	}
	for (elem4=My402ListFirst(pList); elem4 != NULL; elem4=My402ListNext(pList, elem4)) 
    {
		tfilevalues* ival4;
		ival4=(tfilevalues*)(elem4->obj);
		char string[20];
		char outputstring[20];
		int c;
		char str[5];
		
		int dec = (ival4->amount) % 100;
		memset(string,0,sizeof(string));
		memset(outputstring,0,sizeof(outputstring));
		sprintf(string,"%d",(ival4->amount)/100);
		sprintf(str,"%02d", dec);
		//fprintf(stdout, "*** %s", str);
		if((strlen(string) == 4))
		{						//print 2comma
			for(i=0, c=0 ;i<strlen(string);i++,c++)
			{
				if(i == 1){
					outputstring[c] = ',';
					c++;
					outputstring[c] = string[i];
					}
				
				else
					outputstring[c] = string[i];
			}
		}
		else if((strlen(string) == 5))
		{						//print 2comma
			for(i=0, c=0 ;i<strlen(string);i++,c++)
			{
				if(i == 2){
					outputstring[c] = ',';
					c++;
					outputstring[c] = string[i];
					}
				
				else
					outputstring[c] = string[i];
			}
		}
		else if((strlen(string) == 6))
		{						//print 2comma
			for(i=0, c=0 ;i<strlen(string);i++,c++)
			{
				if(i == 3){
					outputstring[c] = ',';
					c++;
					outputstring[c] = string[i];
					}
				
				else
					outputstring[c] = string[i];
			}
		}
		else if((strlen(string) > 6))
		{						//print 2comma
			for(i=0, c=0 ;i<strlen(string);i++,c++)
			{
				if(i == 1){
					outputstring[c] = ',';
					c++;
					outputstring[c] = string[i];
					}
				
				else if(i==4){
					outputstring[c] = ',';
					c++;
					outputstring[c] = string[i];
					}
				else
					outputstring[c] = string[i];
			}
		}
		else
		sprintf(outputstring,"%s",string);
		//printf("OUT:%s\n",outputstring);	
		//char *str1;
		//char point[2]=".";
		//str1=strcat(point,str);
		//finalstr='\0';
		/*
		int len=strlen(outputstring)+strlen(str)+1;
		ival4->outputamountprint[len]='\0';
		*/
		sprintf(ival4->outputamountprint,"%s%s%s",outputstring,".",str);
		//finalstr=strcat(outputstring,str1);
		
			
	}
	
	
	for (elem5=My402ListFirst(pList); elem5 != NULL; elem5=My402ListNext(pList, elem5)) 
    {
		tfilevalues* ival5;
		ival5=(tfilevalues*)(elem5->obj);
		char string[15];
		char outputstring[15];
		int c;
		char str[5];
		
		int dec = (abs(ival5->balances)) % 100;
		memset(string,0,sizeof(string));
		memset(outputstring,0,sizeof(outputstring));
		sprintf(string,"%d",abs(ival5->balances)/100);
		sprintf(str,"%02d", dec);
		
		if((strlen(string) == 4))
		{						//print 2comma
			for(i=0, c=0 ;i<strlen(string);i++,c++)
			{
				if(i == 1){
					outputstring[c] = ',';
					c++;
					outputstring[c] = string[i];
					}
				
				else
					outputstring[c] = string[i];
			}
		}
		else if((strlen(string) == 5))
		{						//print 2comma
			for(i=0, c=0 ;i<strlen(string);i++,c++)
			{
				if(i == 2){
					outputstring[c] = ',';
					c++;
					outputstring[c] = string[i];
					}
				
				else
					outputstring[c] = string[i];
			}
		}
		else if((strlen(string) == 6))
		{						//print 2comma
			for(i=0, c=0 ;i<strlen(string);i++,c++)
			{
				if(i == 3){
					outputstring[c] = ',';
					c++;
					outputstring[c] = string[i];
					}
				
				else
					outputstring[c] = string[i];
			}
		}
		else if((strlen(string) >6))
		{						//print 2comma
			for(i=0, c=0 ;i<strlen(string);i++,c++)
			{
				if(i == 1){
					outputstring[c] = ',';
					c++;
					outputstring[c] = string[i];
					}
				
				else if(i==4){
					outputstring[c] = ',';
					c++;
					outputstring[c] = string[i];
					}
				else
					outputstring[c] = string[i];
			}
		}
		else
			sprintf(outputstring,"%s",string);
		
		//char *str1;
		//char point[2]=".";
		//str1=strcat(point,str);
		
		//finalstr=strcat(outputstring,str1);
		//printf("Entered");
	//	int len=strlen (outputstring)+strlen(str)+1;
	//	ival5->outputbalanceprint[len]='\0';
		char finalstr[15];
		
		sprintf(finalstr,"%s%s%s",outputstring,".",str);
		strcpy(ival5->outputbalanceprint,finalstr);
		
		//printf("Ival5==%s\n",ival5->outputbalanceprint);
		
	}
	
	
	for (elem3=My402ListFirst(pList); elem3 != NULL; elem3=My402ListNext(pList, elem3)) 
    {
		int j;
		tfilevalues* ival3;
		ival3=(tfilevalues*)(elem3->obj);
		fprintf(stdout,"| %s ",ival3->newtimestamp);
		fprintf(stdout,"| %s",ival3->description);
		for(j=0; j<25-strlen(ival3->description);j++)
		{
			fprintf(stdout," ");
		}
		
		if ((ival3->operator)[0] == '+')
		{
			if ((ival3->amount)/100<= 9999999 && (ival3->amount)/100>1000000 )
			{
					
					ival3->outputamountprint[13]='\0';
					
				fprintf(stdout,"| %13s  ",ival3->outputamountprint);
			}
			else if (ival3->amount/100 > 9999999)
				fprintf(stdout,"\?,\?\?\?,\?\?\?.\?\?");
			else
			{
					if ((ival3->amount)/100>999 && (ival3->amount)/100<10000)
					{
						fprintf(stdout,"| ");
						fprintf(stdout,"%13s  ",ival3->outputamountprint);
					}
					else if ((ival3->amount)/100>9999 && (ival3->amount)/100<100000)
					{
						fprintf(stdout,"| ");
						fprintf(stdout,"%13s  ",ival3->outputamountprint);
					}
					else if ((ival3->amount)/100>99999 && (ival3->amount)/100<1000000)
					{
						fprintf(stdout,"| ");
						fprintf(stdout,"%13s  ",ival3->outputamountprint);
					}
					else if((ival3->amount)/100 <100)
					{
						fprintf(stdout,"| ");
						fprintf(stdout,"%13s  ",ival3->outputamountprint);
					}
					
					else if ((ival3->amount)/100>999999 && (ival3->amount)/100<10000000)
					{
						fprintf(stdout,"| ");
						fprintf(stdout,"%13s  ",ival3->outputamountprint);
						
					}
					else if((ival3->amount)/100 <= 999 && (ival3->amount)/100>100)
					{
						fprintf(stdout,"| ");
						fprintf(stdout,"%13s  ",ival3->outputamountprint);
					}
				}
		}
		else
		{
			if ((ival3->amount)/100<= 9999999 && (ival3->amount)/100>1000000 )
				fprintf(stdout,"| (%12s) ",ival3->outputamountprint);
			else if (ival3->amount/100 > 9999999)
				fprintf(stdout,"(\?,\?\?\?,\?\?\?.\?\?)");
			else
				{
					if ((ival3->amount)/100>999 && (ival3->amount)/100<10000)
					{
						fprintf(stdout,"| (");
						
						fprintf(stdout,"%12s) ",ival3->outputamountprint);
					}
					else if ((ival3->amount)/100>9999 && (ival3->amount)/100<100000)
					{
						fprintf(stdout,"| (");
						
						fprintf(stdout,"%12s) ",ival3->outputamountprint);
					}
					else if ((ival3->amount)/100>99999 && (ival3->amount)/100<1000000)
					{
						fprintf(stdout,"| (");
						fprintf(stdout,"%12s) ",ival3->outputamountprint);
					}
					else if((ival3->amount)/100 <100)
					{
						fprintf(stdout,"| (");
						
						fprintf(stdout,"%12s) ",ival3->outputamountprint);
					}
					else if ((ival3->amount)/100>999999 && (ival3->amount)/100<10000000)
					{
						fprintf(stdout,"| (");
						
						fprintf(stdout,"%12s) ",ival3->outputamountprint);
					}
					else if((ival3->amount)/100 <= 999 && (ival3->amount)/100>100)
					{
						fprintf(stdout,"| (");
						fprintf(stdout,"%12s) ",ival3->outputamountprint);
					}
				}

			
		}
		if (ival3->balances > 0)
		{
			//printf("balnace==%d\n",ival3->balances);
			if ((ival3->balances)/100< 10000000 && (ival3->balances)/100>1000000 )
				{//printf("Balance is===%s\n", ival3->outputbalanceprint);
				
				fprintf(stdout,"| %13s  ",ival3->outputbalanceprint);
			}
			else if (ival3->balances/100 > 9999999)
				fprintf(stdout,"|  \?,\?\?\?,\?\?\?.\?\?  ");
			else
				{
					if ((ival3->balances)/100>999 && (ival3->balances)/100<10000)
					{
						fprintf(stdout,"| ");
						
						fprintf(stdout,"%13s  ",ival3->outputbalanceprint);
					}
					 else if ((ival3->balances)/100>9999 && (ival3->balances)/100<100000)
					{
						fprintf(stdout,"| ");
						
						fprintf(stdout,"%13s  ",ival3->outputbalanceprint);
					}
					 else if ((ival3->balances)/100>99999 && (ival3->balances)/100<1000000)
					{
						fprintf(stdout,"| ");
						fprintf(stdout,"%13s  ",ival3->outputbalanceprint);
					}
					 else if((ival3->balances)/100 <100)
					{
						fprintf(stdout,"| ");
						
						fprintf(stdout,"%13s  ",ival3->outputbalanceprint);
					}
					else if((ival3->balances)/100 <= 999 && (ival3->balances)/100>100)
					{
						fprintf(stdout,"| ");
					//	printf("Entered %14s" ,ival3->outputbalanceprint);
					fprintf(stdout,"%13s  ",ival3->outputbalanceprint);
						
					}
				}
			}
			else
				{		ival3->balances=ival3->balances*(-1);
						if ((ival3->balances)/100<= 9999999 && (ival3->balances)/100>=1000000 )
							fprintf(stdout,"| (%12s) ",ival3->outputbalanceprint);
						else if (ival3->balances/100> 9999999)
							fprintf(stdout,"| (\?,\?\?\?,\?\?\?.\?\?) ");
						else
						{
							if ((ival3->balances)/100>999 && (ival3->balances)/100<10000)
							{
								fprintf(stdout,"| (");
										
								fprintf(stdout,"%12s) ",ival3->outputbalanceprint);
							}
							else if ((ival3->balances)/100>9999 && (ival3->balances)/100<100000)
							{
								fprintf(stdout,"| (");
								
								fprintf(stdout,"%12s) ",ival3->outputbalanceprint);
							}
							else if ((ival3->balances)/100>99999 && (ival3->balances)/100<999999)
							{
								fprintf(stdout,"| (");
								
								fprintf(stdout,"%12s) ",ival3->outputbalanceprint);
							}
							else if((ival3->balances)/100 <100)
							{
								fprintf(stdout,"| (");
								
								fprintf(stdout,"%12s) ",ival3->outputbalanceprint);
							}
							else 
							{
								fprintf(stdout,"| (");
								
								fprintf(stdout,"%12s) ",ival3->outputbalanceprint);
							}
						}
				}
		fprintf(stdout,"|");
		fprintf(stdout,"\n");
		
	}
    	printheadline();
  }
 /* ----------------------- Sort() ----------------------- */
void timestampidentical(My402List *pList)
{
    My402ListElem *elem1=NULL;
    My402ListElem *elem2=NULL;
	tfilevalues* ival1= NULL;
	tfilevalues* ival2= NULL;
	long t1,t2;
    
    for (elem1=My402ListFirst(pList); elem1!= NULL; elem1=My402ListNext(pList, elem1)) {
        ival1=(tfilevalues*)(elem1->obj);
        t1= ival1->timestamp;
        for (elem2=My402ListNext(pList, elem1); elem2 != NULL; elem2=My402ListNext(pList, elem2)) {
			ival2=(tfilevalues*)(elem2->obj);
			t2= ival2->timestamp;
			if(t1==t2)
			{
				fprintf(stderr,"Timestamp identical in the input file. \n");
				exit(1);
			}
			
		}
	}
	return;
}
static
void BubbleForward(My402List *pList, My402ListElem **pp_elem1, My402ListElem **pp_elem2)
    /* (*pp_elem1) must be closer to First() than (*pp_elem2) */
{
    My402ListElem *elem1=(*pp_elem1), *elem2=(*pp_elem2);
    void *obj1=elem1->obj, *obj2=elem2->obj;
    My402ListElem *elem1prev=My402ListPrev(pList, elem1);
/*  My402ListElem *elem1next=My402ListNext(pList, elem1); */
/*  My402ListElem *elem2prev=My402ListPrev(pList, elem2); */
    My402ListElem *elem2next=My402ListNext(pList, elem2);

    My402ListUnlink(pList, elem1);
    My402ListUnlink(pList, elem2);
    if (elem1prev == NULL) {
        (void)My402ListPrepend(pList, obj2);
        *pp_elem1 = My402ListFirst(pList);
    } else {
        (void)My402ListInsertAfter(pList, obj2, elem1prev);
        *pp_elem1 = My402ListNext(pList, elem1prev);
    }
    if (elem2next == NULL) {
        (void)My402ListAppend(pList, obj1);
        *pp_elem2 = My402ListLast(pList);
    } else {
        (void)My402ListInsertBefore(pList, obj1, elem2next);
        *pp_elem2 = My402ListPrev(pList, elem2next);
    }
}

static
void BubbleSortForwardList(My402List *pList, int num_items)
{
    My402ListElem *elem=NULL;
    tfilevalues* cur_val;
	tfilevalues* next_val;
	int i=0;
    timestampidentical(pList);
    for (i=0; i < num_items; i++) {
        int j=0, something_swapped=FALSE;
        My402ListElem *next_elem=NULL;

        for (elem=My402ListFirst(pList), j=0; j < num_items-i-1; elem=next_elem, j++) {
             cur_val=(tfilevalues*)(elem->obj);

            next_elem=My402ListNext(pList, elem);
            next_val = (tfilevalues* )(next_elem->obj);

            if ((cur_val->timestamp)> (next_val->timestamp)) {
                BubbleForward(pList, &elem, &next_elem);
                something_swapped = TRUE;
            }
        }
        if (!something_swapped) break;
    }
}

/* ----------------------- fileread() ----------------------- */
int counthenumberofdigits(long time1)
{
	int countdigits=0;
	while(time1 != 0)
	{
		time1= time1/10;
		++countdigits;
	}
	return countdigits;
}
int fddigafdecimal(char* array)
{
	int i,cnt=0;
	for (i=0;i<strlen(array);i++)
	{
		if(array[i]!= '0')
			cnt++;
	}
	return cnt;
}
char* removeleadingspacechar(char *descptr)
{
	while(isspace(*descptr))
		descptr++;
	return descptr;
}
void fileread(FILE *fp)
{	
	
	My402List listform;
	memset(&listform,0,sizeof(My402List));
	memset(buf,0,sizeof(buf));
	My402ListInit(&listform);
	tfilevalues* value = NULL;
	char* stringtoken =NULL;
	
	// To include code for the command line inputs 

	char tab='\t';
	char lsl = '\0';
	char *delim;
	char *lsdelim;	
	delim = &tab;
	lsdelim = &lsl;
	int numdigits;
	int intpart;
	//char* descptr;
	char strbuf[20];
	memset(strbuf,0,sizeof(strbuf));
	while(fgets(buf,sizeof(buf), fp)!= NULL)  // Traverses through the everyline of the function
	{
		value = (tfilevalues*)malloc(sizeof(tfilevalues));	// Creating a new structure for a line
		int g,cnt=0;
		
		if (strlen(buf) > 1024)
		{
			fprintf(stderr,"Line length in the file is greater than 1024 characters\n");
		}
		for(g=0;g<strlen(buf);g++)
		{
			if(buf[g]=='\t')
			cnt++;
		}
		if(cnt !=3 )
		{
					fprintf(stderr,"Number of tabs in the file is not equal to 3\n");
					exit(1);
		}
		//copy the transaction type from the file 
		stringtoken = strtok(buf,delim);
		strncpy(value->operator,stringtoken,sizeof(value->operator));
		if( (strcmp(stringtoken,"-") != 0) && (strcmp(stringtoken,"+") != 0)){
			fprintf(stderr, "Transaction type unknown in the file .\n");
			exit(1);
		}
		
		stringtoken = strtok(NULL,delim);
		long time1=(long)atoi(stringtoken);
		if (time1 > time(NULL))
		{
			fprintf(stderr, "Timestamp is bad in the file .\n");
			exit(1);
		}
					
		if(strlen(stringtoken) >10){
			fprintf(stderr, "Timestamp is bad in the file .\n");
			exit(1);
		}
		value->timestamp = atol(stringtoken);
		
				
		stringtoken = strtok(NULL,delim);
		
		int amt2;
		char *dec;
		dec=strchr(stringtoken,'.');
		dec++;
		amt2=atoi(dec);
		
		value->amount = atoi(stringtoken)*100+amt2;
		
		if (value->amount < 0)
		{
			fprintf(stderr, "The transaction amount must be positive in the file .\n");
			exit(1);
		}
		
		intpart = value->amount/100;
		
		numdigits=counthenumberofdigits(intpart);
		if(numdigits > 7){
			fprintf(stderr, "The Integer part of amount field is not as expected(xxxxxxx.xx) in the tfile .\n");
			exit(1);
		}
		if(strlen(strchr(stringtoken,'.')) >3){
			fprintf(stderr, "The Fractional part of amount field is not as expected(xxxxxxx.xx) in the tfile .\n");
			exit(1);
		}
		stringtoken = strtok(NULL,lsdelim);
		stringtoken = removeleadingspacechar(stringtoken);
		if(*stringtoken == 0){
			fprintf(stderr, "Description field is blank.\n");
			exit(1);
		}
		strncpy(value->description,stringtoken,sizeof(value->description));
		My402ListAppend(&listform,value);
	}
	fclose(fp);
	
	BubbleSortForwardList(&listform,listform.num_members);
	printthedetails(&listform);
}


/* ----------------------- main() ----------------------- */

int main(int argc, char *argv[])
{
    FILE *fp=NULL;
	setlocale(LC_NUMERIC,"");
	if (argc == 1)
	{
		fprintf(stderr, "Command unknown plese find the usage below.\n");
		fprintf(stderr, "usage: warmup1 sort [tfile].\n");
		return -1;
	}
	if ( strcmp(argv[1],"sort") != 0) 
		{
			fprintf(stderr, "Command unknown plese find the usage below.\n");
			fprintf(stderr, "usage: warmup1 sort [tfile].\n");
			return -1;
		}
	if (argc == 3) 
	{
		fp = fopen(argv[2], "r");
		struct stat sb;
		if (fp == NULL) 
		{
			perror("Error");
			return -1;
		}
		if (stat(argv[2], &sb) == 0 && S_ISDIR(sb.st_mode))
		{
			fprintf(stderr,"Error: This is a directory \n");
			return -1;
		}
		
				
		fileread(fp);
		
	} 
	if(argc == 2)
	{
		fileread(stdin);
	}
	return 0;
}
    

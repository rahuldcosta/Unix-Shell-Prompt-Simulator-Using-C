/*
#=====================================================================================================================#
# Author:- Rahul C. Dcosta(1337),Siddhesh Naik(1329),Onkar M. Kelkar(1310)					      #
# File Type :- Main Program File                                     				 		      #
# Description:-Emulating the Shell Prompt with history features	and ctrl+d for termination			      #
# Date Created:-07/05/2014                             		     						      #
# Date Modified:-11/05/2014                            		     						      #
# Copyrights:- All Rights to TroubleShooter	   		     					              #
#=====================================================================================================================#
*/
#include<stdio.h>
#include <ctype.h>
#include<stdlib.h>
#include <unistd.h>
#include<string.h>
#include<wait.h>
#define BUFSIZE 300
#define ARGVSIZE 100
#define DELIM "\n\t\r "
int numbervalidate(char arr[BUFSIZE+1]);

int main(int argc,char **argv)
{


	int i,n,flag=0,spot=0,gone=0;
	char buf[BUFSIZE+1]="\0",temp[BUFSIZE+1]="\0",oldcmd[BUFSIZE+1]="\0",*clargs[ARGVSIZE],listofcmd[BUFSIZE][ARGVSIZE],*p,numb[BUFSIZE+1];
	int returnval,cmdcount=0,cmdno;
	
	while(1)
	{
		
		if(flag==1)
		{
			strcpy(oldcmd,temp);		
	
			}	
	
		n=1;
		write(STDOUT_FILENO,"sh> ",4);
		fgets( buf, sizeof buf, stdin);
		
		if(!strcmp(buf,"history\n"))		//printing list of commands run in totality in the shell
	{
		for(i=0;i<cmdcount;i++)
		{
			printf("%d=>%s",i+1,listofcmd[i]);

		}
		strcpy(buf,"\0");
		
		continue;
	
	}

		else if(buf[0]=='p'&&numbervalidate(buf))		
		{
			
			strcpy(numb,buf);
			p=strtok(numb,"p");
			p = strtok(NULL, "p");
			p=strtok(numb,"p");
			  cmdno=atoi(p);
			p = strtok(NULL, "p");
		
			 if (cmdno<=cmdcount) 
			{ 
				
			strcpy(buf,listofcmd[cmdno-1]);
			  spot=1;
			  }
			else 
			{ printf("No Command history found\nType sh> history to check the list of commands entered\n");
				
				continue;
					}
		}
		else
		{
			strcpy(temp,buf);
			spot=0;
		}
		
			
		clargs[0]=strtok(buf,DELIM);
		
		while((clargs[n]=strtok(NULL,DELIM))!=NULL)
			n++;

		clargs[n]=NULL;
		
	   switch(fork()) 
	{

	case 0 :	//Child Process part
			if((execvp(clargs[0],&clargs[0]))<0)
			{
				printf("Bash Error\nCommand not Found\nOr Invalid option ussage\n");
				exit(200);

			}

	default :	//parent Process part
			wait(&returnval);
			if (WEXITSTATUS(returnval)!=200 && spot != 1 && strcmp(listofcmd[cmdcount-1],temp)!=0 )strcpy(listofcmd[cmdcount++],temp);
			
			
			for(i=0;i<=n;i++)
			clargs[i]="\0";
			for(i=0;i<BUFSIZE+1;i++)
				buf[i]='\0';


	}//end switch
		if(feof(stdin))
		{
   			printf("\nShell Terminated\n");
			
			exit(0);
		}

	
	flag=1;
	}//end for



}//end main


int numbervalidate(char arr[BUFSIZE+1])
{
	int i=0,count=0;

	for(i=1;arr[i]!='\0';i++)
	{
		if ( isdigit(arr[i]) )
		count++ ;
		else 
		break; 
	}	

	
	if (count == strlen(arr)-2)
	return 1;
	else
	return 0;

}

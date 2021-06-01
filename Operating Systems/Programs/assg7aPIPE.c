#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h> //for PIPE_BUF

char ch[400],fname[15];

int display(char fname[])
{
	FILE * fp;
	int i=0;
	fp=fopen(fname,"r");
	printf("\nThe file name is : %s",fname);
	printf("\nThe contents of file are ...\n");

	while(!feof(fp))
	{
		ch[i]=fgetc(fp);
		printf("%c",ch[i]);
		i++;
	}
	fclose(fp);
	return 0;
}

int main()
{
	int data_processed;
	int pipefd_1[2],pipefd_2[2];

	const char some_data[] = "zombie.c";
	char buffer[PIPE_BUF];

	pipe(pipefd_2);
	
	pid_t pid;
	
	if(pipe(pipefd_1)==0)
		pid=fork();

	if(pid==0)
	{
		data_processed=read(pipefd_1[0], buffer, PIPE_BUF);// or use BUFSIZ
		printf("\nChild process read %d bytes of file: %s\n",data_processed,buffer);
		
		display(buffer);
	


		data_processed=write(pipefd_2[1], ch, strlen(ch));
		printf("\nChild process wrote %d bytes of file...\n",data_processed);
		exit(0);
	}
	else
	{
		data_processed=write(pipefd_1[1], some_data, strlen(some_data));
		printf("\nParent process wrote %d bytes of file: %s\n",data_processed,some_data);
		
		sleep(1);
		
		data_processed=read(pipefd_2[0], buffer, PIPE_BUF);
		printf("\nParent process read %d bytes of file:\n %s\n",data_processed,buffer);
	}
	return 0;
}

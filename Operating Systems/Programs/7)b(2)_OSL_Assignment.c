/*
Program By:
Assignment No:7(b)
Pipes : FIFOs: Full duplex communication between two independent processes. First process accepts
sentences and writes on one pipe to be read by second process and second process counts
number of characters, number of words and number of lines in accepted sentences, writes this
output in a text file and writes the contents of the file on second pipe to be read by first process
and displays on standard output.*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define FIFO_NAME "fifo1"
#define FIFO_NAME1 "fifo2"

int main(void)
{
    char s[300],s1[122];
    int num, fd,i=0,character=0,word=1,line=1,fd1;
		 mkfifo(FIFO_NAME, 0666);
    printf("THIS IS SECOND PROCESS\n");
    fd = open(FIFO_NAME, O_RDONLY);
        if ((num = read(fd, s, 300)) == -1)
	{    printf("read error");
	exit(0);
}	
        else {
            s[num] = '\0';
            printf("read sentences from First Process=====>\n \"%s\"\n", s);
        }
	FILE *fp;    
     fp = fopen("output.txt","w"); /* open for writing */
     
	while(s[i]!='\0')
{
if((s[i]>=65 && s[i]<=90)  || ( s[i]>=97 && s[i]<=122))
{
	character++;
}
	i++;
}
	i=0;
while(s[i]!='\0')
{
	if(s[i]!=' ')
{
i++;
printf("%d",i);
}
else
{
word++;
i++;
printf("%d",i);
}
}

i=0;
while(s[i]!='\0')
{
if(s[i]==10)
{
line++;
}
i++;
}
     fprintf(fp,"Number of characters=%d \n Number of Words=%d \n Number of Lines=%d",character,word,line);
     fclose(fp); /* close the file before ending program */
mkfifo(FIFO_NAME1, 0666);
//mknod(FIFO_NAME1, S_IFIFO | 0666, 0);

    fd1 = open(FIFO_NAME1, O_WRONLY);
	FILE *f;
	i=0;
	char ch;
	f=fopen("output.txt","r");
if(f==0)
{
printf("\n file not found");
exit(0);
}
while((ch=fgetc(f))!=EOF)
{	
s1[i++]=ch;
}

	fclose(f);
	printf("\n Number of Chars, Words and Line are Counted, \n Output is stored in text file, \n Output is sent to First Process using FIFO"); 
	write(fd1,s1,strlen(s1));
   return 0;
}
/*
Output:
mcoer@Mcoer:~$ gcc proc1.c
mcoer@Mcoer:~$ ./a.out
THIS IS FIRST PROCESS






Sent some sentences to Second Process using FIFO
Result of Second Process is shown by First Process by using FIFO===>
 "Number of characters=40 
 Number of Words=9 
 Number of Lines=3"

mcoer@Mcoer:~$ gcc proc2.c
mcoer@Mcoer:~$ ./a.out
THIS IS SECOND PROCESS
read sentences from First Process=====>
 "this is mohini from te it
 MCOERC
 eklahare nashik"
1234567891011121314151617181920212223242526272829303132333435363738394041424344454647484950
 Number of Chars, Words and Line are Counted, 
 Output is stored in text file, 
 Output is sent to First Process using FIFOmcoer@Mcoer:~$ 
*/








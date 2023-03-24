#include <stdio.h>  //all the libraries we need for the program.
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char *argv[])
{
//all the variable declarations
char command[256];
pid_t pid;
char i;

while(1)
{
//below the loop it shows a prompt then you input your command
printf("shell-input: ");
fgets(command,256,stdin);

//if the is a space between the commands then the program ignores it 
if((strlen(command)>0)&&(command[strlen(command)-1]=='\n'))
{
command[strlen(command)-1]='\0';
}
//if the command is exit then program exits loop otherwise it continues
if(!strcmp("",command)) continue;
if(!strcmp("exit",command)) break;
char *ptr;
i=0;
//splits the string into tokens with space being used as delimiter
ptr=strtok(command," ");
while(ptr!=NULL){
argv[i]=ptr;
i++;
ptr=strtok(NULL," ");
}
if(!strcmp("&",argv[i-1])){
argv[i-1]=NULL;
argv[i]="&";
}else{
argv[i]=NULL;
}
//fork sys call creates 2 same programs with different IDs 
  pid = fork();
//if the sys call fails it will return 1
if (pid == -1)
{
return 1;
}
//if the process ID is 0 then it will execute command
if (pid == 0)
{
if(strcmp(argv[0],"cd")==0)
{
chdir(argv[1]);
}
else if(strcmp(argv[0],"cd-")==0)
{
chdir("..");
}
else{
execvp(argv[0],argv);
}
}
else
{
//if its not 0 then it will switch to child process and wait until finished 
if(NULL==argv[i]) waitpid(pid,NULL,0);
}
}return EXIT_SUCCESS;
}








#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
int child_s;
char *cmd;
char *arg[100];

while(1){
  size_t size;
  getline(&cmd, &size, stdin);
  cmd[strlen(cmd)-1]='\0';
  
  int i=0;
  
  char *ptr = strtok(cmd, " ");
  
  while(ptr!=NULL){
    arg[i++] = ptr;
    ptr=strtok(NULL," ");
  }
  arg[i]=NULL;
  
  if(strcmp(arg[0], "quit")==0){
    break;
  }
  
  char path[100];
  sprintf(path, "/bin/%s", arg[0]);
  pid_t pid=fork();
  if(pid==0){
    execv(path,arg);
    exit(0);
  }
  else{
    wait(&child_s);
  }
}
free(cmd);
exit(0);
return 0;
}
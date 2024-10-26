#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>

void main(){

int fd, tag;
char buffer[512];
char pages[5];
int i=0, page=1, prin, num, num2, num3, num4;

fd=open("Aladdin.txt", O_RDONLY,S_IRWXU);
tag=open("Aladdin_num.txt", O_WRONLY | O_CREAT,S_IRWXU);

while(read(fd,buffer+i,1)>0){

if(buffer[i]!='\n'){
  i++;
}
else{
if(page>=1000){
num=page/1000;
  pages[0]=num+'0';
  
  num2=(page-num*1000)/100;
  pages[1]=num2+'0';
  
  num3=(page-num*1000-num2*100)/10;
  pages[2]=num3+'0';
  
  num4=(page-num*1000-num2*100-num3*10);
  pages[3]=num4+'0';}
  
  else if(page>=100){
  num=page/100;
  pages[0]=num+'0';
  
  num2=(page-num*100)/10;
  pages[1]=num2+'0';
  
  num3=(page-num*100-num2*10)/1;
  pages[2]=num3+'0';}
  
  else if(page>=10){
  
  num2=(page)/10;
  pages[0]=num2+'0';
  
  num3=(page-num2*10)/1;
  pages[1]=num3+'0';}
  
  else if(page>=1){
  num3=page;
  pages[0]=num3+'0';}

  
  if(page>=1000){
  prin=4;}
  else if(page>=100){
  prin=3;
  }
  else if(page>=10){
  prin=2;
  }
  else if(page>=1){
  prin=1;
  }
  
  write(tag, pages, prin);
  write(tag, buffer, i);
  page++;
  
  
  i=0;
}
}

}
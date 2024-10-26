#ifndef Head
#define Head

#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>

const char *jump="\n";
const char *braked="brake";

int strcmp2(const char *str1, const char *str2){          //strcmp
  for(; (*str1!='\0')&&(*str1==*str2);str1++, str2++);
  if(*str1=='\0'||*str2=='\0'){
    str1--;
    str2--;
  }
  return *str1 - *str2;
}

void clstr(char *str1){                                   //clear str
  for(int i=0;i<520;i++){
    str1[i]='\0';
  }
}

int checkword(const char *str1){                          //check 4 cases
  int check=0;
  
  if(str1[0]=='\"'){
    check=3;
  }
  else{
    for(int i=0;i<520;i++){
      if(str1[i]==' '){
        check=2;
        break;
      }
      else if(str1[i]=='*'){
        check=4;
        break;
      }
      else{
        check=1;
      }
    }                                                    //end of for
  }                                                      //end of if else
  
  return check;
}

int inttostr(char *str1, const int num){
  int digit=0;
  int temp=num;
  int tempdi;
  
  while(temp>0){
    temp=temp/10;
    digit++;
  }
  if(num==0)digit=1;
  temp=num;
  tempdi=digit-1;
  while(tempdi>=0){
    str1[tempdi]=temp%10+'0';
    temp=temp/10;
    tempdi--;
  }
  
  return digit;
}

void printr(char *linestr, int Ldig, int line, char *indexstr, int Idig, int index, int out, int check){
char *dot=":";
char *blank=" ";

    Ldig=inttostr(linestr,line);
    write(STDOUT_FILENO,linestr,Ldig);
    write(out,linestr,Ldig);
  if(check==1||check==3){
    Idig=inttostr(indexstr,index);
    write(STDOUT_FILENO,dot,1);
    write(STDOUT_FILENO,indexstr,Idig);
    write(out,dot,1);
    write(out,indexstr,Idig);
   }
    write(STDOUT_FILENO,blank,1);
    write(out,blank,1);
}

int sep(char multi[250][520], const char *word){
  int i=0;
  int k=0;
  int j=0;
  
  while(word[i]!='\n'){
      if(word[i]==' '){
        multi[k][j+1]='\n';
        k++; j=0;
      }
      else{
        multi[k][j]=word[i];
        j++;
      }
    i++;
  }
  multi[k][j+1]='\n';
  return k;
}

int issame(char a, char b){
  if(a==b)
    return 1;
  else if(a-32==b)
    return 1;
  else if(a+32==b)
    return 1;
  else
    return 0;
}
#endif
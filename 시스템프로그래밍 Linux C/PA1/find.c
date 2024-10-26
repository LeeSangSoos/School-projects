#include "Head.h"

int main(int argc, char *argv[]){
int fd, out;
char buffer[520];
char word[520]="";
char clean[520]="";
char linestr[520]="", indexstr[520]="";
int Ldig, Idig;
int w=0,i=0, check;                       
const char *quit="PA1EXIT";
int line=1, index=0;
const char *jump="\n";
char sepr[250][520];
char two[2][520];
int wnum, found1=0, found2=0,  c3length=1;

fd=open(argv[1], O_RDONLY,00777);
out=open("result.out", O_WRONLY | O_CREAT,00777);

while(1){
  read(STDIN_FILENO, word, 520);
  if(strcmp2(word, quit)==0){
    break;
  }
  
  check=checkword(word);
  if(check==2){
    for(int a=0;a<250;a++){
      clstr(sepr[a]);
    }
    wnum=sep(sepr,word);
  }
  if(check==3){
    c3length=1;
    for(int a=1;a<520;a++){
      c3length++;
      if(word[a]=='"')break;
    }
  }
  if(check==4){
  int next;
    for(int i=0;i<520;i++){
      if(word[i]=='*'){
        next=i+1;
        break;
      }
      else{
        two[0][i]=word[i];
      }
    }
    for(int i=0;i<520;i++){
      if(word[i+next]=='\0'||word[i+next]==' '||word[i+next]=='\n'){
        break;
      }
      else{
        two[1][i]=word[i+next];
      }
    }
  }
  
  while(read(fd,buffer+i,1)>0){
    if(buffer[i]!='\n'){
      i++;
    }
    else{
      found2=0;
      if(check==1){
        for(int j=0;j<=i;j++){
          if(issame(word[0],buffer[j])==1&&(buffer[j-1]==' '||j==0)){
            for(int k=0;k<=i;k++){
              if((buffer[j+k]==' '||buffer[j+k]=='\n')&&(word[k]=='\n'||word[k]=='\0')){
                index=j;
                printr(linestr, Ldig, line, indexstr, Idig, index, out, check);
                break;
              } 
              else if(issame(word[k],buffer[j+k])==0){
                break;
              }
            }
          }
        } 
      }
      else if(check==2){
        for(int temps=wnum;temps>-1;temps--){
          for(int j=0;j<=i;j++){
            if(issame(sepr[temps][0],buffer[j])==1&&(buffer[j-1]==' '||j==0)){
              for(int k=0;k<=i;k++){
                if((buffer[j+k]==' '||buffer[j+k]=='\n')&&(sepr[temps][k]=='\n'||sepr[temps][k]=='\0')){
                  found1=1;
                  found2++;
                  break;
                } 
                else if(issame(sepr[temps][k],buffer[j+k])==0){
                  
                  break;
                }
              }
            }
            if(found1==1){
              found1=0;
              break;
            }
          }
        }
        if(found2==wnum+1){
          printr(linestr, Ldig, line, indexstr, Idig, index, out, check);
        }
      }
      else if(check==3){
        for(int j=0;j<=i;j++){
        
          if(issame(word[1],buffer[j])==1&&(buffer[j-1]==' '||j==0)){  
            for(int l=j;l<=i;l++){
            int c=0;
            if(issame(word[1],buffer[l])==1){
              for(int k=0;k<=i;k++){
              if(word[k+1]=='"'&&k+1==c3length-1){
                if(buffer[l+k]==' '||buffer[l+k]=='\n'){
                  index=l;
                  printr(linestr, Ldig, line, indexstr, Idig, index, out, check);
                  break;
                }
                else if(buffer[l+k]==word[1]){
                  int p=l+k;
                  for(int k=0;k<=i;k++){
                    if(word[k+1]=='"'&&k+1==c3length-1){
                      index=l;
                      printr(linestr, Ldig, line, indexstr, Idig, index, out, check);
                      break;
                    }
                    else if(issame(word[k+1],buffer[p+k])==0){
                      c=1;
                      break;
                    }
                  }
                }
                else{
                  c=1;
                  break;
                }
              }
              else if(issame(word[k+1],buffer[l+k])==0){
                c=1;
                break;
              }
              }
            }
            
            if(c==1){
              j=l;
              break;
            }
          }
        }
        
       } 
      }
      else if(check==4){
        found1=0;
          for(int j=0;j<=i;j++){
          if(found1==0){
            if(issame(two[0][0],buffer[j])==1&&(buffer[j-1]==' '||j==0)){
              for(int k=0;k<=i;k++){
                if((buffer[j+k]==' '||buffer[j+k]=='\n')&&(two[0][k]=='\n'||two[0][k]=='\0'||two[0][k]==' ')){
                  found1=1;
                  j=j+k;
                  break;
                } 
                else if(issame(two[0][k],buffer[j+k])==0){
                  
                  break;
                }
              }
            }
          }
          else if(found1==1){
            if(buffer[j]!=' '&&buffer[j]!='\0'){
              found1=2;
            }
          }
          else if(found1==2){
            if(issame(two[1][0],buffer[j])==1&&(buffer[j-1]==' '||j==0)){
              for(int k=0;k<=i;k++){
                if((buffer[j+k]==' '||buffer[j+k]=='\n')&&(two[1][k]=='\n'||two[1][k]=='\0'||two[1][k]==' ')){
                  found1=3;
                  break;
                } 
                else if(issame(two[1][k],buffer[j+k])==0){
                  
                  break;
                }
              }
            }
          }
          }
        if(found1==3){
          printr(linestr, Ldig, line, indexstr, Idig, index, out, check);
        }
      } 
      i=0;                                                // i=0
      line++;
      index=0;
    }                                                     //end of else
  }                                                     //end while of read
  
  off_t pos=lseek(fd,0,SEEK_SET);
  write(STDOUT_FILENO,jump,1);
  write(out,jump,1);
  line=1;
  index=0;
  clstr(word);                                            //clear word
}                                                         //end while 1


close(fd);
close(out);
exit(0);
return 0;
}
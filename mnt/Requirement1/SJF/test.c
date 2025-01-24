#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>


int main(){
int pid[15];
int i;
int c;
double number=25;
char processid[50];
for(i=1;i<=7;i++){

printf("Enter 1.CPU BOUND or 2.IO BOUND: \n");
scanf("%i",&c);
printf("Enter which number do you want:  \n");
 scanf("%lf", &number);
  pid[i]=fork();
  if(pid[i]==0){
    sprintf(processid,"%2d",i);
    if(c==1)
    execlp("./longrun00","./longrun00",processid,"100000","1000",NULL);
    else{
if(number<0){
printf("Can't Accept negative numbers \n");
printf("Please Enter a positive number: \n");
scanf("%lf",&number);
}
char numberStr[20];
snprintf(numberStr, sizeof(numberStr), "%f", number);

    execlp("./longrun01","./longrun01",processid,"100000","1000",numberStr,NULL);

  }
}
}
for(i=1;i<=10;i++){
  wait(NULL);
}
return 0;
}


#include <stdio.h>

#include <pthread.h>



int count=0;

int counter=0;



void *add1(void *data){



 int tmp;

 while(1){

  while(counter == 10)

   ;

  count++;

sleep(1);

  printf("add1 count= %d\n",count);

tmp=counter;

  sleep(1);

tmp=tmp+1;

counter=tmp;

 }

}



void *add2(void *data){

 int tmp;

 while(1){

  while(counter == 10)

   ;

  count++;

  printf("add2 count= %d\n",count);

  tmp=counter;

  sleep(1);

tmp=tmp+1;

counter=tmp;

 }

}



void *add3(void *data){

 int tmp;

 while(1){

  while(counter == 10)

   ;

  count++;

  printf("add3 count= %d\n",count);

  tmp=counter;

  sleep(1);

tmp=tmp+1;

counter=tmp;

 }

}



void *sub1(void *data){

 int tmp;

 while(1){

  while(counter== 0)

   ;

  count--;

  printf("sub1 count= %d \n",count);

tmp=counter;

  sleep(1);

tmp=tmp-1;

counter=tmp;
 }

}

void *sub2(void *data){int tmp;

 while(1){

  while(counter== 0)
   ;
  count--;
  printf("sub1 count= %d \n",count);
tmp=counter;
  sleep(1);
tmp=tmp-1;
counter=tmp;
 }
}

void *sub3(void *data){
 int tmp;
 while(1){
  while(counter== 0);
  count--;
  printf("sub1 count= %d \n",count);
tmp=counter;
  sleep(1);
tmp=tmp-1;
counter=tmp;
 }}
int main(){
 int i=0;
 pthread_t pthread[5];
 pthread_create(&pthread[0],NULL,add1,NULL);
 pthread_create(&pthread[1],NULL,sub1,NULL);
 pthread_create(&pthread[2],NULL,add2,NULL);
 pthread_create(&pthread[3],NULL,sub2,NULL);
 pthread_create(&pthread[4],NULL,add3,NULL);
 pthread_create(&pthread[5],NULL,sub3,NULL);
 for(i=0;i<6;i++)

  pthread_join(pthread[i],NULL);
 return 0;

}


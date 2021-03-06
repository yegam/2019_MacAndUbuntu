﻿

//# Template Code
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>
#define HUNGRY 0
#define EATING 1
#define THINKING 2
#define NUM_PHIL 5
#define EXEC_TIME 600

typedef struct philosopher {
   unsigned short numEat;
   int state;
   long wait;
} philosopher;

philosopher phil[NUM_PHIL];
sem_t chopstick[NUM_PHIL];
// 10~500 msec wait
int idlewait() {
   int sleepTimeMS = (rand() % 491 + 10);
   usleep(sleepTimeMS * 1000);
   return sleepTimeMS;
}

unsigned int tick() //get current time(msec)
{
   struct timeval tv;
   gettimeofday(&tv, (void*) 0);
   return tv.tv_sec * (unsigned int) 1000 + tv.tv_usec / 1000;
}

sem_t bi_sema;
void initPhil(void) {
   /* .............................................................................................. */
   for(int i = 0; i < NUM_PHIL; i++){
      phil[i].numEat = 0;
      phil[i].state = THINKING;
      phil[i].wait = 0;

      if(sem_init(&chopstick[i], 0, 1) == -1) {//bi_semaphore
         perror("Error");
         exit(0);
      }
   }

   if(sem_init(&bi_sema, 0, 1) == -1) {//bi_semaphore
      perror("Error");
      exit(0);
   }
}

void* dining(void* arg) {
   unsigned short i;
   unsigned short left, right;
   unsigned int start_time;
   unsigned int start_hungry, end_hungry;
   /* .............................................................................................. */

   int philosopher_id = (int)arg;
   left = philosopher_id;
   right = (philosopher_id + 4) % NUM_PHIL;
   start_time = tick();

   while((tick() - start_time) <= EXEC_TIME*1000){
      phil[philosopher_id].state = THINKING;
      idlewait();
      phil[philosopher_id].state = HUNGRY;
      start_hungry = tick();

      while(1){
         sem_wait(&bi_sema);
         int l_val, r_val;
         sem_getvalue(&chopstick[left], &l_val);
         sem_getvalue(&chopstick[right], &r_val);
         if(l_val == 1 && r_val == 1){
            break;
         }
         sem_post(&bi_sema);
      }

      end_hungry = tick();
      phil[philosopher_id].wait += end_hungry - start_hungry;
      phil[philosopher_id].state = EATING;
      phil[philosopher_id].numEat += 1;

      sem_wait(&chopstick[left]);
      sem_wait(&chopstick[right]);
      sem_post(&bi_sema);

      idlewait();
      sem_post(&chopstick[left]);
      sem_post(&chopstick[right]);
   }
   return NULL;
}

void main(void) {
   pthread_t t[NUM_PHIL];
   unsigned short i, args[NUM_PHIL], minCount = USHRT_MAX, maxCount = 0;
   long start, end, minWait = LONG_MAX, maxWait = 0, waitAVG = 0, waitVar = 0;

   double countAVG = 0, countVar = 0;

   srand(time((void*) 0));
   start = tick();
   initPhil();

   for (i = 0; i < NUM_PHIL; i++)
      args[i] = i;

   /* .............................................................................................. */
   pthread_t p_thread[NUM_PHIL];
   for(i = 0; i < NUM_PHIL; i++){
      if(pthread_create(&p_thread[i], NULL, dining, (void*)args[i]) < 0){
            perror("thread create error : ");
            exit(0);
      }
   }
   for(i = 0; i < NUM_PHIL; i++){
      pthread_join(p_thread[i], NULL);
   }

   end = tick();

   for (i = 0; i < NUM_PHIL; i++) {
      printf("Philosopher %d eating count : %d\nPhilosopher %d waiting time in HUNGRY state : %ld.%ld sec\n\n", i, phil[i].numEat, i, phil[i].wait / 1000, phil[i].wait % 1000);
      countAVG += phil[i].numEat;
      if (minCount > phil[i].numEat)
         minCount = phil[i].numEat;
      if (maxCount < phil[i].numEat)
         maxCount = phil[i].numEat;
      waitAVG += phil[i].wait;
      if (minWait > phil[i].wait)
         minWait = phil[i].wait;
      if (maxWait < phil[i].wait)
         maxWait = phil[i].wait;
   }
   countAVG /= NUM_PHIL;
   waitAVG /= NUM_PHIL;
   for (i = 0; i < NUM_PHIL; i++) {
      countVar += (countAVG-phil[i].numEat) * (countAVG-phil[i].numEat);
      waitVar += (waitAVG-phil[i].wait) * (waitAVG-phil[i].wait);
   }
   countVar /= NUM_PHIL;
   waitVar /= NUM_PHIL;
   printf("Min count : %d\nMax count : %d\nAVG count : %.3f\nCount variance : %.3f\n\n", minCount, maxCount, countAVG, countVar);
   printf("Min wait time in HUNGRY state : %ld.%ld sec\nMax wait time in HUNGRY state: %ld.%ld sec\nAVG wait time in HUNGRY state : %ld.%ld sec\nVariance wait time inHUNGRY state : %ld.%ld sec\n\n", minWait / 1000, minWait % 1000, maxWait / 1000, maxWait % 1000, waitAVG / 1000,waitAVG % 1000, waitVar / 1000000, (waitVar % 1000000) / 1000);
   printf("Total run time : %ld.%ld sec\n\n", (end-start)/ 1000, (end-start)% 1000);
}



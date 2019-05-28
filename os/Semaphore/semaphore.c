#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 
#include <time.h> 
#include <pthread.h> 
#include <semaphore.h> 
#define HUNGRY 0 
#define EATING 1 
#define THINKING 2 
#define NUM_PHIL 5 
#define EXEC_TIME 600
 
typedef struct philosopher 
{ 
    unsigned short numEat; 
    int state; 
    long wait; 
}philosopher; 

philosopher phil[NUM_PHIL]; 
sem_t chopstick[NUM_PHIL];
sem_t lock; 
pthread_mutex_t mutex;
// 10~500 msec wait 
int idlewait() 
{ 
    int sleepTimeMS = (rand() % 491 + 10); 
    usleep(sleepTimeMS * 1000); 
    return sleepTimeMS; 
} 
 
unsigned int tick() //get current time(msec) 
{ 
    struct timeval tv; 
    gettimeofday(&tv, (void*)0); 
    return tv.tv_sec * (unsigned int)1000 + tv.tv_usec / 1000; 
} 
void initPhil(void) 
{
/*------------------------------------------------------*/ 
	int i;
	for(i=0;i<NUM_PHIL;i++){
		sem_init(&chopstick[i],0,1);
		phil[i].numEat = 0;
		phil[i].state = THINKING;
		phil[i].wait = 0;
	}
/*------------------------------------------------------*/ 
} 
void* dining(void* arg) 
{ 
    unsigned short i = (int*)arg;
    unsigned short left, right;     
	unsigned int start_time;//wait 
    unsigned int start_hungry, end_hungry;
/*------------------------------------------------------*/ 
	int l,r,j,k;
	philosopher* currentPhil = &phil[i];
	left = i % NUM_PHIL;
	right = (i + 4) % NUM_PHIL;
	idlewait();
	start_time = tick();
	start_hungry = tick();

    currentPhil->state = HUNGRY;
	sem_getvalue(&chopstick[left],&l);
	sem_getvalue(&chopstick[right],&r);

	if(l == 1 && i % 2 == 0){
		sem_wait(&chopstick[left]);
		if(r == 1)
			sem_wait(&chopstick[right]);
		else{
			sem_post(&chopstick[left]);
			idlewait();
		}
	}
	else if(r == 1 && i % 2 == 1){
		sem_wait(&chopstick[right]);
		if(l == 1)
			sem_wait(&chopstick[left]);
		else{
			sem_post(&chopstick[right]);
			idlewait();
		}
	}

	k = 0;
		printf("phil[%d] State = %d\n",i,currentPhil->state);

	if(currentPhil->state == HUNGRY && phil[left].state != EATING && phil[right].state != EATING){
		/*for(j=0;j<NUM_PHIL;j++){
			sem_getvalue(&chopstick[j],&r);//
			printf("i = %d semavalue = %d \n",j,r);
		}*/

		sem_getvalue(&chopstick[left],&l);
		sem_getvalue(&chopstick[right],&r);
		printf("HUNGRY[%d] left = %d right = %d \n",i,l,r);
		while (start_time /1000< EXEC_TIME && l== 0 && r == 0){//random하게 돌리기
			if ( k == 0)
				printf("EATING[%d] \n\n",i);
			k++;
			end_hungry = tick();//while에서 무한루프한다.
			currentPhil->state = EATING;
			currentPhil->wait += (end_hungry - start_hungry);
			currentPhil->numEat++;
		}
	}
	printf("AFTER EATING[%d] numEat = %d\n",i,currentPhil->numEat);
	sem_getvalue(&chopstick[left],&l);//
	sem_getvalue(&chopstick[right],&r);//
	if(currentPhil->state == EATING && l == 0 && r == 0){
		sem_post(&chopstick[left]);
		sem_post(&chopstick[right]);
	}
	sem_getvalue(&chopstick[left],&l);//
	sem_getvalue(&chopstick[right],&r);//
	printf("after left = %d right = %d \n",l,r);
	currentPhil->state = THINKING;
	for(j=0;j<NUM_PHIL;j++){
		sem_getvalue(&chopstick[j],&r);//
		printf("i = %d semavalue = %d \n",j,r);
	}
    return (void*)NULL;
/*------------------------------------------------------*/ 
} 
 
void main(void) 
{ 
    pthread_t t[NUM_PHIL]; 
    unsigned short i, args[NUM_PHIL], minCount = USHRT_MAX, maxCount =0; 
    long start, end, minWait = LONG_MAX, maxWait = 0, waitAVG = 0, waitVar = 0; 
 
    double countAVG = 0, countVar = 0; 
 
    srand(time((void*)0)); 
    start = tick(); 
    initPhil(); 
/*------------------------------------------------------*/ 
	//sem_init(&lock, 0, NUM_PHIL - 1);
    for(i=0;i<NUM_PHIL;i++){ 
		args[i] = i;
		pthread_create(&t[i],NULL,dining,args[i]);
	}
 
 	for(i=0;i<NUM_PHIL;i++)
		pthread_join(t[i],NULL);
    end = tick(); 
   	for(i=0; i<NUM_PHIL; i++)
        sem_destroy(&chopstick[i]);
/*------------------------------------------------------*/ 

    for(i=0;i<NUM_PHIL;i++) 
    { 
        printf("Philosopher %d eating count : %d\nPhilosopher %d waiting time in HUNGRY state : %ld.%ld sec\n\n", i, phil[i].numEat, i, phil[i].wait / 1000, phil[i].wait % 1000); 
        countAVG += phil[i].numEat; 
        if(minCount > phil[i].numEat) 
            minCount = phil[i].numEat; 
        if(maxCount < phil[i].numEat) 
            maxCount = phil[i].numEat; 
        waitAVG += phil[i].wait; 
        if(minWait > phil[i].wait) 
            minWait = phil[i].wait; 
        if(maxWait < phil[i].wait) 
            maxWait = phil[i].wait; 
    } 
    countAVG /= NUM_PHIL; 
    waitAVG /= NUM_PHIL; 
    for(i=0;i<NUM_PHIL;i++) 
    {         
		countVar += (countAVG - phil[i].numEat) * (countAVG - phil[i].numEat);
		waitVar += (waitAVG - phil[i].wait) * (waitAVG - phil[i].wait);
    } 
    countVar /= NUM_PHIL; 
    waitVar /= NUM_PHIL; 
    printf("Min count : %d\nMax count : %d\nAVG count : %.3f\nCount variance : %.3f\n\n",minCount, maxCount, countAVG, countVar); 
    printf("Min wait time in HUNGRY state : %ld.%ld sec\nMax wait time in HUNGRY state: %ld.%ld sec\nAVG wait time in HUNGRY state : %ld.%ld sec\nVariance wait time in HUNGRY state : %ld.%ld sec\n\n", minWait / 1000, minWait % 1000, maxWait / 1000, maxWait % 1000, waitAVG / 1000,waitAVG % 1000, waitVar / 1000000, (waitVar % 1000000) / 1000);
	printf("Total run time : %ld.%ld sec\n\n", (end - start)/ 1000, (end - start)% 1000);
} 
 
 
 


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
int global_time;

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
/*------------------------------------------------------*///제가 고친 부분에 대한 구분선입니다. 
void initPhil(void) 
{
	int i;
	for(i=0;i<NUM_PHIL;i++){//초기화 함수입니다.
		sem_init(&chopstick[i],0,1);//sem_init를 통해 초기화 합니다.
		phil[i].numEat = 0;
		phil[i].state = THINKING;
		phil[i].wait = 0;
	}
} 
/*------------------------------------------------------*/ 
/*------------------------------------------------------*/
void* dining(void* arg) 
{ 
    unsigned short i = (int*)arg;
    unsigned short left, right;     
	unsigned int start_time,rand_time;
    unsigned int start_hungry, end_hungry;
	int l,r;
	philosopher* currentPhil = &phil[i];//현재 진행중인 스레드(철학자)를 포인터로 받습니다.
	left = i % NUM_PHIL;//철학자의 index를 기준으로 left와 right의 index를 계산합니다.
	right = (i + 4) % NUM_PHIL;
	idlewait();//각 스레드 별로 랜덤하게 기다린 후 스레드의 state를 변경합니다.

    currentPhil->state = HUNGRY;

	start_hungry = tick();
	while(currentPhil->state == HUNGRY){
		sem_getvalue(&chopstick[left],&l);//세마포어변수를 통해 젓가락을 잡을 수 있는지 판단합니다.
		sem_getvalue(&chopstick[right],&r);
		if(l == 1 && i % 2 == 0){//짝수 인덱스를 가진 스레드인 경우에는 왼쪽부터 잡습니다.
			sem_wait(&chopstick[left]);
			if(r == 1){
				sem_wait(&chopstick[right]);
    			currentPhil->state = EATING;//양쪽 모두 잡을 경우 state를 변경합니다. 
			}
			else{
				sem_post(&chopstick[left]);
				idlewait();
			}
		}
		else if(r == 1 && i % 2 == 1){//홀수 인덱스를 가진 스레드의 경우에는 오른쪽 부터 잡습니다.
			sem_wait(&chopstick[right]);
			if(l == 1){
				sem_wait(&chopstick[left]);
    			currentPhil->state = EATING;
			}
			else{
				sem_post(&chopstick[right]);
				idlewait();
			}
		}
	}
	end_hungry = tick();//hungry가 끝났기 때문에 시간을 측정합니다.
	start_time = tick();
	sem_getvalue(&chopstick[left],&l);
	sem_getvalue(&chopstick[right],&r);

	while(currentPhil->state == EATING && l == 0 && r ==0) {//state와 왼쪽 오른쪽 젓가락 상태를 검사합니다.
		while ( (tick() - start_time)/100 < EXEC_TIME ){//먹습니다.
			currentPhil->wait += (end_hungry - start_hungry);
			currentPhil->numEat++;
		}
		break;
	}
	sem_getvalue(&chopstick[left],&l);
	sem_getvalue(&chopstick[right],&r);
	if(currentPhil->state == EATING && l == 0 && r == 0){//Eating의 상태였고 젓가락을 모두 가지고 있던 상태였다면 젓가락을 반납합니다.
		sem_post(&chopstick[left]);
		sem_post(&chopstick[right]);
	}
	currentPhil->state = THINKING;//상태를 바꿉니다.
    return (void*)NULL;
} 
/*------------------------------------------------------*/ 
 
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
    for(i=0;i<NUM_PHIL;i++){ 
		args[i] = i;
		pthread_create(&t[i],NULL,dining,args[i]);//스레드 생성
	} 
 	for(i=0;i<NUM_PHIL;i++)
		pthread_join(t[i],NULL);

   	for(i=0; i<NUM_PHIL; i++)
        sem_destroy(&chopstick[i]);
    end = tick(); 
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
 
 
 


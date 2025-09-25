#include <stdio.h>
#include <assert.h>
#include <pthread.h>

static volatile int counter = 0;

void *mythread(void *arg) {
    printf("%s: begin\n", (char *) arg);
    int i;
    // 전역변수 counter를 1씩 100만번 증가시킵니다.
    for (i = 0; i < 1000000; i++){
        counter += 1;
    }
    printf("%s: done\n", (char *) arg);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p1, p2;
    printf("main: begin (counter = %d)\n", counter);
    pthread_create(&p1, NULL, mythread, "A");
    pthread_create(&p2, NULL, mythread, "B");

    pthread_join(p1,NULL);
    pthread_join(p2,NULL);

    printf("main: done (counter = %d)\n",counter);
    return 0;
}

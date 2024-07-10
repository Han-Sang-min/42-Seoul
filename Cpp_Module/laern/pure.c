#include <pthread.h>
#include <stdio.h>

void *thread_func(void *arg) {
    int *sh = (int *)arg;
    printf("Hello from thread_func\n");
    return NULL;
}

int main() {
    pthread_t thread;
    int sh_value = 42;
    printf("sh_value address: %p\n", &sh_value);

    pthread_create(&thread, NULL, thread_func, &sh_value);
    pthread_join(thread, NULL);

    printf("Hello from main\n");

    return 0;
}

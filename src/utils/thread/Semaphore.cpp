//
// Created by fred on 30/07/16.
//

#include "Semaphore.h"


Semaphore::Semaphore(int num)
{
    resources = num;
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);
}

void Semaphore::semaphore_wait()
{
    pthread_mutex_lock(&lock);
    while(resources <= 0)
        pthread_cond_wait(&cond, &lock);
    resources--;
    pthread_mutex_unlock(&lock);
}

void Semaphore::semaphore_post()
{
    pthread_mutex_lock(&lock);
    resources++;
    pthread_mutex_unlock(&lock);
    pthread_cond_signal(&cond);
}
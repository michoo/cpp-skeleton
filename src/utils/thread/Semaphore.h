//
// Created by fred on 30/07/16.
//

#ifndef OPENCV_TUTO_SEMAPHORE_H
#define OPENCV_TUTO_SEMAPHORE_H


#include <iostream>
#include <pthread.h>


class Semaphore
{
    int resources;
    pthread_cond_t cond;
    pthread_mutex_t lock;
public:
    Semaphore(int);
    void semaphore_wait();
    void semaphore_post();
};


#endif //OPENCV_TUTO_SEMAPHORE_H

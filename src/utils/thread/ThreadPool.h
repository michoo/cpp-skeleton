//
// Created by fred on 30/07/16.
//

#ifndef OPENCV_TUTO_THREADPOOL_H
#define OPENCV_TUTO_THREADPOOL_H

#include <iostream>
#include <queue>
#include <pthread.h>
#include <time.h>
#include <cstdlib>
#include "ConcurrentQueue.h"


#define QUEUE_SIZE  40
#define PRODUCER_THREAD 1
#define CONSUMER_THREAD 6
#define WAITING_TIME 3




class ThreadPool {

    enum ThreadPoolStatus {INITIALIZED,STARTED,STOPPED,PAUSED};

public:

    virtual ~ThreadPool(){
        LOG(TRACE) << "ThreadPool delete";
    };
    bool produce(Task &p);
    bool consume(Task &c);
    void init();
    void pause();
    void stop();
    void start();
    ThreadPoolStatus status;
    static void* threadExecute(void *cq);
    static ThreadPool* Instance();




private:
    ThreadPool();
    ConcurrentQueue pool;
    int pID;
    int cID;

//    std::vector<pthread_t> p;
//    std::vector<pthread_t> c;
    pthread_t pt[PRODUCER_THREAD];
    pthread_t ct[CONSUMER_THREAD];
    static ThreadPool* m_pInstance;
    //Semaphore semaphoreProducer;
    //Semaphore semaphoreConsumer;

};


#endif //OPENCV_TUTO_THREADPOOL_H

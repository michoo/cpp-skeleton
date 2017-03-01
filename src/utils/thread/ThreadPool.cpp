#include "ThreadPool.h"
#include "../Common.h"

ThreadPool* ThreadPool::m_pInstance = NULL;

ThreadPool* ThreadPool::Instance()
{
if (!m_pInstance){
    // Only allow one instance of class to be generated.
    m_pInstance = new ThreadPool;
    LOG(TRACE) << "ThreadPool instanciation";
}
return m_pInstance;

}

ThreadPool::ThreadPool():status(INITIALIZED),
                         pID(0),
                         cID(0),
                         pool(QUEUE_SIZE) {
    init();
}

bool ThreadPool::produce(Task &p)
{
    //if max size of queue is overloaded then wait
    return pool.push(p);
}

bool ThreadPool::consume(Task &c)
{
    return pool.pop(c);

}

void ThreadPool::init() {
    //create threads for consumption
    for(int i = 0; i < CONSUMER_THREAD; i++)
    {
        pthread_create(&ct[i], NULL, &threadExecute, this);
        LOG(TRACE) << "Consumer Thread:" << i << " is alive now!";
    }

}

void ThreadPool::pause() {
    status=PAUSED;
}

void ThreadPool::stop(){
    status=STOPPED;
    LOG(TRACE) << "Stopping Threadpool";
    pool.stop();
}

void ThreadPool::start() {
    status=STARTED;
    //big while with
    //if ressoures available consume new one
}


void* ThreadPool::threadExecute(void *cq)
{
    ThreadPool *p = (ThreadPool*)cq;
    Task oneJob;
    while(p->status != STOPPED)
    {
        if(p->status == STARTED){
            p->consume(oneJob);
            oneJob.execute();
        }
        if(p->status == PAUSED){
            sleep(5);
        }
    }

    LOG(TRACE) << "End of this thread";

}


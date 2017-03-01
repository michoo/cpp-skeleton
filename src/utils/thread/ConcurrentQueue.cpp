#include "ConcurrentQueue.h"
#include "../Common.h"

ConcurrentQueue::ConcurrentQueue(int maxSize)
{
    max = maxSize;
    pthread_mutex_init(&push_mutex, NULL);
    pthread_mutex_init(&pop_mutex, NULL);
    pthread_cond_init(&pop_cond, NULL);
    pthread_cond_init(&push_cond, NULL);
    quit = false;
}

bool ConcurrentQueue::push(Task& data)
{
    pthread_mutex_lock(&push_mutex);
    while(_queue_.size()>=max){

        if(quit){
            LOG(DEBUG) << "producer stopping";
            return false;
        }
        pthread_cond_wait(&push_cond, &push_mutex);
    }

    _queue_.push(data);
    LOG(DEBUG) << "producer: " << data.getID() << " pushed ";
    //pthread_cond_signal(&pop_cond);
    pthread_mutex_unlock(&push_mutex);
    return true;
}

bool ConcurrentQueue::pop(Task& popped_data)
{
    pthread_mutex_lock(&pop_mutex);
    while(_queue_.empty()){

        if(quit){
            LOG(DEBUG) << "consumer stopping";
            return false;
        }

        pthread_cond_wait(&pop_cond, &pop_mutex);
    }

    popped_data = _queue_.front();
    _queue_.pop();
    LOG(DEBUG) << "consume: " << popped_data.getID() << " popped";
    //pthread_cond_signal(&push_cond);
    pthread_mutex_unlock(&pop_mutex);
    return true;
}

bool ConcurrentQueue::stop() {
    quit = true;
    pthread_cond_signal(&push_cond);
    pthread_cond_signal(&pop_cond);
    return quit;
}

int ConcurrentQueue::size(){
    return _queue_.size();
}
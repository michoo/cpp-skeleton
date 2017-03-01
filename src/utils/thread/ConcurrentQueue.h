#ifndef OPENCV_TUTO_CONCURRENTQUEUE_H
#define OPENCV_TUTO_CONCURRENTQUEUE_H

#include <queue>
#include <pthread.h>
#include <time.h>
#include <cstdlib>
#include "Task.h"

class ConcurrentQueue {
private:
    std::queue<Task> _queue_;
    pthread_mutex_t push_mutex;
    pthread_mutex_t pop_mutex;
    pthread_cond_t pop_cond;
    pthread_cond_t push_cond;
    int max;
    bool quit;
public:
    ConcurrentQueue(int maxSize);
    bool push(Task& data);
    bool pop(Task& popped_data);
    bool stop();
    int size();

};


#endif //OPENCV_TUTO_CONCURRENTQUEUE_H

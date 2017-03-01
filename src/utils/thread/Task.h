//
// Created by fred on 28/07/16.
//

#ifndef OPENCV_TUTO_TASK_H
#define OPENCV_TUTO_TASK_H


#include <pthread.h>
#include <unistd.h>
#include <queue>
#include <iostream>
#include "../log/easylogging++.h"



enum TaskStatus {NOT_DEFINED,TODO,DONE,FAILED};

//template<class TClass>
class Task {
public:

    Task(int id) : taskID(id), taskStatus(TODO){};
    Task():taskStatus(NOT_DEFINED){};

    virtual ~Task(){
        //LOG(DEBUG) << "Task:" << taskID << " destroyed! " << this;
    };

    //will be overrided by specific JOB
    virtual void execute()
    {
        taskStatus = DONE;
        LOG(DEBUG) << "Task:" << taskID << " done!";

    };

    int getID(){
        return taskID;
    };

private:
    int taskID;
    TaskStatus taskStatus;

};


#endif //OPENCV_TUTO_TASK_H

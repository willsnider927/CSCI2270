#include <iostream>
#include "JobQueue.hpp"

using namespace std;

JobQueue::JobQueue() {
    queueFront = 0;
    queueEnd = 0;
    counter = 0;
}

bool JobQueue::isEmpty() {
    return(counter == 0);
}

bool JobQueue::isFull() {
    return(counter == SIZE);
}

void JobQueue::enqueue(string job) {
    if (isFull()) {
        cout << "Queue full, cannot add new job" << endl;
    }
    else {
        queue[queueEnd] = job;
        if (queueEnd == SIZE-1) queueEnd = 0;
        else queueEnd++;
        counter++;
    }
}

void JobQueue::dequeue() {
    if (isEmpty()) {
        cout << "Queue empty, cannot dequeue a job" << endl;
    }
    else  {
        if (queueFront == SIZE-1) queueFront = 0;
        else queueFront++;
        counter--;
    }
}

int JobQueue::queueSize() {
    return counter; 
}

string JobQueue::peek() {
    if (isEmpty()) {
        cout << "Queue empty, cannot peek" << endl;
        return {};
    }
    else return queue[queueFront];
}
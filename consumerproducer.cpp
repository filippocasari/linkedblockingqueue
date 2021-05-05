#include <iostream>

#include <thread>
#include <vector>
#include "linkingblockingqueue.h"

using namespace std;

// Number of producer threads to start
// Must be greater than zero
const int num_producers = 10;
// Number of integers to be produced by each producer thread
// Must be greater than zero
const int producer_amount = 100;
// Number of consumer threads to start
// Must be greater than zero
const int num_consumers = 5;
// producers * producer_amount / consumers must be a whole integer
queue<int> *queue_message;
void producer()
{
    int i;
    int value;

    for (i = 0; i < producer_amount; ++ i)
    {
        cout<<"value pushed: "<<i<<endl;
        value=i;
        queue_message->push(value);
    }
}

void consumer()
{
    int i;
    for (i = 0; i < producer_amount * num_producers / num_consumers; ++ i)
    {
        int value = queue_message->pop();
        cout<<"Value dequeued: \t"<<value<<endl;
    }
}

int main()
{



    int i;
    vector<thread> producers;
    vector<thread> consumers;
    //thread producers[num_producers];
    //thread consumers[num_consumers];
    for (i = 0; i < producers.size();  i++)
    {
       producers[i]= thread(producer);

    }
    for (i = 0; i < consumers.size(); i++)
    {
        producers[i]=thread(consumer);
    }
    for (i = 0; i < producers.size(); i++)
    {
        producers[i].join();
    }
    for (i = 0; i < consumers.size(); i++)
    {
        consumers[i].join();
    }
}


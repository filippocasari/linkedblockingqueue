#include "blocking_queue.h"
int main() {
    blocking_queue<int> queue(5);

    // create producers
    std::vector<std::thread> producers;
    for (int i = 0; i < 1; i++) {
        producers.emplace_back([&queue, i]() {
            for(int a=0; a<100; a++) {
                std::cout<<"THREAD PRODUCER: "<<i<<" IS PUSHING"<<std::endl;
                queue.push(a);

                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
            //queue.push(i);
            //std::cout<<"Pushing value: "<<i<<std::endl;
            // produces too fast

        });
    }

    // create consumers
    std::vector<std::thread> consumers;
    for (int i = 0; i < 5; i++) {
        producers.emplace_back([&queue, i]() {
            int count=0;
            while(1){
                if(!queue.empty()){
                    std::cout<<"\nTHREAD CONSUMER : "<<i<<" IS POPPING"<<std::endl;
                    int a= (int) queue.pop();
                    count--;

                }else{
                    count++;
                }
                if(count>100){
                    break;
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(100));

            }

            //std::cout<<"popping value: "<<a<<std::endl;
            // consumes too slowly

        });
    }

    std::for_each(producers.begin(), producers.end(), [](std::thread &thread) {
        thread.join();
    });

    std::for_each(consumers.begin(), consumers.end(), [](std::thread &thread) {
        thread.join();
    });

    return EXIT_SUCCESS;
}


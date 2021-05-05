//
// Created by filippocasari on 05/05/21.
//

#ifndef LINKEDBLOCKINGQUEUE_LINKINGBLOCKINGQUEUE_H
#define LINKEDBLOCKINGQUEUE_LINKINGBLOCKINGQUEUE_H


#include <mutex>
#include <condition_variable>
#include <deque>

template <typename T>
class queue
{
private:
    std::mutex              d_mutex;
    std::condition_variable d_condition;
    std::deque<T>           d_queue;
public:
    void push(T const& value) {
        {
            std::unique_lock<std::mutex> lock(this->d_mutex);
            d_queue.push_front(value);
        }
        this->d_condition.notify_one();
    }
    T pop() {
        std::unique_lock<std::mutex> lock(this->d_mutex);
        this->d_condition.wait(lock, [=]{ return !this->d_queue.empty(); });
        T rc(std::move(this->d_queue.back()));
        this->d_queue.pop_back();
        return rc;
    }
};


#endif //LINKEDBLOCKINGQUEUE_LINKINGBLOCKINGQUEUE_H

//
// Created by Atin Sakkeer Hussain on 08/04/2023.
//

#ifndef SPA_CONCURRENTVECTOR_H
#define SPA_CONCURRENTVECTOR_H

#include "QPS/Expressions/Expressions.h"
#include <mutex>


template <typename T>
class ThreadSafeVector {
public:
    ThreadSafeVector() = default;

    void push_back(const T& value) {
        std::unique_lock<std::mutex> lock(mutex_);
        data_.push_back(value);
    }

    void pop_back() {
        std::unique_lock<std::mutex> lock(mutex_);
        if (!data_.empty()) {
            data_.pop_back();
        }
    }

    T back() const {
        std::unique_lock<std::mutex> lock(mutex_);
        if (!data_.empty()) {
            return data_.back();
        }
        return T{};
    }

    bool empty() const {
        std::unique_lock<std::mutex> lock(mutex_);
        return data_.empty();
    }

    size_t size() const {
        std::unique_lock<std::mutex> lock(mutex_);
        return data_.size();
    }

    void clear() {
        std::unique_lock<std::mutex> lock(mutex_);
        data_.clear();
    }

    typename std::vector<T>::const_iterator begin() const {
        std::unique_lock<std::mutex> lock(mutex_);
        return data_.begin();
    }

    typename std::vector<T>::const_iterator end() const {
        std::unique_lock<std::mutex> lock(mutex_);
        return data_.end();
    }

private:
    mutable std::mutex mutex_;
    std::vector<T> data_;
};


#endif //SPA_CONCURRENTVECTOR_H

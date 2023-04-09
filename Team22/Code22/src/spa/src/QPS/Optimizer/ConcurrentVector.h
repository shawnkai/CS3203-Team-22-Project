//
// Created by Atin Sakkeer Hussain on 08/04/2023.
//

#ifndef SPA_CONCURRENTVECTOR_H
#define SPA_CONCURRENTVECTOR_H

#include "QPS/Expressions/Expressions.h"
#include <mutex>


template <typename T>

/*
 * A class for creating a thread-safe vector.
 */
class ThreadSafeVector {
public:
    /**
     * Constructs a new ThreadSafeVector object.
     */
    ThreadSafeVector() = default;

    /**
     * Adds an element to the end of the vector in a thread-safe manner.
     *
     * @param value the element to add to the vector
     */
    void push_back(const T& value) {
        std::unique_lock<std::mutex> lock(mutex_);
        data_.push_back(value);
    }

    /**
     * Removes the last element from the vector in a thread-safe manner if the vector is not empty.
     */
    void pop_back() {
        std::unique_lock<std::mutex> lock(mutex_);
        if (!data_.empty()) {
            data_.pop_back();
        }
    }

    /**
     * Returns the last element in the vector in a thread-safe manner.
     * If the vector is empty, returns the default value of type T.
     *
     * @return the last element in the vector
     */
    T back() const {
        std::unique_lock<std::mutex> lock(mutex_);
        if (!data_.empty()) {
            return data_.back();
        }
        return T{};
    }

    /**
     * Checks if the vector is empty in a thread-safe manner.
     *
     * @return true if the vector is empty, false otherwise
     */
    bool empty() const {
        std::unique_lock<std::mutex> lock(mutex_);
        return data_.empty();
    }

    /**
     * Returns the number of elements in the vector in a thread-safe manner.
     *
     * @return the number of elements in the vector
     */
    size_t size() const {
        std::unique_lock<std::mutex> lock(mutex_);
        return data_.size();
    }


    /**
     * Removes all elements from the vector in a thread-safe manner.
     */
    void clear() {
        std::unique_lock<std::mutex> lock(mutex_);
        data_.clear();
    }

    /**
     * Returns a constant iterator to the beginning of the vector in a thread-safe manner.
     *
     * @return a constant iterator to the beginning of the vector
     */
    typename std::vector<T>::const_iterator begin() const {
        std::unique_lock<std::mutex> lock(mutex_);
        return data_.begin();
    }

    /**
     * Returns a constant iterator to the end of the vector in a thread-safe manner.
     *
     * @return a constant iterator to the end of the vector
     */
    typename std::vector<T>::const_iterator end() const {
        std::unique_lock<std::mutex> lock(mutex_);
        return data_.end();
    }

private:
    mutable std::mutex mutex_;
    std::vector<T> data_;
};


#endif //SPA_CONCURRENTVECTOR_H

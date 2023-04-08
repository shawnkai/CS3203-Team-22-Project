//
// Created by Atin Sakkeer Hussain on 08/04/2023.
//

#ifndef SPA_PARALLEL_H
#define SPA_PARALLEL_H

#include <algorithm>
#include <thread>
#include <functional>
#include <vector>

/***
 * This .h library is adopted from the following stack overflow answer relating to parallelization of for loops
 */

/***
 * @param[in] nbElements : size of your for loop
 * @param[in] functor(start, end) :
 * your function processing a sub chunk of the for loop.
 * "start" is the first index to process (included) until the index "end"
 * (excluded)
 * @code
 *      for(int i = start; i < end; ++i)
 *          computation(i);
 * @endcode
 * @param useThreads : enable / disable threads.
 */
static
void parallelFor(unsigned nbElements,
                 const std::function<void (unsigned int start, unsigned int end)>& functor,
                 bool useThreads = true)
{
    // -------
    unsigned nbThreadsHint = std::thread::hardware_concurrency();
    unsigned nbThreads = nbThreadsHint == 0 ? 8 : (nbThreadsHint);

    unsigned batchSize = nbElements / nbThreads;
    unsigned batchRemainder = nbElements % nbThreads;

    std::vector< std::thread > myThreads(nbThreads);

    if( useThreads )
    {
        // Multithread execution
        for(unsigned i = 0; i < nbThreads; ++i)
        {
            unsigned int start = i * batchSize;
            myThreads[i] = std::thread(functor, start, start + batchSize);
        }
    }
    else
    {
        // Single thread execution (for easy debugging)
        for(unsigned i = 0; i < nbThreads; ++i){
            unsigned int start = i * batchSize;
            functor( start, start + batchSize );
        }
    }

    // Deform the elements left
    unsigned int start = nbThreads * batchSize;
    functor( start, start + batchRemainder);

    // Wait for the other thread to finish their task
    if( useThreads )
        std::for_each(myThreads.begin(), myThreads.end(), std::mem_fn(&std::thread::join));
}

#endif //SPA_PARALLEL_H

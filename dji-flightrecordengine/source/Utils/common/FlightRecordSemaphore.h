//
//  FlightRecordSemaphore.h
//  FlightRecordEngine
//
//  Copyright © 2017 DJI. All rights reserved.
//

#ifndef FlightRecordSemaphore_h
#define FlightRecordSemaphore_h

namespace DJI {
    namespace FlightRecord {
        class Semaphore
        {
        private:
            std::mutex mutex_;
            std::condition_variable condition_;
            unsigned long count_ = 0; // Initialized as locked.

        public:
            void Notify() {
                std::unique_lock<decltype(mutex_)> lock(mutex_);
                ++count_;
                condition_.notify_one();
            }

            void Wait() {
                std::unique_lock<decltype(mutex_)> lock(mutex_);
                while(!count_) // Handle spurious wake-ups.
                    condition_.wait(lock);
                --count_;
            }

            bool TryWait() {
                std::unique_lock<decltype(mutex_)> lock(mutex_);
                if(count_) {
                    --count_;
                    return true;
                }
                return false;
            }
        };
    }
}

#endif /* FlightRecordSemaphore_h */

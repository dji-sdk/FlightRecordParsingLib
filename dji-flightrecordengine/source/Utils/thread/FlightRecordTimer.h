//
//  FlightRecordTimer.h
//  FlightRecordEngine
//
//  Copyright © 2017 DJI. All rights reserved.
//

#ifndef FlightRecordTimer_h
#define FlightRecordTimer_h

#include <stdio.h>
#include <chrono>
#include <memory>
#include <queue>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

typedef uint64_t Tick;

namespace DJI {
    namespace FlightRecord {
        class TimerScheduler;
        class TimerSession;
        using TimerSessionPtr = std::shared_ptr<TimerSession>;

        class Timer;
        using TimerPtr = std::shared_ptr<Timer>;
        using TimerWeakPtr = std::weak_ptr<Timer>;

        class TimerSession {
        public:
            bool Valid();

        private:
            enum class Result {
                Cancelled,
                Pending,
                Timesup,
            };

            std::chrono::time_point<std::chrono::high_resolution_clock> m_nextTick;
            TimerWeakPtr m_pTimer;
            std::mutex m_mutex;

            friend class Timer;
            friend class TimerScheduler;
        };

        class Timer : public std::enable_shared_from_this<Timer> {
        public:
            static TimerPtr CreateTimer(std::chrono::milliseconds interval, std::function<void(TimerSessionPtr)> func = nullptr);

            Timer(std::chrono::milliseconds interval, std::function<void(TimerSessionPtr)> func = nullptr);
            ~Timer() {}

            void Start(bool fireNow, std::shared_ptr<TimerScheduler> scheduler);
            void Stop();

            std::mutex m_mutex;
            std::chrono::milliseconds m_interval;
            TimerSessionPtr m_pCurrentSession;
            std::function<void(TimerSessionPtr)> m_func;
        };

        using TimerPtr = std::shared_ptr<Timer>;
    }
}

namespace DJI {
    namespace FlightRecord {

        class TimerScheduler : public std::enable_shared_from_this<TimerScheduler> {
        public:
            using TimerQueue = std::priority_queue<
            TimerSessionPtr,
            std::vector<TimerSessionPtr>,
            std::function<bool(const TimerSessionPtr&, const TimerSessionPtr&)>>;

            TimerScheduler(std::chrono::milliseconds resolution = std::chrono::milliseconds(10));
            ~TimerScheduler(); 

            void addTimer(const TimerSessionPtr& timer);

            // Call this before release TimerScheduler
            void Cleanup();

        private:
            void StartThread();

        private:
            std::shared_ptr<TimerQueue> m_pTimers;
            std::chrono::milliseconds m_resolution;
            std::shared_ptr<std::thread> m_pThread;
			std::weak_ptr<TimerScheduler> weak_protector_;
            std::mutex m_mutex;
            std::condition_variable m_endCondition;
        };

        using TimerSchedulerPtr = std::shared_ptr<TimerScheduler>; 
    }
}

#endif /* FlightRecordTimer_h */

//
//  FlightRecordTimer.cpp
//  FlightRecordEngine
//
//  Copyright © 2017 DJI. All rights reserved.
//

#include <stdio.h>
#include <Utils/thread/FlightRecordTimer.h>
#include <functional>

using namespace DJI::FlightRecord;

bool TimerSession::Valid() {
    std::lock_guard<std::mutex> sessionGuard(m_mutex);
    auto pTimer = m_pTimer.lock();
    if (pTimer == nullptr) {
        return false;
    }
    else {
        std::lock_guard<std::mutex> timerGuard(pTimer->m_mutex);
        if (pTimer->m_pCurrentSession.get() == this) {
            return true;
        }
    }
    return false;
}

TimerPtr Timer::CreateTimer(std::chrono::milliseconds interval, std::function<void (TimerSessionPtr)> func) {
    return std::make_shared<Timer>(interval, func);
}

Timer::Timer(std::chrono::milliseconds interval, std::function<void(TimerSessionPtr)> func) :
m_interval(interval), m_pCurrentSession(nullptr), m_func(func) {
}

void Timer::Start(bool fireNow, std::shared_ptr<TimerScheduler> scheduler) {
    std::lock_guard<std::mutex> guard(m_mutex);
    if (m_pCurrentSession != nullptr) {
        return;
    }

    m_pCurrentSession = std::make_shared<TimerSession>();
    m_pCurrentSession->m_pTimer = shared_from_this();
    m_pCurrentSession->m_nextTick = std::chrono::high_resolution_clock::now();
    if (!fireNow) {
        m_pCurrentSession->m_nextTick += m_interval;
    }

    if (scheduler) {
        scheduler->addTimer(m_pCurrentSession);
    }
}

void Timer::Stop() {
    std::lock_guard<std::mutex> guard(m_mutex);
    if (m_pCurrentSession == nullptr) {
        return;
    }
    m_pCurrentSession = nullptr;
}

TimerScheduler::TimerScheduler(std::chrono::milliseconds resolution) :
m_pTimers(nullptr),
m_pThread(nullptr),
m_resolution(resolution) {
    m_pTimers = std::make_shared<TimerQueue>([](const TimerSessionPtr& lhs, const TimerSessionPtr& rhs) {
        return (lhs->m_nextTick > rhs->m_nextTick);
    });
}

TimerScheduler::~TimerScheduler(){
}


void TimerScheduler::addTimer(const TimerSessionPtr &timer) {
    std::lock_guard<std::mutex> guard(m_mutex);
    m_pTimers->push(timer);
    if (m_pThread == nullptr) {
        StartThread();
    }
}

void TimerScheduler::StartThread() {
    auto shared_this = shared_from_this();
	weak_protector_ = shared_this;
    m_pThread = std::make_shared<std::thread>([=](){
        while (true) {
            bool shouldExit = false;
            bool shouldSleep = false;
			auto _protector = weak_protector_.lock();
			if (!_protector)
			{
				return;
			}
            std::function<void(TimerSessionPtr)> funcToCall = nullptr;
            auto currentTime = std::chrono::high_resolution_clock::now();
            TimerSessionPtr pTimerSession = nullptr;
            {
                std::unique_lock<std::mutex> lock(shared_this->m_mutex);
                if (shared_this->m_pTimers->empty()) {
                    shouldExit = true;
                }
                else {
                    pTimerSession = shared_this->m_pTimers->top();

                    TimerSession::Result result = TimerSession::Result::Pending;
                    {
                        std::lock_guard<std::mutex> sessionGuard(pTimerSession->m_mutex);

                        auto pTimer = pTimerSession->m_pTimer.lock();

                        if (pTimer == nullptr) {
                            result = TimerSession::Result::Cancelled;
                        }
                        else {
                            std::lock_guard<std::mutex> timerGuard(pTimer->m_mutex);
                            if (pTimer->m_pCurrentSession != pTimerSession) {
                                result = TimerSession::Result::Cancelled;
                            }
                            else {
                                if (currentTime < pTimerSession->m_nextTick) {
                                    result = TimerSession::Result::Pending;
                                }
                                else {
                                    result = TimerSession::Result::Timesup;
									shared_this->m_pTimers->pop();
                                    pTimerSession->m_nextTick = currentTime + pTimer->m_interval;
                                    funcToCall = pTimer->m_func;
                                }
                            }
                        }
                    }

                    switch (result) {
                        case TimerSession::Result::Cancelled:
                            shared_this->m_pTimers->pop();
                            break;
                        case TimerSession::Result::Pending:
                            shouldSleep = true;
                            break;
                        case TimerSession::Result::Timesup:
                            shared_this->m_pTimers->push(pTimerSession);
                            break;
                    }
                }
            }

            if (shouldExit) {
                break;
            }

            if (funcToCall) {
				std::unique_lock<std::mutex> lock(shared_this->m_mutex);
                funcToCall(pTimerSession);
            }
            
            if (shouldSleep) {
                std::this_thread::sleep_for(shared_this->m_resolution);
            }
        }
    });
}

void TimerScheduler::Cleanup() {
    std::unique_lock<std::mutex> lock(m_mutex);
    if (m_pTimers) {
        while (!m_pTimers->empty()) {
            m_pTimers->pop();
        }
    }

	if (m_pThread.get()) {
		m_pThread->join();
	}
}

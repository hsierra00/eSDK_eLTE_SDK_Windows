
/**********************************************************\
 Original Author: Georg Fritzsche
 
 Created:    Nov 6, 2010
 License:    Dual license model; choose one of two:
 New BSD License
 http://www.opensource.org/licenses/bsd-license.php
 - or -
 GNU Lesser General Public License, version 2.1
 http://www.gnu.org/licenses/lgpl-2.1.html
 
 Copyright 2010 Georg Fritzsche and the Firebreath development team
 \**********************************************************/

#pragma once
#ifndef FB_H_ONESHOTMANAGER
#define FB_H_ONESHOTMANAGER

#include <map>
#include <boost/noncopyable.hpp>

#include "APITypes.h"
#include "SafeQueue.h"


namespace FB
{
    typedef void (*OneShotCallback)(void*);
    using SinkPair = std::pair<void*, OneShotCallback>;
    using SinkQueue = std::deque<SinkPair>;
    using Sinks = std::map<void*,SinkQueue*>;

    class OneShotManager : public boost::noncopyable
    {
    public:
        ~OneShotManager();
        
        void npp_register(void* instance);
        void npp_unregister(void* instance);
        
        void npp_scheduleAsyncCallback(void* instance, OneShotCallback func, void *userData);
        
        void npp_asyncCallback();
        
        static OneShotManager& getInstance();
        
    private:
        OneShotManager();
        bool npp_nextCallback(SinkPair& callback);

        mutable std::mutex m_mutex;
        Sinks m_sinks;
        void* m_helper;
        uint32_t m_shots;
    };
}

#endif


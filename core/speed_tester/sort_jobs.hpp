#pragma once

#include <thread>

#include <cstdio>
#include <cstring>
#include <cassert>

#include <functional>
#include <iostream>
#include <iomanip>
#include <limits>
#include <mutex>
#include <thread>
#include <vector>
#include <chrono>

#include "rnum_generator/generator.h"

#include "vt100.hpp"




void worker_routine(std::vector<std::function<void(void)>>& tasks, std::mutex* ticket_pool_mutex)
{
    while (true)
    {
        std::function<void(void)> task;
        {
            std::lock_guard<std::mutex> guard(*ticket_pool_mutex);

            if (tasks.empty())
            {
                return;
            }
            else
            {
                task = tasks.back();
                tasks.pop_back();
            }
        }

        task();
    }
}
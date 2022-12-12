//
// Created by ZZK on 2022/12/8.
//

#pragma once

#include <iostream>
#include <sstream>
#include <mutex>

#define terr OneWeek::thread_stream(std::cerr)
#define tout OneWeek::thread_stream(std::cout)

/*
 * Thread-safe std::ostream class
 * Usage:
 *  tout << "Hello world!" << std::endl;
 *  terr << "Hello world!" << std::endl;
 */

namespace OneWeek
{
    class thread_stream : public std::ostringstream
    {
    public:
        thread_stream(std::ostream& os) : os_(os)
        {
            std::basic_ios<char>::imbue(os.getloc());
            precision(os.precision());
            width(os.width());
            setf(std::ios::fixed, std::ios::floatfield);
        }

        ~thread_stream()
        {
            std::lock_guard<std::mutex> guard(mutex_thread_stream);
            os_ << this->str();
        }

    private:
        static std::mutex mutex_thread_stream;
        std::ostream& os_;
    };

    std::mutex thread_stream::mutex_thread_stream;
}

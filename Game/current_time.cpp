#include "./include/current_time.h"

const char * get_current_time(char * _time_buffer)
{
    auto now = std::chrono::system_clock::now();

    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::tm local_tm = *std::localtime(&in_time_t);

    std::strftime(_time_buffer, TIME_STR_LEN, "%Y-%m-%d %H:%M:%S", &local_tm);

    return _time_buffer;
}
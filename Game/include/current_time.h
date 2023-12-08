#ifndef _CURRENT_TIME_H_
#define _CURRENT_TIME_H_

#include <ctime>
#include <chrono>

const size_t TIME_STR_LEN = 20;

/**
 * 获取当前时间字符串字符串，格式：2023-12-05 13:42:32
 *
 * @param _time_buffer 传入的字符串
 * 
 * @return 经过处理后返回的字符串
*/
const char * get_current_time(char * _time_buffer);

#endif //_CURRENT_TIME_H_
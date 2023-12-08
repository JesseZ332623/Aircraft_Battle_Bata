#ifndef _GAME_H_
#define _GAME_H_

#include "./defs.h"
#include "./draw.h"
#include "./events.h"
#include "./init.h"
#include "./struct.h"
#include "./destroy.h"
#include "./stage.h"

/**
 * 用于控制帧数，来代替简陋的 SDL_Delay(16)，该函数会将帧数控制在 60 FPS 左右。
 * 
 * @param _then 从上一帧开始的刻度计时值
 * @param _remainder 上一帧的误差时间
 * 
 * @return non-return
*/
static void cap_framerate(long int *_then, float * _remainder);

#endif //_GAME_H_
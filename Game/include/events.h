#ifndef _EVENTS_H_
#define _EVENTS_H_

#include "./defs.h"
#include "./struct.h"

/**
 * 处理 按下方向键时的事件
 * 
 * @param _k_events the events of keyboard
*/
void do_keydown(SDL_KeyboardEvent *_k_events);

/**
 * 处理 松开方向键时的事件
 * 
 * @param _k_events the events of keyboard
*/
void do_keyup(SDL_KeyboardEvent *_k_events);

/*
    用来处理游戏内的事件，当前事件有：

    1. 点击 X 触发销毁窗口事件
*/
void events(void);

#endif //_EVENTS_H_
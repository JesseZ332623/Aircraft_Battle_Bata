/*
    def.h 一些常量的定义，头文件包含，以及函数原型会放在此处，如：
    窗口宽度，窗口长度等参数。
*/

#ifndef _DEFS_H_
#define _DEFS_H_

/*一些基本的 SDL 组件声明在此头文件*/
#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_net.h"

#include <iostream>
#include <cstring>

/*窗口宽度: 100 像素*/
const uint32_t SCREEN_WIDTH = 1280;

/*窗口长度: 300 像素*/
const uint32_t SCREEN_HEIGHT = 720;

/*固定延迟时间，单位（ms）*/
const long int DELAY_TIME = 16;

/*角色移动默认速度*/
const float PLAYER_DEFAULT_SPEEND = 0.5000;

/*角色子弹速度*/
const float PLAYER_BULLET_SPEED = 2.0000;

/*键位的数量*/
const uint32_t MAX_KEYBOARD_KEYS = 350;

/*按下*/
const bool PRESS_DOWN = true;

/*松开*/
const bool RELEASE = false;

#endif //_DEFS_H_
#ifndef _STRUCT_H_
#define _STRUCT_H_

#include "./defs.h"

/*
    此结构体充当游戏主循环中的逻辑和渲染函数的委托。
*/
typedef struct _Delegate
{
    void (* _logic)(void);
    void (* _draw)(void);

} Delegate;

/*
    _Application 结构体，内部有：

    SDL_Window 一个窗口类
    SDL_Renderer 一个渲染器

    delegate 逻辑和渲染函数的委托

    keyboard_state 一个布尔类型的数组，用于记录键盘上每一个键的状态（按下/放开）

    _up _down _left _right 上下左右的操控值
    fire 是否开火的操控值
*/
typedef struct _Application
{
    SDL_Window * _window;
    SDL_Renderer * _renderer;

    Delegate delegate;

    bool keyboard_state[MAX_KEYBOARD_KEYS];
} App;

/*
    一个实体（Entity）所需要的数据，内容有：

    (x, y) 实体在窗口中的位置

    (delta_x, delta_y) 实体的 △x 和 △y

    w, h 实体的宽高

    health 角色的生命值

    reload 跟踪玩家的射击能力

    _texture 图片的纹理

    _next 指向下一个 Entity 结构体的指针
*/
typedef struct _Entity
{
    float x;
    float y;
    float delta_x;
    float delta_y;
    int w;
    int h;
    int health;
    int reload;

    SDL_Texture * _texture;
    _Entity * _next;

} Entity;

typedef struct _Sence
{   
    int x;
    int y;
    SDL_Texture * _sence_texture;

} Sence;

/*
    一个实体链表的结构体，内容如下：

    1. _flight_head 飞机实体结构体的实例
    2. _flight_tail 指向飞机实体链表尾部的指针

    3. _bullet_head 子弹实体结构体的实例
    4. _bullet_tail 指向子弹实体链表尾部的指针
*/
typedef struct _Stage
{
    Entity _flight_head, *_flight_tail;
    Entity _bullet_head, * _bullet_tail;

} Stage;

#endif //_STRUCT_H_
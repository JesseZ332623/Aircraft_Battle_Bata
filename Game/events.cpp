#include "./include/events.h"
#include "./include/destroy.h"

extern App _app;

/*
    SDL_Event SDL 中的事件类
*/
SDL_Event _event;

void do_keydown(SDL_KeyboardEvent *_k_events)
{
    /*若不重复按下某个键并且按下的键在键位的数量之内*/
    if (!_k_events->repeat && _k_events->keysym.scancode < MAX_KEYBOARD_KEYS)
    {
        /*该键的状态便记为： 按下*/
        _app.keyboard_state[_k_events->keysym.scancode] = PRESS_DOWN;
    }
}

void do_keyup(SDL_KeyboardEvent *_k_events)
{
    /*若不重复松开某个键并且按下的键在键位的数量之内*/
    if (!_k_events->repeat && _k_events->keysym.scancode < MAX_KEYBOARD_KEYS)
    {
        /*该键的状态便记为： 松开*/
        _app.keyboard_state[_k_events->keysym.scancode] = RELEASE;
    }
}

void events(void)
{
    /*SDL_PollEvent 传入 SDL_Event 实例的地址在循环中不断的处理所发生的事件。*/
    while (SDL_PollEvent(&_event))
    {
        /*使用分支语句，对不同的事件做不同的处理*/
        switch (_event.type)
        {
            /*若点击窗口的 X 或者正常的退出*/
            case SDL_QUIT:
                /*释放所有资源，退出 SDL，最后退出程序*/
                destroy_resource();
                break;

            /*若按下一个键*/
            case SDL_KEYDOWN:
                do_keydown(&_event.key);
                break;

            /*若松开一个键*/
            case SDL_KEYUP:
                do_keyup(&_event.key);

            default:
                break;
        }
    }
}


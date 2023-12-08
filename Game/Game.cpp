#include "./include/Game.h"

extern App _app;

static void cap_framerate(long int *_then, float * _remainder)
{
    /*
        wait 需要等待的时间，frame_time 上一帧的实际执行时间。
    */
    long int wait, frame_time;

    /*
        DELAY_TIME 为 16 ms，1000 ms / 60 fps = 16.6667ms per fps
        再加上 _remainder 的值补上了上一帧误差的时间。
    */
    wait = DELAY_TIME + (*_remainder);

    /*
        去除整数部分，只保留小数的误差。
    */
    *_remainder -= (int)(*_remainder);

    /*
        使用 SDL_GetTicks() 可获得程序开始到当前所经过的时间。
        再用这个值减去上一帧开始的时间，就可得出一帧画面实际执行的时间 frame_time。
    */
    frame_time = SDL_GetTicks() - *_then;

    /*
        计算本帧的执行时间。若上一帧执行的快，
        实际帧时间 frame_time 会较小，而 wait 会比较大，反之亦然。
    */
    wait -= frame_time;

    /*限制等待时间在 1 ms 以上，避免等待时间为负值*/
    if (wait > 1) { wait = 1; }

    /*线程暂停 wait ms*/
    SDL_Delay(wait);

    /*
        更新 从上一帧开始的刻度计时值 和 上一帧的误差时间，继续下一帧的运算。
    */
    *_remainder += 0.667;

    *_then = SDL_GetTicks();
}

int main(int argc, char *argv[])
{
    long int then;
    float remainder = 0;

    /*初始化应用实例*/
    std::memset(&_app, 0, sizeof(App));

    /*初始化 SDL*/
    init_SDL();

    /*初始化 所有实体的链表实例*/
    init_stage();

    /*获取程序开始到现在的时间*/
    then = SDL_GetTicks();

    while (true)
    {
        /*准备渲染*/
        prepare_scence();

        events();

        _app.delegate._logic();
        _app.delegate._draw();

        present_scence();

        cap_framerate(&then, &remainder);
    }

    return EXIT_SUCCESS;
}

#include "./include/init.h"

extern App _app;

void init_SDL(void)
{
    int renderer_flags, window_flags;
    int image_flags, audio_flags;
    
    /*渲染器标志位：启动硬件加速*/
    renderer_flags = SDL_RENDERER_ACCELERATED;

    /*图片的渲染标志位：渲染 .png 和 .jpg 文件*/
    image_flags = IMG_INIT_JPG | IMG_INIT_PNG;

    audio_flags = MIX_INIT_FLAC | MIX_INIT_MP3 | MIX_INIT_MID;

    /*窗口标志位：SDL_WINDOW_RESIZABLE 可自由调整大小，当前该标志位不适用*/
    //window_flags = SDL_WINDOW_RESIZABLE;

     /*窗口标志位：0 默认*/
    window_flags = 0;

    /*初始化 SDL 组件*/
    if ((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO)) < 0)
    {
        SDL_Log("Couldn't initalize SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /*初始化 SDL_Image 组件*/
    if(IMG_Init(image_flags) != image_flags)
    {
        SDL_Log("Init IMG Kit Failed: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if (TTF_Init() < 0)
    {
        SDL_Log("Init TTF Kit Failed: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    if (Mix_Init(audio_flags) != audio_flags)
    {
        SDL_Log("Init Mix Kit Failed: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /*
        创建窗口：
        窗口名："New Window"
        窗口相对屏幕的位置 x：SDL_WINDOWPOS_CENTERED （位于屏幕的正中央）
        窗口相对屏幕的位置 y：SDL_WINDOWPOS_CENTERED 
        窗口宽 w：SCREEN_WIDTH
        窗口长 h: SCREEN_HEIGHT
        窗口标志位：0
    */
    _app._window = SDL_CreateWindow("Aircraft Battle", 
                                    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    SCREEN_WIDTH, SCREEN_HEIGHT, window_flags);

    if (!_app._window)
    {
        SDL_Log("Failed to open %zd * %zd window: %s\n", SCREEN_HEIGHT, SCREEN_WIDTH, SDL_GetError());
        exit(EXIT_FAILURE);
    }

    /*
        SDL_SetHint() 用来设置渲染的缩放质量过滤器
        设置渲染算法，将：
        SDL_HINT_RENDER_SCALE_QUALITY （渲染质量相关的标志位）指定为 "linear" 线性的
    */
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    /*
        创建渲染器，需要传入：
        _app._window 指定的窗口
        -1 要初始化的呈现驱动程序的索引，该参数表示初始化支持所请求标志的第一个驱动程序
        renderer_flags 渲染标志位
    */
    _app._renderer = SDL_CreateRenderer(_app._window, -1, renderer_flags);

    if (!_app._renderer)
    {
        SDL_Log("Failed to create renderer: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}
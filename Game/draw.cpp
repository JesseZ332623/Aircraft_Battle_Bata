#include "./include/draw.h"

extern App _app;
extern Entity * _player;
extern Stage _stage;
extern Sence _sence;

static char _time_buffer[TIME_STR_LEN];

void prepare_scence(void)
{
    /*
        将指定的颜色信息提交，颜色信息由以下几个值组成：
        1.红色 R
        2.绿色 G
        3.蓝色 B
        4.Alpha 通道（透明度）A
    */
    SDL_SetRenderDrawColor(_app._renderer, 96, 0, 255, 255);

    /*刷新渲染器*/
    SDL_RenderClear(_app._renderer);
}

SDL_Texture * load_texture(const char * _filename)
{
    /*新建一个空纹理*/
    SDL_Texture * _texture;

    /*把一张图片的纹理加载到渲染器*/
    _texture = IMG_LoadTexture(_app._renderer, _filename);

    /*
        每加载一张图片，都会输出一条日志：格式为 Loading: _filename

        其中，这个函数的前两个参数有很多选项，具体如下所示：

        参数 1：确定日志来源：
            SDL_LOG_CATEGORY_APPLICATION 应用程序本身的日志
            SDL_LOG_CATEGORY_ERROR       错误信息
            SDL_LOG_CATEGORY_ASSERT      断言失败信息
            SDL_LOG_CATEGORY_SYSTEM      底层系统库日志

        参数 2：日志的优先级，从上到下，级别越高的信息越重要
            SDL_LOG_PRIORITY_VERBOSE     详细日志
            SDL_LOG_PRIORITY_DEBUG       调试信息
            SDL_LOG_PRIORITY_INFO        普通信息
            SDL_LOG_PRIORITY_WARN        警告
            SDL_LOG_PRIORITY_ERROR       错误
    */
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "%s Loading: %s\n", 
                   get_current_time(_time_buffer), _filename);

    /*返回这个纹理*/
    return _texture;
}

void bilt(SDL_Texture * _texture, int x, int y)
{
    /*
        一个矩形，从左上角的原点开始绘制，
        用来确定纹理的绘制的大小(w, h) 和 位置(x, y)
    */
    SDL_Rect _dest;

    _dest.x = x;
    _dest.y = y;

    /*
        查询一个纹理的信息，传入一个纹理，可以获得这个纹理的信息如下：
            1. 颜色信息
            2. 像素数据信息
            3. 纹理的宽
            4. 纹理的高

        当前我们只需要取得纹理的宽高，因此第 2，3个参数为空
    */
    SDL_QueryTexture(_texture, nullptr, nullptr, &_dest.w, &_dest.h);

    /*
        将要渲染的纹理以及相关信息提交给 GPU，该函数有四个参数：
            1. 渲染器
            2. 纹理
            3. 在纹理中渲染的矩形区域（一个 SDL_Rect 类型，若为 nullptr 代表渲染整个纹理）
            4. 纹理相对于窗口中的大小（一个 SDL_Rect 类型，若为 nullptr 代表填满整个窗口）
    */
    SDL_RenderCopy(_app._renderer, _texture, nullptr, &_dest);
}

static void draw_sence(void)
{
    bilt(_sence._sence_texture, _sence.x, _sence.y);
}

/*渲染玩家*/
static void draw_player(void)
{
    bilt(_player->_texture, _player->x, _player->y);
}

/*渲染子弹*/
static void draw_bullets(void)
{
    Entity * _b;

    for (_b = _stage._bullet_head._next; _b != nullptr; _b = _b->_next)
    {
        bilt(_b->_texture, _b->x, _b->y);
    }
}

/*渲染敌机*/
static void draw_fighters(void)
{
    Entity * enemy;

    for (enemy = _stage._flight_head._next; enemy != nullptr; enemy = enemy->_next)
    {
        bilt(enemy->_texture, enemy->x, enemy->y);
    }
}

/*所有美术资源的渲染*/
void draw(void)
{
    draw_sence();
    draw_player();
    draw_fighters();
    draw_bullets();
}

void present_scence(void)
{
    SDL_RenderPresent(_app._renderer);
}
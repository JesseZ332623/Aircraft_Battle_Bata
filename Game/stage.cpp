#include "./include/stage.h"

extern App _app;
extern Stage _stage;
extern Entity * _player;
extern Sence _sence;

/*一个临时的子弹（Bullet）纹理*/
static SDL_Texture * bullet_texture;

/*一个临时的，向左移动的敌机（Enemy）纹理*/
static SDL_Texture * enemy_texture_left;

/*一个临时的，向下移动的敌机（Enemy）纹理*/
static SDL_Texture * enemy_texture_down;

/*敌机再生计时器初始化为*/ 
static int enemy_spantimer;

/*初始化实体链表实例*/
void init_stage(void)
{
    /*
        将 logic 和 draw 函数的地址赋值给 _app 结构体实例中，
        这样 _app 就可以自己调用这两个外部的函数（这已经有点像 class 了）
    */
    _app.delegate._logic = logic;
    _app.delegate._draw = draw;

    /*初始化 _stage*/
    std::memset(&_stage, 0, sizeof(Stage));

    /*设置链表的首尾，初始化阶段，只需首尾相接即可*/
    _stage._flight_tail = &_stage._flight_head;
    _stage._bullet_tail = &_stage._bullet_head;
    
    /*初始化场景*/
    init_sence();

    /*初始化玩家*/
    init_player();

    /*加载子弹的纹理，暂存*/
    bullet_texture = load_texture("./img/bullet_2.png");

    /*加载敌机（向左）的纹理，暂存*/
    enemy_texture_left = load_texture("./img/enemy_plane_left.png");

    enemy_texture_down = load_texture("./img/enemy_plane_down.png");

    /*敌机再生计时器初始化为 0*/
    enemy_spantimer = 0;
}

/*初始化场景*/
static void init_sence(void)
{
    /*场景肯定是要铺满整个窗口的，因此从窗口的原点（0，0）开始渲染*/
    _sence.x = _sence.y = 0;

    _sence._sence_texture = load_texture("./img/sence.png");
}

/*初始化玩家*/
static void init_player(void)
{
    /*为一个新的玩家实体申请内存并初始化*/
    _player = (Entity *)malloc(sizeof(Entity));
    std::memset(_player, 0, sizeof(Entity));

    /*将新创建的实体链接到链表尾部*/
    _stage._flight_tail->_next = _player;
    _stage._flight_tail = _player;

    /*设定玩家的出生点为直角坐标（100，100）*/
    _player->x = 100;
    _player->y = 100;

    /*加载玩家飞机的纹理*/
    _player->_texture = load_texture("./img/plane.png");

    /*查询纹理的宽高并赋值*/
    SDL_QueryTexture(_player->_texture, nullptr, nullptr, &_player->w, &_player->h);
}

/*设置玩家的行为*/
static void do_player(void)
{
    /*将玩家的移速设为 0*/
    _player->delta_x = _player->delta_y = 0;

    /*控制玩家可以多快的开火*/
    if (_player->reload > 0) { --_player->reload; }

    /*当玩家按下方向键时，更新玩家的位置*/
    if (_app.keyboard_state[SDL_SCANCODE_UP]) { _player->delta_y = -PLAYER_DEFAULT_SPEEND; }
    if (_app.keyboard_state[SDL_SCANCODE_DOWN]) { _player->delta_y = PLAYER_DEFAULT_SPEEND; }
    if (_app.keyboard_state[SDL_SCANCODE_LEFT]) { _player->delta_x = -PLAYER_DEFAULT_SPEEND; }
    if (_app.keyboard_state[SDL_SCANCODE_RIGHT]) { _player->delta_x = PLAYER_DEFAULT_SPEEND; }

    /*当玩家按下 W A S D 键时，也可以移动*/
    if (_app.keyboard_state[SDL_SCANCODE_W]) { _player->delta_y = -PLAYER_DEFAULT_SPEEND; }
    if (_app.keyboard_state[SDL_SCANCODE_S]) { _player->delta_y = PLAYER_DEFAULT_SPEEND; }
    if (_app.keyboard_state[SDL_SCANCODE_A]) { _player->delta_x = -PLAYER_DEFAULT_SPEEND; }
    if (_app.keyboard_state[SDL_SCANCODE_D]) { _player->delta_x = PLAYER_DEFAULT_SPEEND; }


    /*当玩家按下开火键 且 装填量为 0 之时，开火*/
    if (_app.keyboard_state[SDL_SCANCODE_LCTRL] && !_player->reload) { fire_bullet(); }

    _player->x += _player->delta_x;
    _player->y += _player->delta_y;
}

/*设置除玩家外飞机的行为*/
static void do_fighters(void)
{
    Entity *enemy, *prev;

    prev = &_stage._flight_head;

    for (enemy = _stage._flight_head._next; enemy != nullptr; enemy = enemy->_next)
    {
        enemy->x += enemy->delta_x;
        enemy->y += enemy->delta_y;

        if (enemy != _player && enemy->x < -enemy->w)
        {
            if (enemy == _stage._flight_tail)
            {
                _stage._bullet_tail = prev;
            }

            prev->_next = enemy->_next;
            free(enemy);
            enemy = prev;
        }

        prev = enemy;
    }
}

static void spawn_enemies(void)
{
    Entity *enemy;

    /*在敌机数量小于等于 0 之时生产新的敌机*/
    if (--enemy_spantimer <= 0)
    {
        enemy = (Entity *)malloc(sizeof(Entity));
        std::memset(enemy, 0, sizeof(Entity));

        _stage._flight_tail->_next = enemy;
        _stage._flight_tail = enemy;

        /*
            敌机在窗口的右边缘生成，生成坐标为：
            (SCREEN_WIDTH，[0, SCREEN_HEIGHT))
        */
        enemy->x = SCREEN_WIDTH;
        enemy->y = std::rand() % SCREEN_HEIGHT; 

        /*将暂存的纹理赋值*/
        enemy->_texture = enemy_texture_left;

        /*查询敌机纹理的宽高并赋值*/
        SDL_QueryTexture(enemy_texture_left, nullptr, nullptr, &enemy->w, &enemy->h);

        /*设置敌机的移速，区间为 [-1, -2]*/
        enemy->delta_x = -(0.5 + (std::rand() % 2));

        /*设置敌机的刷新频率，区间为 [160, 279] ms*/
        enemy_spantimer = 160 + (std::rand() % 220);
    }
}

/*设置开火的行为*/
static void fire_bullet(void)
{
    /*为一个新的子弹实体申请内存并初始化*/
    Entity * bullet = (Entity *)malloc(sizeof(Entity));
    std::memset(bullet, 0, sizeof(Entity));

    /*将新创建的实体链接到链表尾部*/
    _stage._bullet_tail->_next = bullet;
    _stage._bullet_tail = bullet;

    /*将子弹的位置更新到玩家的位置*/
    bullet->x = _player->x;
    bullet->y = _player->y;

    /*
        设置玩家的子弹速度，
        由于子弹只需要沿 X 轴平移，因此 delta_y 为 0
    */
    bullet->delta_x = PLAYER_BULLET_SPEED;
    bullet->delta_y = 0;

    /*设置子弹的生命值为 1*/
    bullet->health = 1;
    
    /*设置子弹的纹理*/
    bullet->_texture = bullet_texture;

    /*查询子弹纹理的宽高并赋值*/
    SDL_QueryTexture(bullet->_texture, nullptr, nullptr, &bullet->w, &bullet->h);

    /*子弹的位置必须更新在玩家纹理中间*/
    bullet->y += (_player->h / 2) - (bullet->h / 2);

    /*将 reload 设为 60，意味着经过 60 帧（约 1.000002 秒）后才能再次开火*/
    _player->reload = 60;
}

/*设置子弹的行为*/
static void do_bullets(void)
{
    Entity * bullet, * prev;

    /*声明一个中间变量指向 _bullet 链表头*/
    prev = &_stage._bullet_head;

    /*遍历 _bullet 链表*/
    for (bullet = _stage._bullet_head._next; bullet != nullptr; bullet = bullet->_next)
    {
        bullet->x += bullet->delta_x;
        bullet->y += bullet->delta_y;

        /*如果子弹移出了屏幕之外*/
        if (bullet->x > SCREEN_WIDTH)
        {
            /*若变量到了链表尾部*/
            if (bullet == _stage._bullet_tail)
            {
                /*重新指向链表头*/
                _stage._bullet_tail = prev;
            }
            /*指向下一个节点*/
            prev->_next = bullet->_next;

            /*删除原节点*/
            free(bullet);
            bullet = prev;
        }

        prev = bullet;
    }
}

/*逻辑控制*/
static void logic(void)
{
    do_player();
    do_fighters();
    do_bullets();
    spawn_enemies();
}
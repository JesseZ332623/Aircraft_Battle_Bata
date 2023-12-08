#ifndef _STAGE_H_
#define _STAGE_H_

#include "./struct.h"
#include "./draw.h"

/*初始化实体链表实例*/
void init_stage(void);

/*初始化场景*/
static void init_sence(void);

/*初始化玩家*/
static void init_player(void);

/*设置玩家的行为*/
static void do_player(void);

/*设置除玩家外飞机的行为*/
static void do_fighters(void);

/*设置敌机的生产规则*/
static void spawn_enemies(void);

/*设置发射子弹的行为*/
static void fire_bullet(void);

/*设置子弹的行为*/
static void do_bullets(void);

/*逻辑控制*/
static void logic(void);

#endif //_STAGE_H_
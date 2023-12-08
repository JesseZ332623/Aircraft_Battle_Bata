#ifndef _DESTROY_H_
#define _DESTROY_H_

#include "./struct.h"

/*释放链表*/
void free_link_list(Entity * _head);

/*
    在游戏结束后销毁所有资源，当前需要销毁的资源有：
    1. 窗口 1 个
    2. 渲染器 1 个
    3. 玩家飞机纹理
    4. 玩家子弹纹理
    5. 场景纹理
    6. 各种 SDL 组件
*/
void destroy_resource(void);


#endif //_DESTROY_H_
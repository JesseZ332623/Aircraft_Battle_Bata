#ifndef _DRAW_H_
#define _DRAW_H_

#include "./defs.h"
#include "./struct.h"
#include "./current_time.h"

/*
    准备渲染场景，将需要的渲染纹理提交给 GPU
*/
void prepare_scence(void);

/**
 * 加载一张图片的纹理
 * 
 * @param _filename the path of image file
 * 
 * @return a texture of this image
*/
SDL_Texture * load_texture(const char * _filename);

/**
 * 确定纹理的位置并准备渲染
 * 
 * @param _texture a texture of image
 * @param x position x
 * @param y position y
*/
void bilt(SDL_Texture * _texture, int x, int y);

/*渲染场景*/
static void draw_sence(void);

/*渲染玩家*/
static void draw_player(void);

/*渲染子弹*/
static void draw_bullets(void);

/*渲染敌机*/
static void draw_fighters(void);

/*所有美术资源的渲染*/
void draw(void);

/*
    渲染，将纹理渲染至屏幕
*/
void present_scence(void);

#endif //_DRAW_H_
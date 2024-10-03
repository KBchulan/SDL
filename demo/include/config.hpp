#ifndef _CONFIG_H
#define _CONFIG_H

// SDL2 头文件
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_gfxPrimitives.h>

// c++ 头文件
#include <iostream>
#include <fstream>
#include <sstream>

// cjson 头文件
#include <cjson/cJSON.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define FPS 144

bool running = true;

#endif // _CONFIG_H 
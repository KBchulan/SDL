/*
本文件为配置文件,包括一些头文件和基础属性，防止全局变量满天飞
user: whx
time: 2024.10.2
*/
#ifndef CONFIG_HPP
#define CONFIG_HPP

// SDL头文件
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL2_gfxPrimitives.h>

// C++头文件
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

// cJSON头文件
#include <cjson/cJSON.h>

// 窗口属性
#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 72

// 游戏基础属性
inline bool running = true;
const int FPS = 144;

#endif // CONFIG_HPP
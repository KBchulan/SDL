#ifndef BEGIN_ANIMATION_HPP
#define BEGIN_ANIMATION_HPP

#include <SDL2/SDL.h>
#include <functional>
#include <SDL2/SDL_image.h>

class BeginAnimation
{
public:
    void on_renderer(SDL_Renderer *renderer);

public:
    BeginAnimation() = default;
    BeginAnimation(SDL_Renderer *renderer,double r,double g,double b);
    ~BeginAnimation();

private:
    SDL_Texture *begin_animation = nullptr;
    SDL_Rect dst;
    double rgb[3];
};

#endif // BEGIN_ANIMATION_HPP
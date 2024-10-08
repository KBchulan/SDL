#include "../include/begin_animation.hpp"

BeginAnimation::BeginAnimation(SDL_Renderer *renderer, double r, double g, double b)
{
    begin_animation = IMG_LoadTexture(renderer, "../resources/begin_animation.png");
    rgb[0] = r, rgb[1] = g, rgb[2] = b;
    SDL_QueryTexture(begin_animation, NULL, NULL, &dst.w, &dst.h);
    while (dst.w > 640 || dst.h > 360)
    {
        dst.w /= 1.5, dst.h /= 1.5;
    }
    dst.x = (1280 - dst.w) / 2;
    dst.y = (720 - dst.h) / 2;
    SDL_SetTextureBlendMode(begin_animation, SDL_BLENDMODE_BLEND);
}

void BeginAnimation::on_renderer(SDL_Renderer *renderer)
{
    for (double alpha = 0; alpha <= 255; alpha += 15)
    {
        SDL_SetRenderDrawColor(renderer, rgb[0] * alpha, rgb[1] * alpha, rgb[2] * alpha, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, begin_animation, NULL, &dst);
        SDL_RenderPresent(renderer);
        SDL_Delay(25);
    }
    SDL_Delay(1500);
    for (double alpha = 255; alpha >= 0; alpha -= 15)
    {
        SDL_SetRenderDrawColor(renderer, rgb[0] * alpha, rgb[1] * alpha, rgb[2] * alpha, 255);
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, begin_animation, NULL, &dst);
        SDL_RenderPresent(renderer);
        SDL_Delay(25);
    }
}

BeginAnimation::~BeginAnimation()
{
    SDL_DestroyTexture(begin_animation);
}
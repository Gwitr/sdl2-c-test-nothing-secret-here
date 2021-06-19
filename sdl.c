#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "graphics.h"

void *GFX_context = NULL;

void LOOP_Start();
void LOOP_Tick();
void LOOP_OnError(const char *s);

void *GFX_LoadBitmap(const char *location) {
    char *path = calloc(1 + strlen(location) + 1, sizeof(char));
    strcpy(path + 1, location);
    path[0] = '.';
    SDL_Surface *surf = IMG_Load(path);
    if (surf == NULL) {
        LOOP_OnError(SDL_GetError());
        return NULL;
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface((SDL_Renderer *) GFX_context, surf);
    if (tex == NULL) {
        LOOP_OnError(SDL_GetError());
        return NULL;
    }
    SDL_FreeSurface(surf);
    free(path);
    return (void *) tex;
}

void GFX_FreeBitmap(void *sprite) {
    SDL_DestroyTexture((SDL_Texture *) sprite);
}

void GFX_GetBitmapSize(void *sprite, int *w, int *h) {
    uint32_t format;
    int access;
    SDL_QueryTexture((SDL_Texture *) sprite, &format, &access, w, h);
}

void GFX_DrawBitmap(void *sprite, int srcx, int srcy, int srcw, int srch, int dstx, int dsty) {
    SDL_Rect srcrect = {srcx, srcy, srcw, srch};
    SDL_Rect dstrect = {dstx, dsty, srcw, srch};
    SDL_RenderCopy((SDL_Renderer *) GFX_context, (SDL_Texture *) sprite, &srcrect, &dstrect);
}

int SDL_main(int argc, char **argv) {
    SDL_Window *window;

    window = SDL_CreateWindow("", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    if (window == NULL) {
        printf("Could not create SDL window\n");
        return 1;
    }

    GFX_context = SDL_CreateRenderer(window, -1, 0);
    if (GFX_context == NULL) {
        printf("Could not create SDL renderer\n");
        return 1;
    }

    IMG_Init(IMG_INIT_PNG);

    LOOP_Start();

    int running = 1;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
            case SDL_QUIT:
                running = 0;
                break;
            }
        }

        LOOP_Tick();

        SDL_RenderPresent((SDL_Renderer *) GFX_context);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer((SDL_Renderer *) GFX_context);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    return 0;
}

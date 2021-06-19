#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

spriteid niko_sprite;

void LOOP_Start() {
    niko_sprite = SPR_CreateSprite("/images/square.png", 0, 0, 48, 64, 10, 10, 0);
    SPR_CreateSprite("/images/square.png", 0, 0, 48, 64, 20, 20, 1);
}

void LOOP_Tick() {
    SPR_DrawAll();

    if (SPR_sprites[niko_sprite].z == 0)
        SPR_sprites[niko_sprite].z = 2;
    else
        SPR_sprites[niko_sprite].z = 0;
    SPR_UpdateSpriteOrder();
}

void LOOP_OnError(const char *s) {
    printf("%s", s);
    abort();
}

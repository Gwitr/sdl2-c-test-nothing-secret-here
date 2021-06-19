#include "graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

Sprite SPR_sprites[MAX_SPRITES] = { 0 };
Sprite SPR_sprites_sorted[MAX_SPRITES] = { 0 };

int _sprite_zsort(const void *a, const void *b) {
    if (((const Sprite*)a)->bitmap == NULL)
        return -1;
    return ((const Sprite*)a)->z - ((const Sprite*)b)->z;
}

static uint8_t sprite_order_to_update = 0;
void SPR_UpdateSpriteOrder() {
    sprite_order_to_update = 1;
}
spriteid SPR_CreateSprite(const char *path, uint16_t srcx, uint16_t srcy, uint8_t srcw, uint8_t srch, int16_t x, int16_t y, int16_t z) {
    Bitmap bmp = GFX_LoadBitmap(path);
    Sprite spr = {.srcx = srcx, .srcy = srcy, .srcw = srcw, .srch = srch, .x = x, .y = y, .z = z, .bitmap = bmp};
    for (int i = 0; i < MAX_SPRITES; i++) {
        if (SPR_sprites[i].bitmap == NULL) {
            SPR_sprites[i] = spr;
            SPR_UpdateSpriteOrder();
            return i;
        }
    }
    SPR_UpdateSpriteOrder();
    return SPRITEID_NONE;
}
void SPR_DestroySprite(spriteid sprite) {
    Sprite empty = {0, 0, 0, 0, 0, 0, 0, NULL};
    SPR_sprites[sprite] = empty;
    SPR_UpdateSpriteOrder();
}
void SPR_DrawAll() {
    for (int i = 0; i < MAX_SPRITES; i++)
        SPR_sprites_sorted[i] = SPR_sprites[i];
    qsort(SPR_sprites_sorted, MAX_SPRITES, sizeof(Sprite), _sprite_zsort);
    sprite_order_to_update = 0;

    for (int i = 0; i < MAX_SPRITES; i++) {
        if (SPR_sprites_sorted[i].bitmap != NULL) {
            GFX_DrawBitmap(SPR_sprites_sorted[i].bitmap,
                           SPR_sprites_sorted[i].srcx, SPR_sprites_sorted[i].srcy,
                           SPR_sprites_sorted[i].srcw, SPR_sprites_sorted[i].srch,
                           SPR_sprites_sorted[i].x, SPR_sprites_sorted[i].y);
        }
    }
}
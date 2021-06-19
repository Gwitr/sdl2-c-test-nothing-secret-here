#if !defined(GRAPHICS_H)
#define GRAPHICS_H

#include <stdint.h>

#define MAX_SPRITES 128
#define SPRITEID_NONE ((spriteid)-1)

typedef void *Bitmap;
typedef uint16_t spriteid;

typedef struct {
    uint16_t srcx, srcy;
    uint8_t srcw, srch;
    int16_t x, y, z;
    void *bitmap;
} Sprite;

extern void *GFX_context;
extern Sprite SPR_sprites[MAX_SPRITES];
extern Sprite SPR_sprites_sorted[MAX_SPRITES];

void *GFX_GetContext();
void *GFX_LoadBitmap(const char *location);
void GFX_FreeBitmap(void *sprite);
void GFX_GetBitmapSize(void *sprite, int *w, int *h);
void GFX_DrawBitmap(void *sprite, int srcx, int srcy, int srcw, int srch, int dstx, int dsty);

void SPR_UpdateSpriteOrder();
spriteid SPR_CreateSprite(const char *path, uint16_t srcx, uint16_t srcy, uint8_t srcw, uint8_t srch, int16_t x, int16_t y, int16_t z);
void SPR_DestroySprite(spriteid sprite);
void SPR_DrawAll();

#endif // GRAPHICS_H
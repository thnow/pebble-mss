#include "health_bitmap.h"

static unsigned health_bitmap_palette_size(GBitmapFormat format) {
  switch (format) {
    case GBitmapFormat1BitPalette:
      return 2;
    case GBitmapFormat2BitPalette:
      return 4;
    case GBitmapFormat4BitPalette:
      return 16;
    default:
      return 0;
  }
}

GBitmap *health_bitmap_load(uint32_t resource_id) {
  GBitmap *bitmap = gbitmap_create_with_resource(resource_id);
  if (!bitmap) {
    return NULL;
  }

  if (!health_bitmap_palette_size(gbitmap_get_format(bitmap))) {
    if (gbitmap_get_format(bitmap) == GBitmapFormat1Bit) {
      GBitmap *palettized = gbitmap_create_palettized_from_1bit(bitmap);
      gbitmap_destroy(bitmap);
      bitmap = palettized;
    }
  }

  return bitmap;
}

void health_bitmap_set_icon_color(GBitmap *bitmap, GColor color) {
  if (!bitmap) {
    return;
  }

  unsigned palette_size = health_bitmap_palette_size(gbitmap_get_format(bitmap));
  if (!palette_size) {
    return;
  }

  GColor *palette = gbitmap_get_palette(bitmap);
  if (!palette) {
    return;
  }

  for (unsigned i = 0; i < palette_size; i++) {
    if (!gcolor_equal(palette[i], GColorClear)) {
      palette[i] = color;
    }
  }
}

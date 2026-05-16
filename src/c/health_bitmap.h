#pragma once

#include <pebble.h>

GBitmap *health_bitmap_load(uint32_t resource_id);
void health_bitmap_set_icon_color(GBitmap *bitmap, GColor color);

#pragma once

#define UTIL_H

typedef struct {
    f32 x;
    f32 y;
} v2;

typedef struct {
    i32 x;
    i32 y;
} vi2;

f32 lerp(f32 curr, f32 target, f32 rate);
f64 time_in_seconds();

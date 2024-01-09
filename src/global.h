#pragma once

#include "base/base_common.h"
#include "base/base_arena.h"

#include "gfx/render.h"
#include "gfx/draw.h"
#include "input.h"

#define WIDTH 1024
#define HEIGHT 640

typedef struct Global Global;
struct Global
{
  Input input;
  D_Resources resources;
  D_Renderer renderer;
};

Vec2F screen_to_world(Vec2F pos);

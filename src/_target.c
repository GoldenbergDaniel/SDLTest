#ifdef _WIN32
#include "glad/glad.c"
#undef near
#undef far
#endif

#include "base/base_os.c"
#include "base/base_arena.c"
#include "base/base_string.c"
#include "base/base_math.c"
#include "base/base_random.c"
#include "render/render.c"
#include "phys/phys.c"
#include "draw.c"
#include "input.c"
#include "entity.c"
#include "game.c"
#include "global.c"
#include "main.c"

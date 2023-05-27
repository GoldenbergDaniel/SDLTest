#define PLAYER_H

typedef struct 
{
    u16 width;
    u16 height;
    SDL_Color color;
    v2 pos;
    v2 vel;
    v2 dir;
    f32 speed;
} Player;

Player create_player(u16 width, u16 height, SDL_Color color);
void init_player(Player *object);
void update_player(Player *object, f64 t, f64 dt);
void draw_player(Player *object, SDL_Renderer *renderer);
#pragma once

#include "base/base_common.h"
#include "base/base_arena.h"
#include "base/base_math.h"

#include "phys/phys.h"

typedef struct Game Game;

typedef struct Entity Entity;
typedef struct EntityRef EntityRef;
typedef struct EntityList EntityList;
typedef struct Timer Timer;

typedef enum EntityType
{
  EntityType_Nil,
  EntityType_Player,
  EntityType_EnemyShip,
  EntityType_Laser,
  EntityType_Wall,
  EntityType_DebugLine,
} EntityType;

typedef enum EntityProp
{
  EntityProp_Controlled = 1 << 0,
  EntityProp_Targetting = 1 << 1,
  EntityProp_Movable = 1 << 2,
  EntityProp_Attacker = 1 << 3,
  EntityProp_Killable = 1 << 4,
  EntityProp_Projectile = 1 << 5,
  EntityProp_Collides = 1 << 6,
  EntityProp_Rendered = 1 << 7,
} EntityProp;

struct Timer
{
  f64 max_duration;
  f64 curr_duration;
  bool should_tick;
  bool is_ticking;
  bool timeout;
  bool should_loop;
  bool start_at_zero;
};

struct EntityRef
{
  Entity *ptr;
  u64 id;
};

struct Entity
{
  Entity *next;
  Entity *next_free;
  Entity *first_child;
  Entity *last_child;
  Entity *next_child;
  u8 child_count;

  EntityRef parent;

  u64 id;
  EntityType type;
  b64 props;
  bool is_active;
  bool is_visible;

  Vec2F pos;
  Vec2F local_pos;
  f32 rot;
  f32 local_rot;
  Vec2F scale;
  Vec2F local_scale;
  f32 width;
  f32 height;
  Mat3x3F xform;
  Mat3x3F model;
  Vec2F pos_offset;
  Vec2F vel;
  Vec2F dir;
  Vec2F input_dir;
  
  Vec4F color;
  u16 z_index;
  f32 speed;
  i8 curr_health;

  Collider2D col;
  u8 col_layer;
  b8 col_mask;

  bool has_target;
  Vec2F target_pos;
  f32 target_angle;
  u16 view_dist;

  Timer timers[3];
};

struct EntityList
{
  Entity *head;
  Entity *tail;
  Entity *first_free;
  u16 count;
};

#define PLAYER_PROPS EntityProp_Rendered | EntityProp_Controlled | EntityProp_Movable \
  | EntityProp_Attacker | EntityProp_Collides
#define ENEMY_PROPS EntityProp_Rendered | EntityProp_Targetting | EntityProp_Movable \
  | EntityProp_Attacker
#define LASER_PROPS EntityProp_Rendered | EntityProp_Movable | EntityProp_Projectile

#define TIMER_COMBAT 0
#define TIMER_HEALTH 1
#define TIMER_KILL 2

#define PLAYER_HEALTH 3
#define PLAYER_SPEED 220.0f
#define PLAYER_ACC 1.5f
#define PLAYER_FRIC 1.5f

// @InitEntity =================================================================================

void init_entity(Entity *entity, EntityType type);
void clear_entity(Entity *entity);

// @UpdateEntity ===============================================================================

void update_entity_collider(Entity *entity);
void update_entity_xform(Game *game, Entity *entity);
void update_controlled_entity_movement(Game *game, Entity *entity);
void update_targetting_entity_movement(Game *game, Entity *entity);
void update_projectile_entity_movement(Game *game, Entity *entity);
void update_controlled_entity_combat(Game *game, Entity *entity);
void update_targetting_entity_combat(Game *game, Entity *entity);

// @SetEntity ==================================================================================

void set_entity_size(Entity *entity, f32 width, f32 height);
void set_entity_scale(Entity *entity, Vec2F scale);
void set_entity_origin(Entity *entity, Vec2I origin);
void set_entity_target(Entity *entity, EntityRef target);

// @OtherEntity ================================================================================

bool entity_is_valid(Entity *entity);
void resolve_entity_collision(Entity *a, Entity *b);
void wrap_entity_at_edges(Entity *entity);
void damage_entity(Entity *entity, i8 damage);

// @EntityRef ==================================================================================

EntityRef ref_from_entity(Entity *entity);
Entity *entity_from_ref(EntityRef ref);

// @EntityList =================================================================================

Entity *create_entity(Game *game);
void destroy_entity(Game *game, Entity *entity);
Entity *get_entity_of_id(Game *game, u64 id);
Entity *get_nearest_entity_of_type(Game *game, Vec2F pos, EntityType type);

// @EntityTree =================================================================================

void set_entity_parent(Entity *entity, Entity *parent);
void add_entity_child(Entity *entity, Entity *child);
void remove_entity_child(Entity *entity, u64 id);
Entity *get_entity_child_at_index(Entity *entity, u8 index);
Entity *get_entity_child_of_id(Entity *entity, u64 id);
Entity *get_entity_child_of_type(Entity *entity, EntityType type);

#include "core_game_settings.h"

static uint16_t planet_radius = 47;
uint16_t get_planet_radius() {return planet_radius;}
static float planet_gravity = 4000000;
float get_planet_gravity() {return planet_gravity;}
void  set_planet_gravity(float g) {planet_gravity = g;}
////////////////////////////////////////
static float projectile_shooting_speed = 100;
float get_projectile_shooting_speed() {return projectile_shooting_speed;}
void  set_projectile_shooting_speed(float speed) {projectile_shooting_speed = speed;}
static uint8_t projectile_shooting_cooldown = 10;
uint8_t get_projectile_shooting_cooldown() {return projectile_shooting_cooldown;}
void    set_projectile_shooting_cooldown(uint8_t cooldown) {projectile_shooting_cooldown = cooldown;}
static uint32_t projectile_color = -1;
uint32_t get_projectile_color() {return projectile_color;}
void     set_projectile_color(uint32_t color) {projectile_color = color;}
////////////////////////////////////////
static uint32_t player1_color = -1;
uint32_t get_player1_color() {return player1_color;}
void     set_player1_color(uint32_t color) {player1_color = color;}
static uint32_t player2_color = -1;
uint32_t get_player2_color() {return player2_color;}
void     set_player2_color(uint32_t color) {player2_color = color;}
static float player_size = 20;
float get_player_size() {return player_size;}
void  set_player_size(float size) {player_size = size;}
float player_acceleration = 100;
float get_player_acceleration() {return player_acceleration;}
void  set_player_acceleration(float acc) {player_acceleration = acc;}
////////////////////////////////////////

bool bouncy_walls = false;
bool get_bouncy_walls() {return bouncy_walls;}
void set_bouncy_walls(bool bouncy) {bouncy_walls = bouncy;}

bool disable_gravity = false;
bool get_disable_gravity() {return disable_gravity;}
void set_disable_gravity(bool disable) {disable_gravity = disable;}

bool infinite_ammo = false;
bool get_infinite_ammo() {return infinite_ammo;}
void set_infinite_ammo(bool infinite) {infinite_ammo = infinite;}

bool disable_wall_damage = false;
bool get_disable_wall_damage() {return disable_wall_damage;}
void set_disable_wall_damage(bool damage) {disable_wall_damage = damage;}

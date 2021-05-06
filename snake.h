#ifndef CURSNAKE_H
#define CURSNAKE_H

#include <curses.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define SCREEN_W 80
#define SCREEN_H 60

#define DELTA      0.05
#define INIT_SPEED 5.

#define SNAKE_HEAD(x) x->body.next
#define SNAKE_BACK(x) x->body.prev

#define LOSE_MSG "Lose. Press 'r' to retry"

#define SNAKE_COLORS 213

enum Dir {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

enum State {
    PLAY,
    LOSE
};

typedef struct {
    int x;
    int y;
    int color;
} t_treat;

typedef struct s_snake_node {
    int                 x;
    int                 y;
    struct s_snake_node *prev;
    struct s_snake_node *next;
} t_snake_node;

typedef struct {
    enum         Dir dir;
    enum         State state;
    float        speed;
    float        frame_size;
    t_snake_node body;
    t_treat      treat;
    int          moved;
    int          color;
} t_snake;


void         bye(t_snake *snake, WINDOW *win);
t_snake_node *new_node(int x, int y);
void         add_node(t_snake_node *body, t_snake_node *node);
void         clear_nodes(t_snake_node *body);
void         move_snake(t_snake *snake);
void         spawn_treat(t_treat *treat);
void         loop(t_snake *snake, WINDOW *win);

#endif

#include "snake.h"

t_snake_node *new_node(int x, int y) {
    t_snake_node *node = malloc(sizeof(t_snake_node));

    if (!node)
        return 0;
    node->x = x;
    node->y = y;
    return node;
}

void add_node(t_snake_node *body, t_snake_node *node) {
    node->prev = body->prev;
    node->next = body;
    body->prev->next = node;
    body->prev = node;
}

void clear_nodes(t_snake_node *body) {
    t_snake_node *tmp = body->next;

    while (tmp != body) {
        tmp = tmp->next;
        free(tmp->prev);
    }
    body->next = body;
    body->prev = body;
}


// moves the back node to the front and shifts its
// coordinates accordingly to direction
void move_snake(t_snake *snake) {
    t_snake_node *back = SNAKE_BACK(snake);

    if (SNAKE_HEAD(snake) != back) {
        t_snake_node *body = &snake->body;
        body->prev = back->prev;
        body->prev->next = body;
        back->prev = body;
        back->next = body->next;
        back->next->prev = back;
        body->next = back;

        back->x = back->next->x;
        back->y = back->next->y;
    }

    if (snake->dir == UP)
        back->y--;
    else if (snake->dir == LEFT)
        back->x--;
    else if (snake->dir == DOWN)
        back->y++;
    else
        back->x++;
}

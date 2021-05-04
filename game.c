#include "snake.h"

void spawn_treat(t_treat *treat) {
    treat->x = rand() % (SCREEN_W - 1);
    treat->y = rand() % (SCREEN_H - 1);
}

void process_keys(t_snake *snake, WINDOW *win) {
    int ch = wgetch(win);

    if (ch != ERR) {
        if (ch == 'q')
            bye(snake, win);
        if (snake->state == PLAY) {
            if (ch == 'w' && snake->dir != DOWN)
                snake->dir = UP;
            else if (ch == 'a' && snake->dir != RIGHT)
                snake->dir = LEFT;
            else if (ch == 's' && snake->dir != UP)
                snake->dir = DOWN;
            else if (ch == 'd' && snake->dir != LEFT)
                snake->dir = RIGHT;
        } else if (snake->state == LOSE) {
            if (ch == 'r') {
                t_snake_node *node = new_node(SCREEN_W >> 1, SCREEN_H >> 1);
                if (!node)
                    bye(snake, win);
                add_node(&snake->body, node);
                snake->state = PLAY;
                spawn_treat(&snake->treat);
                snake->frame_size = 1.;
                snake->speed = INIT_SPEED;
            }
        }
    }
}

void draw(t_snake *snake, WINDOW *win) {
    wclear(win);

    box(win, 0, 0);

    if (snake->state == PLAY) {
        mvwaddch(win, snake->treat.y, snake->treat.x, '@');
        for (t_snake_node *n = SNAKE_HEAD(snake); n != &snake->body; n = n->next)
            mvwaddch(win, n->y, n->x, '#');
    } else if (snake->state == LOSE) {
        mvwaddstr(win, SCREEN_H >> 1, (SCREEN_W >> 1) - (strlen(LOSE_MSG) >> 1), LOSE_MSG);
    }
    wrefresh(win);
}

// walls collision
int check_walls(t_snake *snake) {
    t_snake_node *head = SNAKE_HEAD(snake);

    return !(head->x < 1 || head->x >= SCREEN_W - 1 ||
        head->y < 1 || head->y >= SCREEN_H - 1);
}

// self collision
int check_self(t_snake *snake) {
    t_snake_node *head = SNAKE_HEAD(snake);
    t_snake_node *tmp = SNAKE_BACK(snake);

    for (; tmp != head; tmp = tmp->prev)
        if (tmp->x == head->x && tmp->y == head->y)
            return 0;
    return 1;
}

void loop(t_snake *snake, WINDOW *win) {
    while (1) {
        process_keys(snake, win);
        if (snake->state == PLAY) {
            // when frame_size hits 1, the snake moves
            snake->frame_size += snake->speed * DELTA;
            if (snake->frame_size >= 1.) {
                // if snake head hits a treat - add node to snake and spawn a new treat
                if (SNAKE_HEAD(snake)->x == snake->treat.x && SNAKE_HEAD(snake)->y == snake->treat.y) {
                    t_snake_node *node = new_node(0, 0);
                    if (!node)
                        bye(snake, win);
                    add_node(&snake->body, node);
                    spawn_treat(&snake->treat);
                    snake->speed += 0.5;
                }
                move_snake(snake);
                snake->frame_size = 0.;
            }
            if (!check_walls(snake) || !check_self(snake)) {
                clear_nodes(&snake->body);
                snake->state = LOSE;
            }
        }
        draw(snake, win);
        usleep(40000);
    }
}

#include "snake.h"

void bye(t_snake *snake, WINDOW *win) {
    clear_nodes(&snake->body);
    cbreak();
    echo();
    delwin(win);
    endwin();
    exit(0);
}

void init_colors() {
    for (int i = 0; i < SNAKE_COLORS; i++)
        init_pair(i + 1, 0, i + 17);
}

int main() {
    t_snake snake;
    WINDOW *win;
    srand(time(0));

    initscr();
    win = newwin(SCREEN_H, SCREEN_W, 0, 0);
    nocbreak();
    noecho();
    nodelay(win, TRUE);
    curs_set(0);
    start_color();
    init_colors();

    snake.body.next = &snake.body;
    snake.body.prev = &snake.body;
    snake.state = PLAY;
    snake.dir = RIGHT;
    snake.speed = INIT_SPEED;
    snake.frame_size = 1.;
    snake.moved = 1;
    snake.color = 1;

    t_snake_node *node = new_node(SCREEN_W >> 1, SCREEN_H >> 1);
    if (!node)
        bye(&snake, win);
    add_node(&snake.body, node);

    spawn_treat(&snake.treat);
    signal(SIGINT, SIG_IGN);
    loop(&snake, win);
}

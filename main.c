#include "snake.h"

void bye(t_snake *snake, WINDOW *win) {
    clear_nodes(&snake->body);
    cbreak();
    echo();
    delwin(win);
    endwin();
    exit(0);
}

int main() {
    t_snake snake;
    WINDOW *win;

    initscr();
    win = newwin(SCREEN_H, SCREEN_W, 0, 0);
    nocbreak();
    noecho();
    nodelay(win, TRUE);
    curs_set(0);
    start_color();
    init_pair(1, 0, 28); // green
    init_pair(2, 0, 21); // blue

    snake.body.next = &snake.body;
    snake.body.prev = &snake.body;
    snake.state = PLAY;
    snake.dir = RIGHT;
    snake.speed = INIT_SPEED;
    snake.frame_size = 1.;
    snake.moved = 1;

    t_snake_node *node = new_node(SCREEN_W >> 1, SCREEN_H >> 1);
    if (!node)
        bye(&snake, win);
    add_node(&snake.body, node);

    srand(time(0));
    spawn_treat(&snake.treat);
    signal(SIGINT, SIG_IGN);
    loop(&snake, win);
}

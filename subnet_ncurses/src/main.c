#include <ncurses.h>
#include <stdlib.h>

int main(void) {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  curs_set(1);

  /* smaller so it works on small terminals */
  WINDOW *w = newwin(5, 20, 0, 0);
  box(w, 0, 0);
  mvwprintw(w, 1, 1, "OLA");
  wrefresh(w);

  wgetch(w);
  delwin(w);
  endwin();
  return EXIT_SUCCESS;
}

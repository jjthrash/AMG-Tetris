#include <FL/Fl.H>
#include <FL/Fl_Window.H>

#include "board.hpp"

void handle_timeout(void *context) {
  Board *board = (Board*)context;
  board->updateDisplay();
}

int main(int argc, char **argv) {
  Fl_Window *window = new Fl_Window(440,840);
  Board *board = new Board(20,20,400,800);
  window->end();
  window->show(argc, argv);
  Fl::repeat_timeout(0.001, handle_timeout, (void*)board);
  return Fl::run();
}


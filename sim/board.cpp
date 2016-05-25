#include "board.hpp"
#include <FL/Fl_draw.H>

Board::Board(int x, int y, int w, int h) : Fl_Widget(x,y,w,h) {
  clearBoard();
}

void Board::clearBoard() {
  for (int i = 0; i < BOARD_WIDTH_BLOCKS; i++) {
    for (int j = 0; j < BOARD_HEIGHT_BLOCKS; j++) {
      this->matrix[i][j] = fl_rgb_color(0,0,0);
    }
  }
}

void Board::setCartesianPixelColor(int x, int y, int r, int g, int b) {
  this->matrix[x][y] = fl_rgb_color(r, g, b);
}

void Board::setLinearPixelColor(int i, int r, int g, int b) {
  this->matrix[i%BOARD_WIDTH_BLOCKS][i/BOARD_WIDTH_BLOCKS] =
    fl_rgb_color(r, g, b);
}

int Board::blockX(int i, int j) {
  //top left + i * blockwidth
  return this->x() + i * this->blockW(i, j);
}

int Board::blockY(int i, int j) {
  return this->y() + j * this->blockH(i, j);
}

int Board::blockW(int i, int j) {
  return this->w() / BOARD_WIDTH_BLOCKS;
}

int Board::blockH(int i, int j) {
  return this->h() / BOARD_HEIGHT_BLOCKS;
}

void Board::updateDisplay() {
  for (int i = 0; i < BOARD_WIDTH_BLOCKS; i++) {
    for (int j = 0; j < BOARD_HEIGHT_BLOCKS; j++) {
      fl_color(matrix[i][j]);
      fl_rectf(this->blockX(i,j),
               this->blockY(i,j),
               this->blockW(i,j),
               this->blockH(i,j));
    }
  }
}

int Board::readRight() {
  return 0;
}

int Board::readLeft() {
  return 0;
}

int Board::readUp() {
  return 0;
}

int Board::readDown() {
  return 0;
}

void Board::draw() {
  fl_color(123, 56, 23);
  fl_rectf(this->x(), this->y(), this->w(), this->h());
}


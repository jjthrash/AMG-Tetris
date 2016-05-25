#include <FL/Fl.H>
#include <FL/Fl_Widget.H>

#define BOARD_WIDTH_BLOCKS 10
#define BOARD_HEIGHT_BLOCKS 20

class Board : public Fl_Widget {
  public:
    Board(int x, int y, int w, int h);
    void setCartesianPixelColor(int x, int y, int r, int g, int b);
    void setLinearPixelColor(int i, int r, int g, int b);
    void updateDisplay();
    int readRight();
    int readLeft();
    int readUp();
    int readDown();
    void draw();

  private:
    //place to store stuff
    Fl_Color matrix[BOARD_WIDTH_BLOCKS][BOARD_HEIGHT_BLOCKS];
    int blockX(int i, int j);
    int blockY(int i, int j);
    int blockW(int i, int j);
    int blockH(int i, int j);
};

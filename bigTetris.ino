/*
Copyright 2014 Joel Lienhard  (joel@mclien.de  joel@sisam42.de)

Modified by the Alamance Makers Guild 5/6/2016 (Jeff Wright, Schae Stewart, Danny Oakley)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Need to have e copy of adafruits nepixel Library in the according arduino folder
#include <Adafruit_NeoPixel.h>

#define PIN 3
#define UP 9
#define Left 10
#define Right 11
#define DOWN 12

#define matrixx 20
#define matrixy 10
#define fallspeedorg 160
#define debouncevalue 10

int pos[2] = {1, 5};//Start position of block of initial block, start position of additional blocks is in checkend udf
int bricks[7][4][2] = {{{0, 1}, {-1, 0}, {0, 0}, {1, 0}}, {{-1, 1}, {-1, 0}, {0, 0}, {1, 0}}, {{1, 1}, {-1, 0}, {0, 0}, {1, 0}}, {{-1, 0}, {0, 0}, {0, 1}, {1, 1}}, {{-1, 1}, {0, 1}, {0, 0}, {1, 0}}, {{1, 0}, {1, 1}, {0, 1}, {0, 0}}, {{-1, 0}, {0, 0}, {1, 0}, {2, 0}}};
int colors[7][3] = {{255, 0, 0}, {100, 255, 0}, {0, 0, 255}, {255, 255, 0}, {0, 255, 255}, {255, 100, 0}, {255, 255, 255}};
int matrix[matrixx][matrixy] = {0};
int current[4][2] = {{1, 1}, {-1, 0}, {0, 0}, {1, 0}};
int currentcach[4][2] = {0};
int currentnum = 1;
int truepos[2] = {0,0};
int fallspeed = fallspeedorg;
int fallcount = 1;
int debounce = 0;
int moveable = 0;
int fullrow = 0;
int rowtodelete = 0;
int gameover = 0;
int RotateState = 0;         // variable for reading the rotate pushbutton status
int LeftState = 0;         // variable for reading the left pushbutton status
int RightState = 0;         // variable for reading the right pushbutton status
int DownState = 0;         // variable for reading the down pushbutton status
int score = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(200, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();
  pinMode(UP, INPUT);
  pinMode(DOWN, INPUT);
  pinMode(Left, INPUT);
  pinMode(Right, INPUT);
}

void loop(){
  if(fallcount == fallspeed){
    fallcount = 0;
    down();
  }

  // read and store the state of the pushbutton value:
  RotateState = digitalRead(UP);
  LeftState = digitalRead(Left);
  RightState = digitalRead(Right);
  DownState = digitalRead(DOWN);

  // Direct to udf with intended action if button was recorded as active.
  if(RotateState == 1 and debounce == 0){
    debounce = debouncevalue * 1.5;
    rotate();
  }
  if(RightState == 1 and debounce == 0){
    debounce = debouncevalue;
    right();
  }
  if(LeftState == 1 and debounce == 0){
    debounce = debouncevalue;
    left();
  }
  if(DownState == 1 and debounce == 0){
    debounce = debouncevalue;
    down();
  }


  if(debounce != 0){
    debounce--;
  }
  fallcount++;
  checkrows();// Checks to see if rows are full
  checkend();//Checks to see if game is over
  show();
}

// Checks to see if their is room for another game piece then inserts it. If not it shows the score by displaying an LED for each full row in the round.
void checkend(){
  gameover = 0;
  for(int y = 0; y < matrixy; y++){
    if(matrix[1][y] != 0){
      gameover = 1;
    }
  }
  if(gameover == 1){
    showScore();
    fallspeed = fallspeedorg;
    pos[0] = 0;
    pos[1] = 5;
    for(int x = 0; x < matrixx; x++){
        for(int y = 0; y< matrixy; y++){
        matrix[x][y] = 0;
      }
    }
    add(random(7));
    for(int x = 0; x < matrixx; x++){
      for(int y = 0; y< matrixy; y++){
        matrix[x][y] = 0;

      }
    }
  }
}
// Checks to see if the game piece has room to fall, if not checks all rows to see if a full row has been made. If so, removes the row and increases the speed by reducing the time between falling to 80% of the previous value
void checkrows(){
  for(int x = 0; x < matrixx; x++){
    fullrow = 1;
    for(int y = 0; y < matrixy; y++){
      if(matrix[x][y] == 0){
        fullrow = 0;
      }
    }

    if(fullrow == 1){
      score = score +1;
      for(int row = x; row > 0; row--){
        for(int y = 0; y < matrixy; y++){
          matrix[row][y] = matrix[row-1][y];
        }
      }
      //Speed up the game every 2 points
      if(score%2 == 1 and fallspeed * 0.9 > 1){
        fallspeed = fallspeed * 0.9;
      }
      if(fallspeed * 0.9 < 1 and fallspeed -1 > 0){
        fallspeed = fallspeed -1;
      }
    }
  }
}

void left(){
  moveable = 1;
  for(int e = 0; e < 4; e++){
    if(matrix[current[e][0]+pos[0]][current[e][1]+pos[1]+1] != 0){
      moveable = 0;
    }
    if(current[e][1]+pos[1]+1 == matrixy){
      moveable = 0;
    }
  }
  if(moveable == 1){
    pos[1]++;
  }
}

void right()  {
  moveable = 1;
  for(int e = 0; e < 4; e++){
    if(matrix[current[e][0]+pos[0]][current[e][1]+pos[1]-1] != 0){
      moveable = 0;
    }
//    if(current[e][0]+pos[0]-1 == 0){
    if(current[e][1]+pos[1] == 0){
      moveable = 0;
    }
  }
  if(moveable == 1){
    pos[1]--;
  }
}

void down(){
  moveable = 1;
  for(int e = 0; e < 4; e++){
    if(matrix[current[e][0]+pos[0]+1][current[e][1]+pos[1]] != 0){
      moveable = 0;
    }
    if(current[e][0]+pos[0]+1 == matrixx){
      moveable = 0;
    }
  }
  if(moveable == 1){
    pos[0]++;
  }
   else{
    add(random(7));
  }
}

void rotate(){
  for(int e = 0; e < 4; e++){
    currentcach[e][0] = current[e][0];
    currentcach[e][1] = current[e][1];
  }
  for(int e = 0; e < 4; e++){
    current[e][1] = currentcach[e][0];
    current[e][0] = -currentcach[e][1];
  }
  moveable = 1;
  for(int e = 0; e < 4; e++){
    if(matrix[current[e][0]+pos[0]][current[e][1]+pos[1]] != 0 or current[e][0]+pos[1] < 0 or current[e][0]+pos[1] > 9 or currentnum == 5){
      moveable = 0;
    }
  }

  if(moveable == 0){
    for(int e = 0; e < 4; e++){
      current[e][0] = currentcach[e][0];
      current[e][1] = currentcach[e][1];
    }
  }
}

void add(int b){
  for(int e = 0; e < 4; e++){
    matrix[current[e][0]+pos[0]][current[e][1]+pos[1]] = currentnum + 1;
    current[e][0] = bricks[b][e][0];
    current[e][1] = bricks[b][e][1];
  }
  currentnum = b;
  pos[0] = 1;
  pos[1] = 5;
}

void setCartesianPixelColor(int x, int y, int r, int g, int b) {
  // The IF statement takes all even rows and reverses them. This accounts for all odd rows linking from left to right and all even rows connecting from right to left.
  if (x % 2) {
    strip.setPixelColor((x*matrixy)+y, r, g, b);
  }
  else {
    strip.setPixelColor((x*matrixy)+(matrixy-y-1), r, g, b);
  }
}

void setLinearPixelColor(int i, int r, int g, int b) {
  strip.setPixelColor(i, r, g, b);
}

void updateDisplay() {
  strip.show();
}

void clearBoard() {
  for(int i = 0; i < strip.numPixels(); i++){
    setLinearPixelColor(i, 0, 0, 0);
  }
}


//Displays the screen by converting the matrix (gameboard) into a continuous LED strip.
void show(){
  clearBoard();

  // displays old pieces?
  for(int x = 0; x < matrixx; x++){
    for(int y = 0; y < matrixy; y ++){
      if(matrix[x][y] != 0) {
        setCartesianPixelColor(x, y, colors[matrix[x][y]-1][0], colors[matrix[x][y]-1][1], colors[matrix[x][y]-1][2]);
      }
    }
  }

  // displays current falling piece? This seems redundant, since I *think* matrix has the piece already
  for(int e = 0; e < 4; e++){
    truepos[0] = current[e][0]+pos[0];
    truepos[1] = current[e][1]+pos[1];
    setCartesianPixelColor(truepos[1], truepos[0], colors[currentnum][0], colors[currentnum][1], colors[currentnum][2]);
  }
  updateDisplay();
}


void showScore(){
  clearBoard();

  if(score == 0){
    setLinearPixelColor(0, 255, 0, 0);
  }
  for(int i = 0; i < score; i++){
    setLinearPixelColor(i, 255, 255, 255);
  }
  updateDisplay();
  score = 0;
  delay(1000);

  // read and store the state of the pushbutton value:
  for(int i = 0; i < 3; i++){
    RotateState = digitalRead(UP);
    LeftState = digitalRead(Left);
    RightState = digitalRead(Right);
    DownState = digitalRead(DOWN);

    // Direct to udf with intended action if button was recorded as active.
    if(RotateState == 1 or RightState == 1 or LeftState == 1 or DownState == 1){
      i = 5;
    }
    else{
      i = 0;
    }
  }
}

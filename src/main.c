#include "../screen/screen.h"
#include "../server/server.h"
#include "../objects/objects.h"
#include "../actor/actor.h"
typedef struct {
  float mat[4][4];
} ProjectionMatrix;

typedef struct {
  float mat[4][4];
} RotationMatrix;

int main(int argc, char *argv[]) {
  Screen screen;

  if (initScreen(&screen, 0, 0) != 0) { // Width and height later
    printf("Failed to initialize screen.");
    return 1;
  }
  
  /*
  for (;;) {
    drawLine(&screen, '+', 10.0f, 30.0f, 10.0f, 10.0f);
    drawLine(&screen, '+', 10.0f, 10.0f, 30.0f, 10.0f);
    drawLine(&screen, '+', 30.0f, 10.0f, 10.0f, 30.0f);

    printScreen(&screen);
    clearScreen(&screen);
    clearTerminal(&screen);

    drawLine(&screen, '+', 10.0f, 10.0f, 30.0f, 10.0f);
    drawLine(&screen, '+', 30.0f, 10.0f, 30.0f, 30.0f);
    drawLine(&screen, '+', 30.0f, 30.0f, 10.0f, 10.0f);

    printScreen(&screen);
    clearScreen(&screen);
    clearTerminal(&screen);

    drawLine(&screen, '+', 10.0f, 30.0f, 30.0f, 10.0f);
    drawLine(&screen, '+', 30.0f, 10.0f, 30.0f, 30.0f);
    drawLine(&screen, '+', 30.0f, 30.0f, 10.0f, 30.0f);

    printScreen(&screen);
    clearScreen(&screen);
    clearTerminal(&screen);

    drawLine(&screen, '+', 10.0f, 30.0f, 10.0f, 10.0f);
    drawLine(&screen, '+', 10.0f, 10.0f, 30.0f, 30.0f);
    drawLine(&screen, '+', 30.0f, 30.0f, 10.0f, 30.0f);

    printScreen(&screen);
    clearScreen(&screen);
    clearTerminal(&screen);
  }
  */

  /*
  float x1 = 50, y1 = 30.0f, x2 = 50.0f, y2 = 30.0f;
  
  for (;;) {
    drawLine(&screen, '+', 30.0f, 30.0f, 30.0f, 10.0f);
    drawLine(&screen, '+', x1, y1, 30.0f, 10.0f);
    drawLine(&screen, '+', 30.0f, 30.0f, x2, y2);

    printScreen(&screen);
    clearScreen(&screen);
    clearTerminal();

    x1+=0.5f;
    y1+=0.5f;
    x2+=0.5f;
    y2+=0.5f;

    if (x2 > SCREEN_WIDTH) {
      x1 = 30; y1 = 10.0f; x2 = 50.0f; y2 = 30.0f;
    }
  }
  */

  float a = 10.0f, b = 10.0f;

  for (;;) {
    fillScreen(&screen, '.');

    drawLine(&screen, '+', 15.0f, 30.0f, 15.0f, 15.0f);
    drawLine(&screen, '+', 15.0f, 15.0f, 30.0f, 15.0f);
    drawLine(&screen, '+', 30.0f, 15.0f, 15.0f, 30.0f);
    
    //drawLine(&screen, '+', 15.0f, 30.0f, 30.0f, 15.0f);
    drawLine(&screen, '+', 30.0f, 15.0f, 30.0f, 30.0f);
    drawLine(&screen, '+', 30.0f, 30.0f, 15.0f, 30.0f);
    
    printScreen(&screen);
    clearTerminal();
  }
  
  return 0;
}

#pragma once
#include "../common/common.h"


#define __INTERNAL_ASPECT_RATIO__ 4

#define __INT_FRAME_HEIGHT__ 45
#define __INT_FRAME_WIDTH__  __INT_FRAME_HEIGHT__ * __INTERNAL_ASPECT_RATIO__

#define __FRAME_HEIGHT__ 45.0f
#define  __FRAME_WIDTH__  __FRAME_HEIGHT__ * __INTERNAL_ASPECT_RATIO__

#define __ASPECT_RATIO__ (float)(__FRAME_WIDTH__/__FRAME_HEIGHT__)

#define SCREEN_HEIGHT __FRAME_HEIGHT__
#define SCREEN_WIDTH  __FRAME_HEIGHT__
#define SCALAR_ASPECT_RATIO  2

#define X_CENTER_OFSET_VALUE (__FRAME_WIDTH__/8)
#define Y_CENTER_OFSET_VALUE (__FRAME_HEIGHT__/2)

typedef struct {
  char  ASCIIBuffer[__INT_FRAME_HEIGHT__][__INT_FRAME_WIDTH__];
  float depthBuffer[__INT_FRAME_HEIGHT__][__INT_FRAME_WIDTH__];
} Buffer;

int initBuffer(Buffer *buffer) {
  if (buffer == NULL) return 1;
  for (int i = 0; i < __FRAME_HEIGHT__; i++) {
    for (int j = 0; j < __FRAME_WIDTH__; j++) {
      buffer->ASCIIBuffer[i][j] = ' ';
      buffer->depthBuffer[i][j] = 0.0f;
    }
  }
  return 0;
}

int mergeBuffer(Buffer *result, Buffer *bottom, Buffer *top) {
  if (result == NULL || bottom == NULL || top == NULL) return 1;
  for (int i = 0; i < __FRAME_HEIGHT__; i++) {
    for (int j = 0; j < __FRAME_WIDTH__; j++) {
      if (top->ASCIIBuffer[i][j] == ' ') {
        result->ASCIIBuffer[i][j] = bottom->ASCIIBuffer[i][j];
      } else {
        result->ASCIIBuffer[i][j] = top->ASCIIBuffer[i][j];
      }
    }
  }
  return 0;
}

// INITIALIZING & CLEARING

int fillBuffer(Buffer *buffer, const char fill) {
  if (buffer == NULL) return 1;
  for (int i = 0; i < __FRAME_HEIGHT__; i++) {
    for (int j = 0; j < __FRAME_WIDTH__; j++) {
      buffer->ASCIIBuffer[i][j] = fill;
      buffer->depthBuffer[i][j] = 0.0f;
    }
  }
  return 0;
}

int clearBuffer(Buffer *buffer) {
  if (buffer == NULL) return 1;
  for (int i = 0; i < __FRAME_HEIGHT__; i++) {
    for (int j = 0; j < __FRAME_WIDTH__; j++) {
      buffer->ASCIIBuffer[i][j] = ' ';
      buffer->depthBuffer[i][j] = 0.0f;
    }
  }
  return 0;
}

void clearTerminal() {
  printf("\033[2J\033[H");
}

// DRAWING

/*
  Implement a way to choose the char based on the depth of the point;
*/

int plotPoint(Buffer *buffer, const char fill, float x, float y) {
  if (buffer == NULL) return 1;

  x *= __ASPECT_RATIO__;
  buffer->ASCIIBuffer[(int)y][(int)x] = fill;
  return 0;
}

int plotSmartPoint(Buffer *buffer, float x, float y) { // NEEDS WORK
  if (buffer == NULL) return 1;

  char fill;

  if (1.0f <= (y/x) && (y/x) <= 2.0f) {
    fill = '/';
  } else if (-1.0f <= (y/x) && (y/x) <= -2.0f) {
    fill = '\\';
  } else if (-1.0f < (y/x) && (y/x) < 1.0f) {
    fill = '.';
  } else if ((y/x) > 2.0f) {
    fill = '|';
  } else {
    fill = '.';
  }

  x *= __ASPECT_RATIO__;
  buffer->ASCIIBuffer[(int)y][(int)x] = fill;
  return 0;
}

int drawSimpleLine(Buffer *buffer, char fill, float x1, const float y1, float x2, const float y2) {
    if (buffer == NULL) return 1;
    if (__ASPECT_RATIO__ * x1 > __FRAME_WIDTH__  ||
        __ASPECT_RATIO__ * x2 > __FRAME_WIDTH__  ||
                           y1 > __FRAME_HEIGHT__ ||
                           y2 > __FRAME_HEIGHT__ ){
          printf("[ERROR] Vertex (%f, %f) out of bounds!\n\t~ Process terminated", x1 > x2 ? x1 : x2, y1 > y2 ? y1 : y2);
          exit(1);
        }

    float dx = SCALAR_ASPECT_RATIO * (x2 - x1);
    float dy = y2 - y1;
    int steps;
    float xIncrement, yIncrement, x = SCALAR_ASPECT_RATIO * x1, y = y1;

    if (fabs(dx) > fabs(dy)) {
        steps = fabs(dx);
    } else {
        steps = fabs(dy);
    }

    xIncrement = dx / steps;
    yIncrement = dy / steps;

    for (int k = 0; k <= steps; k++) {
        if (y > __FRAME_HEIGHT__ || x > __FRAME_WIDTH__) continue;
           
        buffer->ASCIIBuffer[(int)round(y)][(int)round(x)] = fill; // [(int)y][(int)x] = fill; // 
        buffer->depthBuffer[(int)round(y)][(int)round(x)] = 0.0f;
        x += xIncrement;
        y += yIncrement;
    }

    return 0;
}

int drawLine(Buffer *buffer, const char *ASCIICharSet, float x1, float y1, float z1, float x2, float y2, float z2) {
  if (buffer == NULL) return 1;
  if (__ASPECT_RATIO__ * x1 > __FRAME_WIDTH__  ||
      __ASPECT_RATIO__ * x2 > __FRAME_WIDTH__  ||
                         y1 > __FRAME_HEIGHT__ ||
                         y2 > __FRAME_HEIGHT__ ){
        printf("[ERROR] Vertex (%f, %f, %f) out of bounds!\n\t~ Process terminated", x1 > x2 ? x1 : x2, y1 > y2 ? y1 : y2);
        exit(1);
      }

  if (x1 > 1 || x2 > 1) { // Do not render past this point
    
  }
    
  return 0;
}

// FILLING TRIANGLES

int fillTriangle1(Buffer *buffer, const char fill, float v1_x, float v1_y, float v2_x, float v2_y, float v3_x, float v3_y) {
  for (int i = 0; i < 100; i++) {
    
  }
}

int sortVertices(int* yValues, int* xValues) {
  if (yValues[0] > yValues[1]) {
    // Swap yValues
    int tempY = yValues[0];
    yValues[0] = yValues[1];
    yValues[1] = tempY;

    // Swap corresponding xValues
    int tempX = xValues[0];
    xValues[0] = xValues[1];
    xValues[1] = tempX;
  }

  if (yValues[0] > yValues[2]) {
    // Swap yValues
    int tempY = yValues[0];
    yValues[0] = yValues[2];
    yValues[2] = tempY;

    // Swap corresponding xValues
    int tempX = xValues[0];
    xValues[0] = xValues[2];
    xValues[2] = tempX;
  }

  if (yValues[1] > yValues[2]) {
    // Swap yValues
    int tempY = yValues[1];
    yValues[1] = yValues[2];
    yValues[2] = tempY;

    // Swap corresponding xValues
    int tempX = xValues[1];
    xValues[1] = xValues[2];
    xValues[2] = tempX;
  }

  return 0;
}

int fillTriangle(Buffer *buffer, const char fill, int x1, int y1, int x2, int y2, int x3, int y3) {
  int minY = y1;
  int maxY = y3;

  // Sort vertices based on their y-coordinates
  int yValues[3] = {y1, y2, y3};
  int xValues[3] = {x1, x2, x3};
  sortVertices(yValues, xValues);

  for (int y = minY; y <= maxY; y++) {
    int xLeft = ((y - yValues[0]) * (xValues[2] - xValues[0])) / (yValues[2] - yValues[0]) + xValues[0];
    int xRight;

    if (y < yValues[1]) {
        xRight = ((y - yValues[0]) * (xValues[1] - xValues[0])) / (yValues[1] - yValues[0]) + xValues[0];
    } else {
        xRight = ((y - yValues[1]) * (xValues[2] - xValues[1])) / (yValues[2] - yValues[1]) + xValues[1];
    }

    drawSimpleLine(buffer, fill, (float)xLeft, (float)y, (float)xRight, (float)y);
  }
  return 0;
}

// TEXT

int printText(Buffer *buffer, const char *text, const float x, const float y) { // Coordintes of first character
  int co_x = (int)x;
  int co_y = (int)y;
  int i = 0;
  while (text[i] != '\0') {
    if (text[i] == '\n') {
      co_y++;
      co_x = (int)x;
    } else {
      buffer->ASCIIBuffer[co_y][co_x++] = text[i];
    }
    i++;
  }
}

// RENDERING

int renderFrame(Buffer *buffer) {
  if (buffer == NULL) return 1;
  return 0;
}

int printBufferToTerminal(Buffer *buffer) {
  if (buffer == NULL) return 1;
  for (int i = 0; i < __FRAME_HEIGHT__; i++) {
    for (int j = 0; j < __FRAME_WIDTH__; j++) {
      putchar(buffer->ASCIIBuffer[i][j]);
    }
    putchar('\n');
  }
  return 0;
}

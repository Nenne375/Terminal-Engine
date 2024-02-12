#pragma once
#include "./camera.h"
#include "../../screen/screen.h"

typedef struct {
  Camera camera;
  Buffer overlay;
} Player;

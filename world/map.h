#pragma once

typedef struct {
  float position[16];
} Chunk;

typedef struct {
  Chunk *map;
} Map;

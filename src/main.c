#include "../screen/screen.h"
#include "../server/server.h"

#include "../world/components/objects.h"
#include "../world/components/actor.h"
#include "../world/map.h"

#include "../world/player/player.h"

int main(int argc, char *argv[]) {
  Buffer frame;
  Buffer buffer;
  Buffer overlay;

  if (initBuffer(&frame) != 0   ||
      initBuffer(&buffer) != 0  ||
      initBuffer(&overlay) != 0 ){
      printf("Failed to initialize buffers");
      return 1;
  }

  fillBuffer(&frame, '.');
  drawSimpleLine(&frame, '@', 0.0f, 0.0f, 90.0f, 45.0f);
  printBufferToTerminal(&frame);
  return 0;
}

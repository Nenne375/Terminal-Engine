#include "../common/common.h"

#define VERTICES_ALLOCATION_FAILED           obj->vertices==NULL
#define NORMALS_ALLOCATION_FAILED             obj->normals==NULL
#define TEXTURECOORDS_ALLOCATION_FAILED obj->textureCoords==NULL
#define FACES_ALLOCATION_FAILED                 obj->faces==NULL

typedef struct {
  float x, y, z;
} Vertex;

typedef struct {
  float x, y, z;
} VertexNormal;

typedef struct {
  float u, v;
} VertexTextureCoord;

typedef struct {
  int vIndex, nIndex, tIndex;
} VertexFace;

typedef struct {
  Vertex p1, p2; // Point 1 and 2
} Vector;

/*
typedef struct {
  
} Triangle;
*/
typedef struct {
  int vCount, vCapacity,
      nIndex, nCapacity,
      tIndex, tCapacity,
      fIndex, fCapacity;

  Vertex *vertices;
  VertexNormal *normals;
  VertexTextureCoord *textureCoords;
  VertexFace *faces;
} Object;

int loadObj(Object *obj, const char *file) {
  FILE *fp = fopen(file, "r");

  if (fp == NULL) {
    perror("~ Error opening model file");
    fclose(fp);
    return 1;
  }

  obj->vCount = obj->nIndex = obj->tIndex = obj->fIndex = 0;
  obj->vCapacity = obj->nCapacity = obj->tCapacity = obj->fCapacity = 10;

  obj->vertices = (Vertex*) malloc(sizeof(Vertex) * obj->vCapacity);
  obj->normals = (VertexNormal*) malloc(sizeof(VertexNormal) * obj->nCapacity);
  obj->textureCoords = (VertexTextureCoord*) malloc(sizeof(VertexTextureCoord) * obj->tCapacity);
  obj->faces = (VertexFace*) malloc(sizeof(VertexFace) * obj->fCapacity);

  char line[256];

  int i = 0;

  while(fgets(line, sizeof(line), fp) != NULL) {
    char type[3];
    if (sscanf(line, "%2s", type) == 1) {
      if (strcmp(type, "v") == 0) {
        // Read the vertex coordinates
        if (obj->vCapacity <= obj->vCount) {
          obj->vCapacity *= 2;
          obj->vertices = (Vertex*) realloc(obj->vertices, sizeof(Vertex) * obj->vCapacity);

          if (VERTICES_ALLOCATION_FAILED)
            return 2;
        }

        sscanf(line, "v %f %f %f", &(obj->vertices[obj->vCount].x), &(obj->vertices[obj->vCount].y), &(obj->vertices[obj->vCount].z));
        obj->vCount++;
      } 
      
      if (strcmp(type, "vn") == 0) {
        // Read the normal coordinates
        if (obj->nCapacity <= obj->nIndex) {
          obj->nCapacity *= 2;
          obj->normals = (VertexNormal*) realloc(obj->normals, sizeof(VertexNormal) * obj->nCapacity);

          if (NORMALS_ALLOCATION_FAILED)
            return 2;
        }

        sscanf(line, "vn %f %f %f", &(obj->normals[obj->nIndex].x), &(obj->normals[obj->nIndex].y), &(obj->normals[obj->nIndex].z));
        obj->nIndex++;
      }

      if (strcmp(type, "vt") == 0) {
        // Read the normal coordinates
        if (obj->tCapacity <= obj->tIndex) {
          obj->tCapacity *= 2;
          obj->textureCoords = (VertexTextureCoord*) realloc(obj->textureCoords, sizeof(VertexTextureCoord) * obj->tCapacity);

          if (TEXTURECOORDS_ALLOCATION_FAILED)
            return 2;
        }

        sscanf(line, "vt %f %f", &(obj->textureCoords[obj->tIndex].u), &(obj->textureCoords[obj->tIndex].v));
        obj->tIndex++;
      }

      if (strcmp(type, "f") == 0) {
        // Read the normal coordinates
        if (obj->fCapacity <= obj->fIndex) {
          obj->fCapacity *= 2;
          obj->faces = (VertexFace*) realloc(obj->faces, sizeof(VertexFace) * obj->fCapacity);

          if (FACES_ALLOCATION_FAILED)
            return 2;
        }

        sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d",
          &(obj->faces[obj->fIndex].vIndex),
          &(obj->faces[obj->fIndex].tIndex),
          &(obj->faces[obj->fIndex].nIndex),
          &(obj->faces[obj->fIndex + 1].vIndex),
          &(obj->faces[obj->fIndex + 1].tIndex),
          &(obj->faces[obj->fIndex + 1].nIndex),
          &(obj->faces[obj->fIndex + 2].vIndex),
          &(obj->faces[obj->fIndex + 2].tIndex),
          &(obj->faces[obj->fIndex + 2].nIndex));
        
        obj->fIndex += 3;
      }
    }
  }

  fclose(fp);
  return 0;
}

int freeObj(Object *obj) {
  free(obj->vertices);
  free(obj->normals);
  free(obj->textureCoords);
  free(obj->faces);
  return 0;
}

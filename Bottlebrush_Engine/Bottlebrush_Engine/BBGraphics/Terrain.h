#ifndef BOTTLEBRUSH_ENGINE_TERRAIN_H
#define BOTTLEBRUSH_ENGINE_TERRAIN_H

#include <string>
#include <vector>

#include "glm/glm.hpp"
#include "stb/stb_image.h"

class Terrain {
 public:
  Terrain() = default;
  Terrain(const std::string &heightmap, float y_scale = 1.0f,
          float y_shift = 0.0f);

  [[nodiscard]] std::vector<unsigned> GetElements() const;
  [[nodiscard]] float GetHeight(float x, float z) const;
  [[nodiscard]] int GetLength() const;
  [[nodiscard]] int GetNumStrips() const;
  [[nodiscard]] int GetNumTriangles() const;
  [[nodiscard]] int GetSize() const;
  [[nodiscard]] std::vector<float> GetVertices() const;
  [[nodiscard]] int GetWidth() const;

 private:
  [[nodiscard]] bool InBounds(float x, float z) const;
  void PopulateElemBuffer();
  void PopulateVertBuffer();

  int channels_;
  unsigned char *data_;
  std::vector<unsigned> elements_;
  int length_;
  int num_strips_;
  int num_triangles;
  std::string path_;
  int size_;
  std::vector<float> vertices_;
  int width_;
  float y_scale_;
  float y_shift_;
};

#endif  // BOTTLEBRUSH_ENGINE_TERRAIN_H

#ifndef BOTTLEBRUSH_ENGINE_TERRAIN_H
#define BOTTLEBRUSH_ENGINE_TERRAIN_H

#include <string>
#include <vector>

#include "glm/glm.hpp"
#include "stb/stb_image.h"

class Terrain {
 public:
  Terrain() = default;
  Terrain(const std::string &heightmap, float y_scale, float y_shift);

  int channels_;
  unsigned char *data_;
  int length_;
  unsigned int id_;
  std::vector<unsigned int> index_buffer_;
  unsigned int num_strips_;
  unsigned int num_verts_per_strips_;
  std::string path_;
  std::vector<float> vertex_buffer_;
  int width_;
};

#endif  // BOTTLEBRUSH_ENGINE_TERRAIN_H

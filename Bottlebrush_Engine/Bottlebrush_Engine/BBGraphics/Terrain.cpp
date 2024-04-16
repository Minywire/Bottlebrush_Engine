#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#include "Terrain.h"

Terrain::Terrain(const std::string &heightmap, float y_scale, float y_shift) {
  path_ = heightmap;
  data_ = stbi_load(path_.c_str(), &width_, &length_, &channels_, 0);
  num_strips_ = length_ - 1;
  num_verts_per_strips_ = width_ * 2;

  for (int i = 0; i < length_; i++) {
    for (int j = 0; j < width_; j++) {
      unsigned char *offset = data_ + (j + width_ * i) * channels_;
      unsigned char y = offset[0];
      auto h = static_cast<float>(length_), w = static_cast<float>(width_);

      vertex_buffer_.push_back(-h / 2.0f + h * i / h);
      vertex_buffer_.push_back(y * y_scale - y_shift);
      vertex_buffer_.push_back(-w / 2.0f + w * j / w);
    }
  }

  for (unsigned i = 0; i < length_ - 1; i++) {
    for (unsigned j = 0; j < width_; j++) {
      for (unsigned k = 0; k < 2; k++) {
        index_buffer_.push_back(j + width_ * (i + k * 1));
      }
    }
  }

  stbi_image_free(data_);
}

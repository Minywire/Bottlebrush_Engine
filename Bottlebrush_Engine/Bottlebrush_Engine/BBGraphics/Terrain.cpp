#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#include "Terrain.h"

Terrain::Terrain(const std::string &heightmap, float y_scale, float y_shift) {
  data_ = stbi_load(heightmap.c_str(), &width_, &length_, &channels_, 0);
  num_strips_ = length_;
  num_triangles = width_ * 2;
  path_ = heightmap;
  size_ = width_ * length_;
  y_scale_ = y_scale;
  y_shift_ = y_shift;

  PopulateVertBuffer();
  PopulateElemBuffer();

  stbi_image_free(data_);
}

std::vector<unsigned> Terrain::GetElements() const { return elements_; }

float Terrain::GetHeight(float x, float z) const {
  int a = static_cast<int>(x), b = static_cast<int>(z);

  if (!InBounds(x, z)) return 0.0f;

  return vertices_.at(a + width_ * b);
}

int Terrain::GetLength() const { return length_; }

int Terrain::GetNumStrips() const { return num_strips_; }

int Terrain::GetNumTriangles() const { return num_triangles; }

int Terrain::GetSize() const { return size_; }

std::vector<float> Terrain::GetVertices() const { return vertices_; }

int Terrain::GetWidth() const { return width_; }

bool Terrain::InBounds(float x, float z) const {
  int a = static_cast<int>(x), b = static_cast<int>(z);

  if (a > width_ - 1 || b > length_ - 1) return false;
  if (a < 0 || b < 0) return false;

  return true;
}

void Terrain::PopulateElemBuffer() {
  for (int i = 0; i < length_; i++) {
    for (int j = 0; j < width_; j++) {
      for (int k = 0; k < 2; k++) {
        elements_.push_back(j + width_ * (i + k * 1));
      }
    }
  }
}

void Terrain::PopulateVertBuffer() {
  auto w = static_cast<float>(width_), l = static_cast<float>(length_);

  for (int i = 0; i < length_; i++) {
    for (int j = 0; j < width_; j++) {
      unsigned char *texel = data_ + (j + width_ * i) * channels_,
                    height = texel[0];

      float x = -w / 2.0f + w * static_cast<float>(j) / w,
            y = static_cast<float>(height) * y_scale_ - y_shift_,
            z = -l / 2.0f + l * static_cast<float>(i) / l;

      vertices_.push_back(x);
      vertices_.push_back(y);
      vertices_.push_back(z);
    }
  }
}

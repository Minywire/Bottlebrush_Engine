#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#endif

#include "Terrain.h"

Terrain::Terrain(const std::string &heightmap, glm::vec3 scale,
                 glm::vec3 shift) {
  data_ = stbi_load(heightmap.c_str(), &width_, &length_, &channels_, 0);

  auto w = static_cast<float>(width_), l = static_cast<float>(length_);
  centre_ = {-w / 2.0f * scale_.x, 0.0f, -l / 2.0f * scale_.z};
  num_strips_ = length_;
  num_triangles = width_ * 2;
  path_ = heightmap;
  scale_ = scale;
  shift_ = shift;
  size_ = width_ * length_;

  PopulateVertices();
  PopulateElements();
}

Terrain::~Terrain() {
  stbi_image_free(data_);
  data_ = nullptr;
}

glm::vec3 Terrain::GetCentre() const { return centre_; }

std::vector<unsigned> Terrain::GetElements() const { return elements_; }

float Terrain::GetHeight(float x, float z) const {
  auto w = static_cast<float>(width_), l = static_cast<float>(length_);

  float terrain_x = x;
  float terrain_z = z;

  float grid_size = w / l - 1.0f;
  int grid_x = std::floor(terrain_x / grid_size);
  int grid_z = std::floor(terrain_z / grid_size);

  if (grid_x < 0) grid_x = -grid_x;
  if (grid_z < 0) grid_z = -grid_z;
  if (!InBounds(grid_x, grid_z)) return 0.0f;

  float coord_x = std::fmod(terrain_x, grid_size) / grid_size;
  float coord_z = std::fmod(terrain_z, grid_size) / grid_size;
  glm::vec3 barycentre = {0.0f, 0.0f, 0.0f};

  if (coord_x <= 1 - coord_z) {
    glm::vec3 a = {0.0f, heights_.at(grid_x + width_ * grid_z), 0.0f},
              b = {1.0f, heights_.at((grid_x + 1) + width_ * grid_z), 0.0f},
              c = {0.0f, heights_.at(grid_x + width_ * (grid_z + 1)), 1.0f},
              p = {coord_x, 0.0f, coord_z};
    barycentre = Barycentric(a, b, c, p);
  } else {
    glm::vec3 a = {1.0f, heights_.at(grid_x + width_ * grid_z), 0.0f},
              b = {1.0f, heights_.at((grid_x + 1) + width_ * grid_z), 1.0f},
              c = {0.0f, heights_.at(grid_x + width_ * (grid_z + 1)), 1.0f},
              p = {coord_x, 0.0f, coord_z};
    barycentre = Barycentric(a, b, c, p);
  }

  return barycentre.y / scale_.y + shift_.y;
}

int Terrain::GetLength() const { return length_; }

int Terrain::GetNumStrips() const { return num_strips_; }

int Terrain::GetNumTriangles() const { return num_triangles; }

glm::vec3 Terrain::GetScale() const { return scale_; }

glm::vec3 Terrain::GetShift() const { return shift_; }

int Terrain::GetSize() const { return size_; }

std::vector<float> Terrain::GetVertices() const { return vertices_; }

int Terrain::GetWidth() const { return width_; }

glm::vec3 Terrain::Barycentric(glm::vec3 a, glm::vec3 b, glm::vec3 c,
                               glm::vec3 p) const {
  glm::vec3 u = b - a, v = c - a, w = p - a;
  float d_00 = glm::dot(u, u);
  float d_01 = glm::dot(u, v);
  float d_11 = glm::dot(v, v);
  float d_20 = glm::dot(w, u);
  float d_21 = glm::dot(w, v);
  float denominator = d_00 * d_11 - d_01 * d_01;
  float x = (d_11 * d_20 - d_01 * d_21) / denominator;
  float y = (d_00 * d_21 - d_01 * d_20) / denominator;
  float z = 1.0f - x - y;

  return {x, y, z};
}

bool Terrain::InBounds(int a, int b) const {
  return (a > -1 && a < width_) && (b > -1 && b < length_);
}

void Terrain::PopulateElements() {
  for (int i = 0; i < length_ - 1; i++) {
    for (int j = 0; j < width_; j++) {
      for (int k = 0; k < 2; k++) {
        elements_.push_back(j + width_ * (i + k * 1));
      }
    }
  }
}

void Terrain::PopulateVertices() {
  auto w = static_cast<float>(width_), l = static_cast<float>(length_);

  for (int i = 0; i < length_; i++) {
    for (int j = 0; j < width_; j++) {
      unsigned char *texel = data_ + (j + width_ * i) * channels_,
                    height = texel[0];

      float x = -w / 2.0f + w * static_cast<float>(j) / w * scale_.x - shift_.x,
            y = static_cast<float>(height) * scale_.y - shift_.y,
            z = -l / 2.0f + l * static_cast<float>(i) / l * scale_.z - shift_.z;

      vertices_.push_back(x);
      vertices_.push_back(y);
      vertices_.push_back(z);

      heights_.push_back(y);
    }
  }
}

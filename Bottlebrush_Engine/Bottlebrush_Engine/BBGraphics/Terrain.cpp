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
  InitMesh();
}

Terrain::~Terrain() {
  stbi_image_free(data_);
  data_ = nullptr;
}

glm::vec3 Terrain::GetCentre() const { return centre_; }

std::vector<unsigned> Terrain::GetElements() const { return elements_; }

float Terrain::GetHeight(float x, float z) const {
  int a = static_cast<int>(x), b = static_cast<int>(z);

  if (a < 0) a = -a;
  if (b < 0) b = -b;
  if (!InBounds(a, b)) return 0.0f;

  return vertices_.at(a + width_ * b) * scale_.y;
}

int Terrain::GetLength() const { return length_; }

int Terrain::GetNumStrips() const { return num_strips_; }

int Terrain::GetNumTriangles() const { return num_triangles; }

int Terrain::GetSize() const { return size_; }

std::vector<float> Terrain::GetVertices() const { return vertices_; }

int Terrain::GetWidth() const { return width_; }

bool Terrain::InBounds(int a, int b) const {
  auto w = static_cast<int>(width_ / 2), l = static_cast<int>(length_ / 2);
  return (a > -w && a < w) && (b > -l && b < l);
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
    }
  }
}

void Terrain::InitMesh() { 
    std::vector<unsigned int> layout;
  layout.push_back(3); // 3 elements for position
  mesh_ = GraphicsFactory<GraphicsAPI::OpenGL>::CreateMesh();
  mesh_->CreateMesh(vertices_, elements_, layout);
}

std::unique_ptr<Mesh> &Terrain::GetMesh() { return mesh_; }

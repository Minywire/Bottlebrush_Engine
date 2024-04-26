#include "Terrain.h"

Terrain::Terrain(const std::string &heightmap, glm::vec3 scale,
                 glm::vec3 shift) {
  data_ = stbi_load(heightmap.c_str(), &width_, &depth_, &channels_, 0);

  auto w = static_cast<float>(width_), l = static_cast<float>(depth_);
  num_strips_ = depth_;
  num_triangles = width_ * 2;
  path_ = heightmap;
  scale_ = scale;
  shift_ = shift;
  size_ = width_ * depth_;
  centre_ = {(w / 2.0f * scale_.x) - shift_.x, 0.0f,
             (l / 2.0f * scale_.z) - shift_.z};

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
  auto terr_size = static_cast<float>(size_),
       grid_size = static_cast<float>(heights_.size());

  float terrain_x = (x / scale_.x) + shift_.x;
  float terrain_z = (z / scale_.z) + shift_.z;

  float grid_square_size = terr_size / (grid_size - 1);
  int grid_x = std::floor(terrain_x / grid_square_size);
  int grid_z = std::floor(terrain_z / grid_square_size);

  if (!InBounds(grid_x, grid_z)) return 0.0f;

  float coord_x = std::fmod(terrain_x, grid_square_size) / grid_square_size;
  float coord_z = std::fmod(terrain_z, grid_square_size) / grid_square_size;
  float height = 0.0f;

  if (coord_x <= 1 - coord_z) {
    glm::vec3 a = {0.0f, heights_.at(grid_x + width_ * grid_z), 0.0f},
              b = {1.0f, heights_.at((grid_x + 1) + width_ * grid_z), 0.0f},
              c = {0.0f, heights_.at(grid_x + width_ * (grid_z + 1)), 1.0f};
    glm::vec2 p = {coord_x, coord_z};
    height = Barycentric(a, b, c, p);
  } else {
    glm::vec3 a = {1.0f, heights_.at((grid_x + 1) + width_ * grid_z), 0.0f},
              b = {1.0f, heights_.at((grid_x + 1) + width_ * (grid_z + 1)),
                   1.0f},
              c = {0.0f, heights_.at(grid_x + width_ * (grid_z + 1)), 1.0f};
    glm::vec2 p = {coord_x, coord_z};
    height = Barycentric(a, b, c, p);
  }

  return height;
}

int Terrain::GetDepth() const { return depth_; }

int Terrain::GetNumStrips() const { return num_strips_; }

int Terrain::GetNumTriangles() const { return num_triangles; }

glm::vec3 Terrain::GetScale() const { return scale_; }

glm::vec3 Terrain::GetShift() const { return shift_; }

int Terrain::GetSize() const { return size_; }

std::vector<float> Terrain::GetVertices() const { return vertices_; }

int Terrain::GetWidth() const { return width_; }

bool Terrain::InBounds(int a, int b) const {
  return (a > -1 && a < width_ - 1) && (b > -1 && b < depth_ - 1);
}

void Terrain::PopulateElements() {
  for (int i = 0; i < depth_ - 1; i++) {
    for (int j = 0; j < width_; j++) {
      for (int k = 0; k < 2; k++) {
        elements_.push_back(j + width_ * (i + k * 1));
      }
    }
  }
}

void Terrain::PopulateVertices() {
  auto w = static_cast<float>(width_), d = static_cast<float>(depth_);

  for (int i = 0; i < depth_; i++) {
    for (int j = 0; j < width_; j++) {
      unsigned char *texel = data_ + (j + width_ * i) * channels_,
                    height = texel[0];

      float x = (static_cast<float>(j) * scale_.x) - shift_.x,
            y = (static_cast<float>(height) * scale_.y) - shift_.y,
            z = (static_cast<float>(i) * scale_.z) - shift_.z;

      vertices_.push_back(x);
      vertices_.push_back(y);
      vertices_.push_back(z);

      vertices_.push_back(x / w);
      vertices_.push_back(z / d);

      heights_.push_back(y);
    }
  }
}

void Terrain::InitMesh() {
  std::vector<unsigned int> layout;
  layout.push_back(3);  // 3 elements for position
  layout.push_back(2);  // 2 elements for tex coords
  mesh_ = GraphicsFactory<GraphicsAPI::OpenGL>::CreateMesh(vertices_, elements_,
                                                           "", 0, layout);
}

std::unique_ptr<Mesh> &Terrain::GetMesh() { return mesh_; }

float Barycentric(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec2 p) {
  float det = (b.z - c.z) * (a.x - c.x) + (c.x - b.x) * (a.z - c.z);
  float u = ((b.z - c.z) * (p.x - c.x) + (c.x - b.x) * (p.y - c.z)) / det;
  float v = ((c.z - a.z) * (p.x - c.x) + (a.x - c.x) * (p.y - c.z)) / det;
  float w = 1.0f - u - v;

  return u * a.y + v * b.y + w * c.y;
}

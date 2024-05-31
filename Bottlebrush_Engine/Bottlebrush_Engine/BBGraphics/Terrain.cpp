#include "Terrain.h"

void Terrain::Vert::Init(float a, float b, float c, float width, float depth,
                         glm::vec3 scale, glm::vec3 shift,
                         bool texture_stretch) {
  nrm = {0.0f, 0.0f, 0.0f};

  pos.x = Transpose(a, scale.x, shift.x);
  pos.y = Transpose(b, scale.y, shift.y);
  pos.z = Transpose(c, scale.z, shift.z);

  if (texture_stretch) {
    tex.x = a / width;
    tex.y = c / depth;
  } else {
    tex.x = Transpose(a, scale.x, shift.x) / width;
    tex.y = Transpose(c, scale.z, shift.z) / depth;
  }
}

Terrain::Terrain(const std::string &path, const std::string &texture,
                 glm::vec3 scale, glm::vec3 shift) {
  data_ = stbi_load(path.c_str(), &width_, &depth_, &channels_, 0);

  scale_ = scale;
  shift_ = shift;
  size_ = width_ * depth_;
  texture_ = texture;

  EvaluateMidpoint();
  TransposeHeights();
  PopulateVertices();
  PopulateElements();
  CalculateNormals();

  // Populate raw vert buffer
  for (auto &v : vertices_) {
    vert_buf_.push_back(v.pos.x);
    vert_buf_.push_back(v.pos.y);
    vert_buf_.push_back(v.pos.z);

    vert_buf_.push_back(v.nrm.x);
    vert_buf_.push_back(v.nrm.y);
    vert_buf_.push_back(v.nrm.z);

    vert_buf_.push_back(v.tex.x);
    vert_buf_.push_back(v.tex.y);
  }

  // Populate raw elem buffer
  for (auto &e : elements_) {
    elem_buf_.push_back(e.idx);
  }

  InitMesh();

  stbi_image_free(data_);
  data_ = nullptr;
}

glm::vec3 Terrain::GetCentre() const { return centre_; }

std::vector<unsigned int> Terrain::GetElements() const { return elem_buf_; }

float Terrain::GetHeight(float x, float z) const {
  float height = 0.0f;

  // Evaluate terrain mesh size and terrain grid size.
  auto size_m = static_cast<float>(size_),
       size_g = static_cast<float>(heights_.size() - 1);

  // Evaluate current xz-position on terrain mesh.
  float x_m = x / scale_.x;
  float z_t = z / scale_.z;

  // Evaluate grid square size and current grid location.
  float size_s = size_m / size_g;
  int x_g = std::floor(x_m / size_s);
  int z_g = std::floor(z_t / size_s);

  // Check within terrain bounds.
  if (!InBounds(x_g, z_g)) return height;

  // Evaluate x and z co-ordinates inside grid square.
  float x_c = std::fmod(x_m, size_s) / size_s;
  float z_c = std::fmod(z_t, size_s) / size_s;

  // Triangulate position using the line x = 1 - z that defines the triangles
  // in a quad.
  if (x_c <= 1 - z_c) {
    // Within the triangle x < 1 - z.
    glm::vec3 a = {0.0f, heights_.at(x_g + width_ * z_g), 0.0f},
              b = {1.0f, heights_.at((x_g + 1) + width_ * z_g), 0.0f},
              c = {0.0f, heights_.at(x_g + width_ * (z_g + 1)), 1.0f};
    glm::vec2 p = {x_c, z_c};
    height = Barycentric(a, b, c, p);
  } else {
    // Within the triangle x > 1 - z.
    glm::vec3 a = {1.0f, heights_.at((x_g + 1) + width_ * z_g), 0.0f},
              b = {1.0f, heights_.at((x_g + 1) + width_ * (z_g + 1)), 1.0f},
              c = {0.0f, heights_.at(x_g + width_ * (z_g + 1)), 1.0f};
    glm::vec2 p = {x_c, z_c};
    height = Barycentric(a, b, c, p);
  }

  return height;
}

int Terrain::GetDepth() const { return depth_; }

float Terrain::GetMaxHeight() const {
  return *std::max_element(heights_.begin(), heights_.end());
}

float Terrain::GetMinHeight() const {
  return *std::min_element(heights_.begin(), heights_.end());
}

glm::vec3 Terrain::GetScale() const { return scale_; }

glm::vec3 Terrain::GetShift() const { return shift_; }

int Terrain::GetSize() const { return size_; }

std::vector<float> Terrain::GetVertices() const { return vert_buf_; }

int Terrain::GetWidth() const { return width_; }

float Terrain::Transpose(float value, float scale, float shift) {
  return (value * scale) - shift;
}

bool Terrain::InBounds(int a, int b) const {
  return (a > -1 && a < width_ - 1) && (b > -1 && b < depth_ - 1);
}

void Terrain::CalculateNormals() {
  for (size_t i = 0; i < elements_.size(); i += 3) {
    unsigned int a = elements_.at(i).idx, b = elements_.at(i + 1).idx,
                 c = elements_.at(i + 2).idx;

    glm::vec3 u = vertices_.at(b).pos - vertices_.at(a).pos,
              v = vertices_.at(c).pos - vertices_.at(a).pos;

    glm::vec3 normal = glm::normalize(glm::cross(u, v));

    vertices_.at(a).nrm += normal;
    vertices_.at(b).nrm += normal;
    vertices_.at(c).nrm += normal;
  }

  for (auto &vert : vertices_) {
    vert.nrm = glm::normalize(vert.nrm);
  }
}

void Terrain::EvaluateMidpoint() {
  float x = Transpose(static_cast<float>(width_) / 2.0f, scale_.x, shift_.x),
        y = 0.0f,
        z = Transpose(static_cast<float>(depth_) / 2.0f, scale_.z, shift_.z);
  centre_ = {x, y, z};
}

void Terrain::PopulateElements() {
  elements_.resize(width_ * (depth_ - 1) * 6);

  int idx = 0;

  for (int i = 0; i < depth_ - 1; i++) {
    for (int j = 0; j < width_ - 1; j++) {
      unsigned int a = j + width_ * i, b = j + width_ * (i + 1),
                   c = (j + 1) + width_ * (i + 1), d = (j + 1) + width_ * i;

      elements_.at(idx++).idx = a;
      elements_.at(idx++).idx = b;
      elements_.at(idx++).idx = c;

      elements_.at(idx++).idx = a;
      elements_.at(idx++).idx = c;
      elements_.at(idx++).idx = d;
    }
  }
}

void Terrain::PopulateVertices() {
  vertices_.resize(size_ * 8);

  auto w = static_cast<float>(width_), d = static_cast<float>(depth_);
  int idx = 0;

  for (int i = 0; i < depth_; i++) {
    for (int j = 0; j < width_; j++) {
      unsigned char *texel = data_ + (j + width_ * i) * channels_;

      auto x = static_cast<float>(j), y = static_cast<float>(texel[0]),
           z = static_cast<float>(i);

      vertices_.at(idx++).Init(x, y, z, w, d, scale_, shift_, texture_stretch_);
    }
  }
}

void Terrain::TransposeHeights() {
  heights_.reserve(size_);

  for (int i = 0; i < depth_; i++) {
    for (int j = 0; j < width_; j++) {
      unsigned char *texel = data_ + (j + width_ * i) * channels_;

      auto h = static_cast<float>(texel[0]);

      heights_.push_back(Transpose(h, scale_.y, shift_.y));
    }
  }
}

void Terrain::InitMesh() {
  std::vector<unsigned int> layout;
  layout.push_back(3);  // 3 elements for position
  layout.push_back(3);  // 3 elements for normals
  layout.push_back(2);  // 2 elements for tex coords
  mesh_ = GraphicsFactory<GraphicsAPI::OpenGL>::CreateMesh(vert_buf_, elem_buf_,
                                                           texture_, 0, layout);
}

std::unique_ptr<Mesh> &Terrain::GetMesh() { return mesh_; }

float Barycentric(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec2 p) {
  float d = 1.0f / ((b.z - c.z) * (a.x - c.x) + (c.x - b.x) * (a.z - c.z));
  float u = (b.z - c.z) * (p.x - c.x) + (c.x - b.x) * (p.y - c.z) * d;
  float v = (c.z - a.z) * (p.x - c.x) + (a.x - c.x) * (p.y - c.z) * d;
  float w = 1.0f - u - v;

  return u * a.y + v * b.y + w * c.y;
}

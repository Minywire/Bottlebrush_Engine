#ifndef BOTTLEBRUSH_ENGINE_TERRAIN_H
#define BOTTLEBRUSH_ENGINE_TERRAIN_H

#include <string>
#include <vector>

#include "glm/glm.hpp"
#include "stb/stb_image.h"

class Terrain {
 public:
  Terrain() = default;
  Terrain(const std::string &heightmap, glm::vec3 scale = {1.0f, 1.0f, 1.0f},
          glm::vec3 shift = {0.0f, 0.0f, 0.0f});

  ~Terrain();

  [[nodiscard]] glm::vec3 GetCentre() const;
  [[nodiscard]] std::vector<unsigned> GetElements() const;
  [[nodiscard]] float GetHeight(float x, float z) const;
  [[nodiscard]] int GetLength() const;
  [[nodiscard]] int GetNumStrips() const;
  [[nodiscard]] int GetNumTriangles() const;
  [[nodiscard]] glm::vec3 GetScale() const;
  [[nodiscard]] glm::vec3 GetShift() const;
  [[nodiscard]] int GetSize() const;
  [[nodiscard]] std::vector<float> GetVertices() const;
  [[nodiscard]] int GetWidth() const;

 private:
  [[nodiscard]] glm::vec3 Barycentric(glm::vec3 a, glm::vec3 b, glm::vec3 c,
                                      glm::vec3 p) const;
  [[nodiscard]] bool InBounds(int a, int b) const;
  void PopulateElements();
  void PopulateVertices();

  glm::vec3 centre_;
  int channels_;
  unsigned char *data_;
  std::vector<unsigned> elements_;
  std::vector<float> heights_;
  int length_;
  int num_strips_;
  int num_triangles;
  std::string path_;
  glm::vec3 scale_;
  glm::vec3 shift_;
  int size_;
  std::vector<float> vertices_;
  int width_;
};

#endif  // BOTTLEBRUSH_ENGINE_TERRAIN_H

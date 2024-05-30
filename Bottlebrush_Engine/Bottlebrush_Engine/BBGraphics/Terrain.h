#ifndef BOTTLEBRUSH_ENGINE_TERRAIN_H
#define BOTTLEBRUSH_ENGINE_TERRAIN_H

#include <memory>
#include <string>
#include <vector>

#include "GraphicsFactory.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "stb/stb_image.h"

/// @class Terrain
/// @brief The \c Terrain class encapsulates a 3D heightmap-based terrain.
///
/// The \c Terrain class is used to represent a three-dimensional terrain that
/// is based on a two-dimensional grayscale heightmap image. The class does not
/// currently support terrain generation algorithms.
/// <p>
/// The class constructor generates a three-dimensional terrain based on the
/// grayscale heightmap provided by the \c heightmap parameter. The heightmap
/// scale and shift in each direction may be optionally provided by specifying
/// the \c scale and \c shift parameters, respectively.
/// @authors Alan Brunet, Jaiden di Lanzo, Marco Garzon Lara
class Terrain {
  struct Elem {
    unsigned int idx;
  };

  struct Vert {
    void Init(float a, float b, float c, float width, float depth,
              glm::vec3 scale, glm::vec3 shift, bool texture_stretch);

    glm::vec3 nrm;
    glm::vec3 pos;
    glm::vec2 tex;
  };

 public:
  Terrain(const std::string &path, const std::string &texture,
          glm::vec3 scale = {1.0f, 1.0f, 1.0f},
          glm::vec3 shift = {0.0f, 0.0f, 0.0f});

  /// @brief Gets the terrain centre point.
  /// <p>
  /// The \c GetCentre function retrieves the centre point of the generated
  /// terrain mesh.
  /// <p>
  /// The return value is a three-dimensional vector object representing the
  /// terrain central point.
  /// @returns A three-dimensional vector object that represents the terrain
  /// centre point.
  [[nodiscard]] glm::vec3 GetCentre() const;

  /// @brief Gets the element index list that describes the vertex indices of
  /// the generated terrain.
  /// <p>
  /// The \c GetElements function retrieves the generated list of vertex indices
  /// for the generated terrain mesh.
  /// <p>
  /// The return value is a vector container object containing the index
  /// positions describing the vertex positions for the generated terrain.
  /// @returns A vector container object that represents the terrain vertex
  /// indices.
  [[nodiscard]] std::vector<unsigned int> GetElements() const;

  /// @brief Gets the height value at the given \a x and \a z co-ordinates.
  /// <p>
  /// The \c GetHeight function evaluates the height of the terrain in the \a y
  /// directional plane at the given \a x and \a z co-ordinates. The values
  /// supplied by the \c x and \c z parameters should be in local positional
  /// space.
  /// <p>
  /// The height is evaluated using the barycentric co-ordinate method to obtain
  /// the local cell position within a grid, and thus obtain the triangulated
  /// height value.
  /// <p>
  /// The return value is a real-valued number representing the terrain height
  /// at the given \a x and \a z co-ordinates.
  /// @returns A real-valued number that represents the terrain height.
  [[nodiscard]] float GetHeight(float x, float z) const;

  /// @brief Gets the depth of the terrain.
  /// <p>
  /// The \c GetDepth function retrieves the terrain length in the \a z
  /// directional plane.
  /// <p>
  /// The return value is an integer value specifying the terrain length.
  /// @returns An integer specifying the terrain length.
  [[nodiscard]] int GetDepth() const;

  [[nodiscard]] float GetMaxHeight() const;
  [[nodiscard]] float GetMinHeight() const;

  /// @brief Gets the terrain scaling factors.
  /// <p>
  /// The \c GetScale function retrieves the scaling factors of the generated
  /// terrain mesh.
  /// <p>
  /// The return value is a three-dimensional vector object representing the
  /// scale in each of the \a x, \a y, and \a z directional planes.
  /// @returns A three-dimensional vector object that represents the terrain
  /// scale.
  [[nodiscard]] glm::vec3 GetScale() const;

  /// @brief Gets the terrain shifting factors.
  /// <p>
  /// The \c GetShift function retrieves the shifting factors of the generated
  /// terrain mesh.
  /// <p>
  /// The return value is a three-dimensional vector object representing the
  /// shift in each of the \a x, \a y, and \a z directional planes.
  /// @returns A three-dimensional vector object that represents the terrain
  /// shift.
  [[nodiscard]] glm::vec3 GetShift() const;

  /// @brief Gets the total size of the terrain.
  /// <p>
  /// The \c GetSize function retrieves the total terrain size. The total
  /// terrain size is equal to its width multiplied by its length.
  /// <p>
  /// The return value is an integer value specifying the total terrain size.
  /// @returns An integer specifying the total terrain size.
  [[nodiscard]] int GetSize() const;

  /// @brief Gets the vertex list that describes vertices of the generated
  /// terrain.
  /// <p>
  /// The \c GetVertices function retrieves the generated list of vertices for
  /// the generated terrain mesh.
  /// <p>
  /// The return value is a vector container object containing the \a x, \a y,
  /// and \a z vertex positions that compose the generated terrain mesh.
  /// @returns A vector container object that represents the terrain vertices.
  [[nodiscard]] std::vector<float> GetVertices() const;

  /// @brief Gets the width of the terrain.
  /// <p>
  /// The \c GetWidth function retrieves the terrain length in the \a x
  /// directional plane.
  /// <p>
  /// The return value is an integer value specifying the terrain width.
  /// @returns An integer specifying the terrain width.
  [[nodiscard]] int GetWidth() const;

  /// @author Alan
  /// @brief Gets the terrain mesh
  [[nodiscard]] std::unique_ptr<Mesh> &GetMesh();

  bool texture_stretch_ = false;

 private:
  static float Transpose(float value, float scale, float shift);

  [[nodiscard]] bool InBounds(int a, int b) const;
  void CalculateNormals();
  void EvaluateMidpoint();
  void PopulateElements();
  void PopulateVertices();
  void TransposeHeights();

  /// @author Alan
  /// @brief Creates the mesh on the Graphics API format
  void InitMesh();

  glm::vec3 centre_;
  int channels_;
  unsigned char *data_;
  std::vector<Elem> elements_;
  std::vector<float> heights_;
  int depth_;
  std::unique_ptr<Mesh> mesh_;
  glm::vec3 scale_;
  glm::vec3 shift_;
  int size_;
  std::string texture_;
  std::vector<Vert> vertices_;
  int width_;

  // Raw buffers
  std::vector<unsigned int> elem_buf_;
  std::vector<float> vert_buf_;
};

float Barycentric(glm::vec3 a, glm::vec3 b, glm::vec3 c, glm::vec2 p);

#endif  // BOTTLEBRUSH_ENGINE_TERRAIN_H

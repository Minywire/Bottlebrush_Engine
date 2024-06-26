#pragma once

// magic number "IDP2" or 844121161
#define MD2_IDENT       (('2'<<24) + ('P'<<16) + ('D'<<8) + 'I')

// model version
#define MD2_VERSION     8

#include <vector>
#include <memory>
#include <map>
#include <unordered_map>
#include <filesystem>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "GraphicsFactory.h"

typedef struct
{
    float x;
    float y;
    float z;
} vec3_md2;

// vertex
typedef struct
{
    unsigned char   v[3];                // compressed vertex (x, y, z) coordinates
    unsigned char   lightnormalindex;    // index to a normal vector for the lighting

} vertex_md2;

typedef struct
{
    char name[64];                      // texture file name
} skin_md2;

// texture coordinates
typedef struct
{
    short    s;
    short    t;

} texCoord_md2;

// frame
typedef struct
{
    vec3_md2        scale;          // scale values
    vec3_md2        translate;      // translation vector
    char            name[16];       // frame name
    std::vector<vertex_md2> verts;  // first vertex of this frame

} frame_md2;

// triangle
typedef struct
{
    unsigned short   index_xyz[3];    // indexes to triangle's vertices
    unsigned short   index_st[3];     // indexes to vertices' texture coorinates

} triangle_md2;

typedef struct
{
    unsigned int startIndex;
    unsigned int endIndex;
} anim_md2;

struct MD2Header {
    int ID;                 // Magic number ("IDP2") - Identifies the file as an MD2 model
    int version;            // Version number (8) - MD2 file format version

    int skinWidth;          // Width of the texture
    int skinHeight;         // Height of the texture
    int frameSize;          // Size of each frame in bytes

    int numSkins;           // Number of skins
    int numVertices;        // Number of vertices per frame
    int numTexCoords;       // Number of texture coordinates
    int numTriangles;       // Number of triangles
    int numGlCommands;      // Number of OpenGL commands
    int numFrames;          // Number of frames

    int offsetSkins;        // Offset to skin data
    int offsetTexCoords;    // Offset to texture coordinate data
    int offsetTriangles;    // Offset to triangle data
    int offsetFrames;       // Offset to frame data
    int offsetGlCommands;   // Offset to OpenGL command data
    int offsetEnd;          // Offset to end of file
};

class MD2Model {
public:
    MD2Model(const std::string& filename, const std::string& texturefile);
    
    void displayModelDetails();
    void displayAnimNames();
    int GetSpecificAnim(std::string animName);
    std::string GetSpecificAnim(int animIndex);

    /**
    * @return List containing all animation names
    */
    std::vector<std::string> AnimationNames();

    /**
     * @reutrn Number of animations
     */
    int getNumAnims() { return m_animation.size(); }

    /**
     * @return The container with all of the animation state data for MD2
     */
    std::map<std::string, anim_md2>& getAnimations() { return m_animation; }

    /**
     * @return The header containing all of the metadata for a loaded MD2 file
     */
    std::unique_ptr<MD2Header>& GetHeader() { return m_header; }

    /**
     * @return The container containing all vertex array objects
     */
    const std::vector<unsigned int> & returnVaos() const;

    /**
     * @return The number of faces in the loaded MD2 model
     */
    const int getNumTris() const { return m_header->numTriangles * 3; }

    /**
     *@brief binds the MD2 model texture
     */
    void setTexture() const;
   private:
    /**
     *@brief Loads an MD2 model from a specified file path
     * @param filename The MD2 model file name/path to read from
     * @return True if file loading succeeds
     */
    bool LoadModel(std::string filename);
    /**
     *@brief Loads an MD2 texture from a specified file path
     * @param filename The png file name/path to read from
     *  @return True if file loading succeeds
     */
    bool LoadTexture(std::string texturefile);
    /**
     *@brief sets up all specific Core-profile OpenGL data needed for MD2 use in modern render engines
     */
    void InitBuffers();

    template<typename T>
    static std::vector<T> ReadDataFromFile(std::ifstream& file, int dataSize, int offset);

    // MD2 file contents
    std::unique_ptr<MD2Header> m_header;                    /// header file with details about the mesh
    std::vector<skin_md2> m_skins;                          /// Skin names
    std::vector<texCoord_md2> m_texCoords;                  /// TexCoords
    std::vector<triangle_md2> m_triIndex;                   /// triangle indices

    std::map<std::string, anim_md2> m_animation;            /// map for animation start and end
    std::map<int, std::pair<std::string, std::vector<vec3_md2>>> m_frameVerts;      // Vertex data per frame

    // OpenGL variables
    std::unique_ptr<Texture> m_texture;                     /// texture buffer
    std::vector<float> m_vertices;                          /// stream of vertex data to upload

    std::vector<unsigned int> m_vertexArray;                /// vertex array object
};

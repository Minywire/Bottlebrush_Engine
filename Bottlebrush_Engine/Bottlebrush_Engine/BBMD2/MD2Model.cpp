#include "MD2Model.h"
#include "glad/glad.h"

#include <iostream>
#include <fstream>

MD2Model::MD2Model(std::string filename, std::string texturefile) 
    : m_currentFrame(0)
{
    if (!LoadModel(filename))
    {
        std::cout << "Could not load M2D model" << std::endl;
        return;
    }
    
    if (!LoadTexture(texturefile))
    {
        std::cout << "Could not load Texture for MD2 model" << std::endl;
        return;
    }
    
    InitBuffers();
}

bool MD2Model::LoadModel(std::string filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }

    MD2Header header;
    file.read(reinterpret_cast<char*>(&header), sizeof(MD2Header));

    // Check if the magic number matches the expected value
    if (header.ID != MD2_IDENT || header.version != MD2_VERSION) {
        std::cerr << "Invalid MD2 file format." << std::endl;
        return false;
    }

    // Populate model information from the header
    m_header = std::make_unique<MD2Header>(header);
    displayModelDetails(); // print details

    // resize member variables accordingly
    m_skins.resize(header.numSkins);
    m_texCoords.resize(header.numTexCoords);
    m_triIndex.resize(header.numTriangles);

    // read the data into their memory
    m_skins = ReadDataFromFile<skin_md2>(file, m_skins.size(), header.offsetSkins);
    m_texCoords = ReadDataFromFile<texCoord_md2>(file, m_texCoords.size(), header.offsetTexCoords);
    m_triIndex = ReadDataFromFile <triangle_md2>(file, m_triIndex.size(), header.offsetTriangles);
    
    // local variables for loading, gets offloaded to m_frameVerts
    std::vector<frame_md2> frameData; // Frame data
    frameData.resize(header.numFrames);
    // read frame data for each animation
    file.seekg(header.offsetFrames, std::ios::beg);
    for (int i = 0; i < header.numFrames; i++)
    {
        frameData[i].verts.resize(header.numVertices);
        
        file.read(reinterpret_cast<char*>(&frameData[i].scale), 3 * sizeof(float));
        file.read(reinterpret_cast<char*>(&frameData[i].translate), 3 * sizeof(float));
        file.read(reinterpret_cast<char*>(&frameData[i].name), 16 * sizeof(char));
        for (int j = 0; j < header.numVertices; j++)
        {
            file.read(reinterpret_cast<char*>(&frameData[i].verts[j]), sizeof(vertex_md2));
        }
        
    }

    // local variables for loading, gets offloaded to m_frameVerts
    std::vector<vec3_md2> trueVerticesMD2;
    trueVerticesMD2.resize(header.numVertices);
    // variables for m_animation assign
    int startAnim = 0;
    
    // decompress true vertex positions
    for (int anim = 0; anim < header.numFrames; anim++)
    {
        for (int vert = 0; vert < header.numVertices; vert++)
        {

            trueVerticesMD2[vert].x = frameData[anim].scale.x * frameData[anim].verts[vert].v[0] + frameData[anim].translate.x;
            trueVerticesMD2[vert].y = frameData[anim].scale.y * frameData[anim].verts[vert].v[1] + frameData[anim].translate.y;
            trueVerticesMD2[vert].z = frameData[anim].scale.z * frameData[anim].verts[vert].v[2] + frameData[anim].translate.z;
        }


        // allocate m_animation
        std::string animName = "";
        std::string frameAnim = frameData[anim].name;
        // split string from numbers
        for (char c : frameAnim)
        {
            if (!std::isdigit(c)) animName += c;
        }

        // populate frame vert data
        m_frameVerts[anim] = { animName, trueVerticesMD2 };

        // add to m_animation if animName doesnt exists, else increment endIndex
        if (m_animation.find(animName) == m_animation.end())
        {
            startAnim = anim;
            m_animation.emplace(animName, anim_md2(startAnim, startAnim));
        }
        else
        {
            m_animation[animName].endIndex++;
        }
    }

    file.close();
}

bool MD2Model::LoadTexture(std::string texturefile)
{
    m_texture.CreateTexture(texturefile);
    return true;
}

template<typename T>
std::vector<T> MD2Model::ReadDataFromFile(std::ifstream& file, int dataSize, int offset) {
    std::vector<T> data(dataSize);
    file.seekg(offset, std::ios::beg);
    file.read(reinterpret_cast<char*>(data.data()), dataSize * sizeof(T));
    return (data);
}

void MD2Model::displayModelDetails()
{
    std::cout << "numFrames: " << m_header->numFrames << std::endl;
    std::cout << "numSkins: " << m_header->numSkins << std::endl;
    std::cout << "numVertices: " << m_header->numVertices << std::endl;
    std::cout << "numTexCoords: " << m_header->numTexCoords << std::endl;
    std::cout << "numTriangles: " << m_header->numTriangles << std::endl;
}

void MD2Model::displayAnimNames()
{
    int count = 0;
    for (auto anim : m_animation)
    {
        std::cout << "Anim " << count << ": " << anim.first << std::endl;
        count++;
    }
}

int MD2Model::GetSpecificAnim(std::string animName)
{
    int count = 0;
    for (auto anim : m_animation)
    {
        if (anim.first.compare(animName) == 0) break;
        count++;
    }
    return count;
}

std::string MD2Model::GetSpecificAnim(int animIndex)
{
    std::map<std::string, anim_md2>::iterator it = m_animation.begin();
    for (int i = 0; i < animIndex; i++)
    {
        it++;
    }

    if (it == m_animation.end())
    {
        it = m_animation.begin();
    }

    return it->first;
}

void MD2Model::InitBuffers()
{
    int nextFrameIndex = 0;
    int maxFrame = m_header->numFrames;
    bool endOfAnim = false;

    // used for looping next frame index back to start of animation
    std::string currentAnimName;
    std::string nextAnimName;

    // per frame
    for (int frame = 0; frame < maxFrame; frame++)
    {
        currentAnimName = m_frameVerts[frame].first;
        nextAnimName = m_frameVerts[frame+1].first;

        // loop the next frame to be start of the animation
        // if this frame's name is the same as before
        if (currentAnimName.compare(nextAnimName) == 0)
        {
            nextFrameIndex = nextFrameIndex == maxFrame - 1 ? 0 : nextFrameIndex + 1;
        }
        // if this frame's name is different
        else
        {
            // loop back to the start frame of this animation
            nextFrameIndex = m_animation[currentAnimName].startIndex;
            endOfAnim = true; // to switch it back to the end once data is emplaced
        }

        // per face
        for (int index = 0; index < m_header->numTriangles; index++)
        {
            // per vertex
            for (int vertex = 0; vertex < 3; vertex++)
            {
                // Current frame
                m_vertices.emplace_back(m_frameVerts[frame].second[m_triIndex[index].index_xyz[vertex]].x);
                m_vertices.emplace_back(m_frameVerts[frame].second[m_triIndex[index].index_xyz[vertex]].y);
                m_vertices.emplace_back(m_frameVerts[frame].second[m_triIndex[index].index_xyz[vertex]].z);

                // Next frame
                m_vertices.emplace_back(m_frameVerts[nextFrameIndex].second[m_triIndex[index].index_xyz[vertex]].x);
                m_vertices.emplace_back(m_frameVerts[nextFrameIndex].second[m_triIndex[index].index_xyz[vertex]].y);
                m_vertices.emplace_back(m_frameVerts[nextFrameIndex].second[m_triIndex[index].index_xyz[vertex]].z);

                // Tex coords
                m_vertices.emplace_back(m_texCoords[m_triIndex[index].index_st[vertex]].s / (float) m_header->skinWidth);
                m_vertices.emplace_back(m_texCoords[m_triIndex[index].index_st[vertex]].t / (float) m_header->skinHeight);

            }
        }

        // make next frame index back to end of animation
        if (endOfAnim)
        {
            nextFrameIndex = frame + 1;
            endOfAnim = false;
        }
    }


    unsigned int vao, vbo;
    for (int i = 0; i < maxFrame; i++)
    {
        glGenBuffers(1, &vbo);
        glGenVertexArrays(1, &vao);

        // Bind vertex array object
        glBindVertexArray(vao);

        // Bind vertex buffer objects
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        // upload vertex data
        glBufferData(GL_ARRAY_BUFFER,
            m_header->numTriangles * 8 * 3 * sizeof(float), // size of vertices buffer = number of faces * 8 floats * 3 vertex
            &m_vertices[i * m_header->numTriangles * 8 * 3], // pointer to the first element
            GL_STATIC_DRAW
        );

        // Set vertex attribute pointers
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(0)); // positions
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float))); // next position
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), reinterpret_cast<void*>(6 * sizeof(float))); // tex coords

        //m_vertexBuffer.emplace_back(vbo);
        m_vertexArray.emplace_back(vao);

        //unbind vbo
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        //unbind vao
        glBindVertexArray(0);
    }

    //unbind vao
    glBindVertexArray(0);
    
}

int MD2Model::GetAnimationCurrentFrame(int animIndex, float interpolation)
{
    std::string animName = GetSpecificAnim(animIndex);
    
    if (m_currentFrame > m_animation[animName].endIndex || m_currentFrame < m_animation[animName].startIndex)
        m_currentFrame = m_animation[animName].startIndex;

    if (interpolation >= 1.0f && m_currentFrame <= m_animation[animName].endIndex)
        m_currentFrame++;

    return m_currentFrame;
}

std::vector<std::string> MD2Model::AnimationNames()
{
    std::vector<std::string> anims;
    for (auto a : m_animation)
    {
        anims.emplace_back(a.first);
    }
    return anims;
}

const std::vector<unsigned int>& MD2Model::returnVaos() const
{
    return m_vertexArray;
}

void MD2Model::setTexture() const
{ 
    m_texture.Bind();
}

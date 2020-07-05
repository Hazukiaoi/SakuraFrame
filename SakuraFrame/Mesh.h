#pragma once

#include "Type.h"
#include "Bound.h"

#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;
namespace Render
{
    typedef struct VertexData
    {

        /*
        4byte                                   int                     顶点数
        12 * 3 + 16 + 8 * 2 byte * vertexCount  3 Vec3 + Vec4 + 2 Vec2  [顶点坐标 顶点色 法线 切线 UV0 UV1] * 顶点总数
        4byte                                   int                     索引数
        4byte * triangles                       int[]                   顶点索引

        */
    public:
        Vector3 vertex;
        Color color;
        Vector3 normal;
        Vector4 tangent;
        Vector2 uv0, uv1;

    };

    struct Mesh
    {
    public:
        unsigned int vertexCount;
        unsigned int trianglesCount;

        VertexData* vertices;
        unsigned int* triangles;
        unsigned int VAO, VBO, EBO;

        Bound bound;

    public:

        Mesh();
        ~Mesh();
        void LoadMesh(const char* path);
        void setupMesh();
    };
}
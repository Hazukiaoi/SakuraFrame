#pragma once

#include "Type.h"
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;

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
    unsigned int *triangles;
    unsigned int VAO, VBO, EBO;

public:

    Mesh()
    {
        vertexCount = 0;
        trianglesCount = 0;
    }

    ~Mesh()
    {
        free(vertices);
        free(triangles);

        cout << "relesed" << endl;
    }

    void LoadMesh(const char* path)
    {
        fstream fs(path, ios::in | ios::binary);

        //vertexCount = (int)malloc(4);

        //int* vetCount = (int*)malloc(4);
        fs.read((char*)&vertexCount, 4);

        int dataLength = vertexCount * (sizeof(VertexData));
        vertices = (VertexData*)malloc(dataLength);
        fs.read((char*)vertices, dataLength);


        //int* trisCount = (int*)malloc(4);
        fs.read((char*)&trianglesCount, 4);

        triangles = (unsigned int*)malloc(trianglesCount * sizeof(unsigned int));
        fs.read((char*)triangles, trianglesCount * sizeof(unsigned int));

        fs.close();
    }

    void setupMesh()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData) * vertexCount, vertices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, trianglesCount * sizeof(unsigned int), triangles, GL_STATIC_DRAW);

        /*
            Vector3 vertex;
            Color color;
            Vector3 normal;
            Vector4 tangent;
            Vector2 uv0, uv1;
        */

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(sizeof(Vector3)));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(sizeof(Vector3) + sizeof(Color)));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(sizeof(Vector3) + sizeof(Color) + sizeof(Vector3)));
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(sizeof(Vector3) + sizeof(Color) + sizeof(Vector3) + sizeof(Vector4)));
        glEnableVertexAttribArray(4);
        glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(sizeof(Vector3) + sizeof(Color) + sizeof(Vector3) + sizeof(Vector4)+ sizeof(Vector2)));
        glEnableVertexAttribArray(5);

        //解绑VAO VBO EBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

    }
};
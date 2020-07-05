#include "Mesh.h"
namespace Render
{

    Mesh::Mesh()
    {
        vertexCount = 0;
        trianglesCount = 0;
    }

    Mesh::~Mesh()
    {
        free(vertices);
        free(triangles);

        cout << "relesed" << endl;
    }

    void Mesh::LoadMesh(const char* path)
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

        //读取模型的Bound参数
        fs.read((char*)&bound, sizeof(Bound));

        fs.close();
    }

    void Mesh::setupMesh()
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
        glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)(sizeof(Vector3) + sizeof(Color) + sizeof(Vector3) + sizeof(Vector4) + sizeof(Vector2)));
        glEnableVertexAttribArray(5);

        //解绑VAO VBO EBO
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

    }
}
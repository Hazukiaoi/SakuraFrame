#pragma once

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <string>
#include <unordered_map>

#include "Type.h"
#include "Texture.h"
#include "BaseDefine.h"

namespace Render
{
    class Shader
    {
    public:
        unsigned int ID;
        const char* mShaderName;

        Shader(const GLchar* vertPath, const GLchar* fragPath, const char* shaderName);

        void use();


        void SetFloat(const GLchar* name, float value) const;

        void SetBool(const GLchar* name, bool value) const;

        void SetColor(const GLchar* name, glm::vec4& value) const;

        void SetVector3(const GLchar* name, glm::vec3& value) const;

        void SetInt(const GLchar* name, int value) const;

        void SetTexture(const GLchar* name, Texture& value) const;

        void SetMatrix4x4(const GLchar* name, Matrix4x4 value) const;

    };


    class ShaderLibrary
    {
    public:

        Ref<Shader> Create(const std::string& name, const std::string& vertSrc, const std::string& fragSrc);

        Ref<Shader> Get(const std::string& name);

    private:
        std::unordered_map<std::string, Ref<Shader>> m_Shaders;
    };
}
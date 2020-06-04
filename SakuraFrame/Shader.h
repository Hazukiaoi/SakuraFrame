#pragma once

#include <GL/glew.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "Type.h"
#include "Texture.h"

class Shader
{
public:
    unsigned int ID;

    Shader(const GLchar* vertPath, const GLchar* fragPath)
    {
        //------------------��ȡShader�ļ�
        std::string vertCode;
        std::string fragCode;

        std::ifstream vertFile;
        std::ifstream fragFile;

        std::cout << vertPath << std::endl;
        std::cout << fragPath << std::endl;

        //ȷ�������׳��쳣 
        vertFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        fragFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            vertFile.open(vertPath);
            fragFile.open(fragPath);

            std::stringstream vShaderStream, fShaderStream;

            //�ļ��������ַ�����
            vShaderStream << vertFile.rdbuf();
            fShaderStream << fragFile.rdbuf();

            //�ر��ļ���
            vertFile.close();
            fragFile.close();

            vertCode = vShaderStream.str();
            fragCode = fShaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
        }

        const char* vShaderCode = vertCode.c_str();
        const char* fShaderCode = fragCode.c_str();

        //===============

        GLint success;
        GLuint vertShaderID, fragShaderID;
        char infoLog[512];

        //�����ͱ���Shader
        vertShaderID = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertShaderID, 1, &vShaderCode, NULL);
        glCompileShader(vertShaderID);
        // ��ӡ�����������еĻ���
        glGetShaderiv(vertShaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "Vertex Shader Compile Error : " << infoLog << std::endl;
        }

        fragShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragShaderID, 1, &fShaderCode, NULL);
        glCompileShader(fragShaderID);
        glGetShaderiv(fragShaderID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "Fragment Shader Compile Error : " << infoLog << std::endl;
        }

        //����Shader
        ID = glCreateProgram();
        glAttachShader(ID, vertShaderID);
        glAttachShader(ID, fragShaderID);
        glLinkProgram(ID);

        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cout << "Shader Link Error : " << infoLog << std::endl;
        }

        glDeleteShader(vertShaderID);
        glDeleteShader(fragShaderID);
    }

    void use() 
    {
        glUseProgram(ID);
    }

    void SetFloat(const GLchar* name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name), value);
    }
    void SetBool(const GLchar* name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name), value);
    }
    void SetColor(const GLchar* name, glm::vec3 &value) const
    {
        glUniform3fv(glGetUniformLocation(ID, name), 1, &value[0]);
    }
    void SetVector3(const GLchar* name, glm::vec3 &value) const
    {
        glUniform3fv(glGetUniformLocation(ID, name), 1, &value[0]);
    }
    void SetInt(const GLchar* name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name), value);
    }
    void SetTexture(const GLchar* name, Texture &value) const
    {
        glUniform1i(glGetUniformLocation(ID, name), value.texture);
    }
    void SetMatrix4x4(const GLchar* name, Matrix4x4 value) const
    {
        glUniformMatrix4fv(
            glGetUniformLocation(ID, name),     //ID
            1,                                  //����һ������
            GL_FALSE,                           //��Ϊglm����������������Բ���Ҫת��
            glm::value_ptr(value));             //��Ϊglm������ݱ�����shader��Ҫ�ģ���������value_ptrת��
    }
};

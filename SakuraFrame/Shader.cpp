#include "Shader.h"

using Render::Shader;

Shader::Shader(const GLchar* vertPath, const GLchar* fragPath, const char* shaderName) : mShaderName(shaderName)
{
    //------------------读取Shader文件
    std::string vertCode;
    std::string fragCode;

    std::ifstream vertFile;
    std::ifstream fragFile;

    std::cout << vertPath << std::endl;
    std::cout << fragPath << std::endl;

    //确保可以抛出异常 
    vertFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        vertFile.open(vertPath);
        fragFile.open(fragPath);

        std::stringstream vShaderStream, fShaderStream;

        //文件流传入字符串流
        vShaderStream << vertFile.rdbuf();
        fShaderStream << fragFile.rdbuf();

        //关闭文件流
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

    //创建和编译Shader
    vertShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShaderID, 1, &vShaderCode, NULL);
    glCompileShader(vertShaderID);
    // 打印编译错误（如果有的话）
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

    //链接Shader
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

void Shader::use()
{
    glUseProgram(ID);

}

void Shader::SetFloat(const GLchar* name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name), value);
}
void Shader::SetBool(const GLchar* name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name), value);
}
void Shader::SetColor(const GLchar* name, glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(ID, name), 1, &value[0]);
}
void Shader::SetVector3(const GLchar* name, glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(ID, name), 1, &value[0]);
}
void Shader::SetInt(const GLchar* name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name), value);
}
void Shader::SetTexture(const GLchar* name, Texture& value) const
{
    glUniform1i(glGetUniformLocation(ID, name), value.texture);
}
void Shader::SetMatrix4x4(const GLchar* name, Matrix4x4 value) const
{
    glUniformMatrix4fv(
        glGetUniformLocation(ID, name),     //ID
        1,                                  //传入一个矩阵
        GL_FALSE,                           //因为glm本身就是列主序，所以不需要转置
        glm::value_ptr(value));             //因为glm存的数据本身不是shader需要的，所以先用value_ptr转换
}

using Render::ShaderLibrary;
Ref<Shader> ShaderLibrary::Create(const std::string& name, const std::string& vertSrc, const std::string& fragSrc)
{
    if (m_Shaders.find(name) == m_Shaders.end())
    {
        Ref<Shader> _shader = CreateRef<Shader>(vertSrc.c_str(), fragSrc.c_str(), name.c_str());
        m_Shaders[name] = _shader;
    }
    return m_Shaders[name];
}

Ref<Shader> ShaderLibrary::Get(const std::string& name)
{
    if (m_Shaders.find(name) == m_Shaders.end())
    {
        std::cout << "Can't find shader" << std::endl;
        return nullptr;
    }
    else
    {
        return m_Shaders[name];
    }
}
#pragma once

#include <iostream>
#include "stb_image.h"
#include "GL/glew.h"

struct Texture
{
public:
    int width, height, nrChannels;
    unsigned char *data;
    unsigned int texture;

    Texture() {};
    Texture(int width, int height) :width(width), height(height) 
    {
    }

    ~Texture()
    {
        if (data)
            stbi_image_free(data);
    }
};

struct Texture2D : Texture
{
public:
    Texture2D() {};
    Texture2D(int width, int height)
    {
        this->width = width;
        this->height = height;
    }

    Texture2D(const char* path)
    {
        unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    }

    void SetUp()
    {
        glGenTextures(1, &texture);
        glActiveTexture(GL_TEXTURE0);           //把激活Texture0位置，
        glBindTexture(GL_TEXTURE_2D, texture); //把当前操作纹理绑定到GL_TEXTURE_2D槽上，因为上面激活了Texture0位置，所以此时绑定操作此纹理都会放到Texture0上
        // 为当前绑定的纹理对象设置环绕、过滤方式
        SetUp(GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);

        //绑定数据到目标
        if (data)
        {
            glTexImage2D(
                GL_TEXTURE_2D,      //绑定的位置
                0,                  //Mipmap级数0，基础级数
                GL_RGB,             //纹理储存格式
                width,              //宽
                height,             //高
                0,                  //历史遗留问题，肯定填0
                GL_RGB,             //原图格式，此处使用RGB加载
                GL_UNSIGNED_BYTE,   //储存为char(byte)数组 （上面读入的）
                data);

            glGenerateMipmap(GL_TEXTURE_2D);    //生成mipmap
        }
        else
        {
            std::cout << "Faild To Load Texture" << std::endl;
        }
    }

    void SetUp(int warp_s_type, int warp_t_type, int min_filter, int mag_filter)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, warp_s_type);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, warp_t_type);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
    }

    ~Texture2D()
    {
        if(data)
            stbi_image_free(data);
    }
};
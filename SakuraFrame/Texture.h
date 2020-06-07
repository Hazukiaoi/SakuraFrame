#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
//#include "stb_image.h"
#include "GL/glew.h"

struct Texture
{
public:
    int width, height, nrChannels;
    bool mipmap = true;
    unsigned char *data;
    unsigned int texture;

    Texture() {};
    Texture(int width, int height) :width(width), height(height) 
    {
    }

    ~Texture()
    {
        if (data)
            //stbi_image_free(data);
            free(data);
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

    //从路径读取二进制格式 
    //4byte     width
    //4byte     height
    //4byte     channels
    //toEnd     datas 
    Texture2D(const char* path)
    {
        std::fstream readImg(path, std::ios::in | std::ios::binary);
        readImg.read((char*)&width, 4);
        readImg.read((char*)&height, 4);
        readImg.read((char*)&nrChannels, 4);

        int len = width * height * nrChannels;

        unsigned char* img = (unsigned char*)malloc(len);
        readImg.read((char*)img, len);
        readImg.close();
        //unsigned char *data = stbi_load(path, &width, &height, &nrChannels, 0);
    }

    void BindTexture(GLenum channel)
    {
        glActiveTexture(channel);
        glBindTexture(GL_TEXTURE_2D, texture);
    }

    void SetUp()
    {
        glGenTextures(1, &texture);
        //glActiveTexture(GL_TEXTURE0);           //把激活Texture0位置，
        glBindTexture(GL_TEXTURE_2D, texture); //把当前操作纹理绑定到GL_TEXTURE_2D槽上
        // 为当前绑定的纹理对象设置环绕、过滤方式
        SetUp(GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);

        //绑定数据到目标
        if (data)
        {
            glTexImage2D(
                GL_TEXTURE_2D,                                  //绑定的位置
                0,                                              //Mipmap级数0，基础级数
                nrChannels > 3 ? GL_RGBA : GL_RGB,              //纹理储存格式
                width,                                          //宽
                height,                                         //高
                0,                                              //历史遗留问题，肯定填0
                nrChannels > 3 ? GL_RGBA : GL_RGB,              //原图格式，此处使用RGB加载
                GL_UNSIGNED_BYTE,                               //储存为char(byte)数组 （上面读入的）
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
            free(data);
    }
};
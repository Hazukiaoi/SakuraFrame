#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
//#include "stb_image.h"
#include "GL/glew.h"

class Texture
{
public:
    int width, height, nrChannels;
    bool mipmap = true;
    unsigned char *data = nullptr;
    unsigned int texture;

    Texture() {};
    Texture(int width, int height, int channels) :width(width), height(height), nrChannels(channels)
    {
        int len = width * height * nrChannels;
        data = (unsigned char*)malloc(len);
    }

    virtual void SetPixel(Color color, int x, int y)
    {
        if (x < 0 || x >= width || y < 0 || y >= height) return;

        int p = (x + y * height) * 3;
        data[p] = (char)int(color.r * 255.99f);
        data[p + 1] = (char)int(color.g * 255.99f);
        data[p + 2] = (char)int(color.b * 255.99f);
        if(nrChannels > 3) data[p + 3] = (char)int(color.a * 255.99f);
        
    }

    virtual void SetUp(int warp_s_type, int warp_t_type, int min_filter, int mag_filter)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, warp_s_type);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, warp_t_type);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
    }

    virtual void SetUp()
    {
        glGenTextures(1, &texture);
        //glActiveTexture(GL_TEXTURE0);           //�Ѽ���Texture0λ�ã�
        glBindTexture(GL_TEXTURE_2D, texture); //�ѵ�ǰ��������󶨵�GL_TEXTURE_2D����
        // Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
        SetUp(GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);

        //�����ݵ�Ŀ��
        if (data)
        {
            glTexImage2D(
                GL_TEXTURE_2D,                                  //�󶨵�λ��
                0,                                              //Mipmap����0����������
                nrChannels > 3 ? GL_RGBA : GL_RGB,              //�������ʽ
                width,                                          //��
                height,                                         //��
                0,                                              //��ʷ�������⣬�϶���0
                nrChannels > 3 ? GL_RGBA : GL_RGB,              //ԭͼ��ʽ���˴�ʹ��RGB����
                GL_UNSIGNED_BYTE,                               //����Ϊchar(byte)���� ���������ģ�
                data);

            glGenerateMipmap(GL_TEXTURE_2D);    //����mipmap
        }

        free(data);
        data = nullptr;
    }

    ~Texture()
    {
        std::cout << &data << std::endl;
        if (&data != nullptr)
        {
            free(data);
        }
            //stbi_image_free(data);
    }
};

class Texture2D : public Texture
{

public:
    Texture2D() {};
    Texture2D(int width, int height)
    {
        this->width = width;
        this->height = height;
    }

    //��·����ȡ�����Ƹ�ʽ 
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

        data = (unsigned char*)malloc(len);
        readImg.read((char*)data, len);
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
        //glActiveTexture(GL_TEXTURE0);           //�Ѽ���Texture0λ�ã�
        glBindTexture(GL_TEXTURE_2D, texture); //�ѵ�ǰ��������󶨵�GL_TEXTURE_2D����
        // Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
        SetUp(GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);

        //�����ݵ�Ŀ��
        if (data)
        {
            glTexImage2D(
                GL_TEXTURE_2D,                                  //�󶨵�λ��
                0,                                              //Mipmap����0����������
                nrChannels > 3 ? GL_RGBA : GL_RGB,              //�������ʽ
                width,                                          //��
                height,                                         //��
                0,                                              //��ʷ�������⣬�϶���0
                nrChannels > 3 ? GL_RGBA : GL_RGB,              //ԭͼ��ʽ���˴�ʹ��RGB����
                GL_UNSIGNED_BYTE,                               //����Ϊchar(byte)���� ���������ģ�
                data);

            glGenerateMipmap(GL_TEXTURE_2D);    //����mipmap
        }
        else
        {
            std::cout << "Faild To Load Texture" << std::endl;
        }

        free(data);
        data = nullptr;
        std::cout << "Load Texture Finish" << std::endl;
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
        //if(data)
        //    free(data);
    }
};
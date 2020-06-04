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
        glActiveTexture(GL_TEXTURE0);           //�Ѽ���Texture0λ�ã�
        glBindTexture(GL_TEXTURE_2D, texture); //�ѵ�ǰ��������󶨵�GL_TEXTURE_2D���ϣ���Ϊ���漤����Texture0λ�ã����Դ�ʱ�󶨲�����������ŵ�Texture0��
        // Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
        SetUp(GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);

        //�����ݵ�Ŀ��
        if (data)
        {
            glTexImage2D(
                GL_TEXTURE_2D,      //�󶨵�λ��
                0,                  //Mipmap����0����������
                GL_RGB,             //�������ʽ
                width,              //��
                height,             //��
                0,                  //��ʷ�������⣬�϶���0
                GL_RGB,             //ԭͼ��ʽ���˴�ʹ��RGB����
                GL_UNSIGNED_BYTE,   //����Ϊchar(byte)���� ���������ģ�
                data);

            glGenerateMipmap(GL_TEXTURE_2D);    //����mipmap
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
#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
//#include "stb_image.h"
#include "GL/glew.h"
namespace Render
{
    class Texture
    {
    public:
        int width, height, nrChannels;
        bool mipmap = true;
        unsigned char* data = nullptr;
        unsigned int texture;

        GLenum Warp_s, Warp_t;
        GLenum Min_filter, Mag_filter;

        int mipmapLevel = 0;

        Texture()
        {
            glGenTextures(1, &texture);

            Warp_s = Warp_t = GL_REPEAT;
            Min_filter = Mag_filter = GL_LINEAR;
        }
        Texture(int width, int height, int channels) :width(width), height(height), nrChannels(channels)
        {
            glGenTextures(1, &texture);

            Warp_s = Warp_t = GL_REPEAT;
            Min_filter = Mag_filter = GL_LINEAR;

            int len = width * height * nrChannels;
            data = (unsigned char*)malloc(len);
        }

        virtual void SetPixel(Color color, int x, int y)
        {
            if (x < 0 || x >= width || y < 0 || y >= height) return;

            int p = (x + y * height) * nrChannels;
            data[p] = (char)int(color.r * 255.99f);
            data[p + 1] = (char)int(color.g * 255.99f);
            data[p + 2] = (char)int(color.b * 255.99f);
            if (nrChannels > 3) data[p + 3] = (char)int(color.a * 255.99f);

        }

        virtual Color GetPixel(int x, int y)
        {
            Color c = Color();
            int p = (x + y * height) * nrChannels;
            c.r = int(data[p]) / 256.0f;
            c.g = int(data[p + 1]) / 256.0f;
            c.b = int(data[p + 2]) / 256.0f;

            if (nrChannels > 3)
            {
                c.a = int(data[p + 3]) / 256.0f;
            }
            return c;
        }

        //virtual void SetUp(int warp_s_type, int warp_t_type, int min_filter, int mag_filter)
        //{
        //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, warp_s_type);
        //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, warp_t_type);
        //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
        //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
        //}

        //��������ÿ�����Ʋ���
        virtual void SetWarpS(GLenum type)
        {
            Warp_s = type;
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Warp_s);
        }
        virtual void SetWarpT(GLenum type)
        {
            Warp_t = type;
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Warp_t);
        }
        virtual void SetMinFilter(GLenum type)
        {
            Min_filter = type;
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Min_filter);
        }
        virtual void SetMagFilter(GLenum type)
        {
            Mag_filter = type;
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Mag_filter);
        }


        virtual void SetUp()
        {
            //glActiveTexture(GL_TEXTURE0);           //�Ѽ���Texture0λ�ã�
            glBindTexture(GL_TEXTURE_2D, texture); //�ѵ�ǰ��������󶨵�GL_TEXTURE_2D����
            // Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
            //SetUp(GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, Warp_s);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, Warp_t);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Min_filter);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Mag_filter);

            //�����ݵ�Ŀ��
            if (data)
            {
                glTexImage2D(
                    GL_TEXTURE_2D,                                  //�󶨵�λ��
                    mipmapLevel,                                    //Mipmap����0����������
                    nrChannels > 3 ? GL_RGBA : GL_RGB,              //�������ʽ
                    width,                                          //��
                    height,                                         //��
                    0,                                              //��ʷ�������⣬�϶���0
                    nrChannels > 3 ? GL_RGBA : GL_RGB,              //ԭͼ��ʽ���˴�ʹ��RGB����
                    GL_UNSIGNED_BYTE,                               //����Ϊchar(byte)���� ���������ģ�
                    data);

                if (mipmap) glGenerateMipmap(GL_TEXTURE_2D);    //����mipmap
            }
        }

        virtual void Release()
        {
            if (&data != nullptr)
            {
                free(data);
                data = nullptr;

            }
        }

        ~Texture()
        {
            std::cout << &data << std::endl;
            if (&data != nullptr)
            {
                free(data);
                data = nullptr;
            }
            //stbi_image_free(data);
        }
    };

    class Texture2D : public Texture
    {

    public:
        Texture2D()
        {
        };
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

        //void SetUp()
        //{
        //    glGenTextures(1, &texture);
        //    //glActiveTexture(GL_TEXTURE0);           //�Ѽ���Texture0λ�ã�
        //    glBindTexture(GL_TEXTURE_2D, texture); //�ѵ�ǰ��������󶨵�GL_TEXTURE_2D����
        //    // Ϊ��ǰ�󶨵�����������û��ơ����˷�ʽ
        //    SetUp(GL_REPEAT, GL_REPEAT, GL_LINEAR, GL_LINEAR);

        //    //�����ݵ�Ŀ��
        //    if (data)
        //    {
        //        glTexImage2D(
        //            GL_TEXTURE_2D,                                  //�󶨵�λ��
        //            0,                                              //Mipmap����0����������
        //            nrChannels > 3 ? GL_RGBA : GL_RGB,              //�������ʽ
        //            width,                                          //��
        //            height,                                         //��
        //            0,                                              //��ʷ�������⣬�϶���0
        //            nrChannels > 3 ? GL_RGBA : GL_RGB,              //ԭͼ��ʽ���˴�ʹ��RGB����
        //            GL_UNSIGNED_BYTE,                               //����Ϊchar(byte)���� ���������ģ�
        //            data);

        //        glGenerateMipmap(GL_TEXTURE_2D);    //����mipmap
        //    }
        //    else
        //    {
        //        std::cout << "Faild To Load Texture" << std::endl;
        //    }
        //    std::cout << "Load Texture Finish" << std::endl;
        //}

        //void SetUp(int warp_s_type, int warp_t_type, int min_filter, int mag_filter)
        //{
        //    
        //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, warp_s_type);
        //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, warp_t_type);
        //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
        //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
        //}

        //~Texture2D()
        //{
        //    //if(data)
        //    //    free(data);
        //}
    };
}
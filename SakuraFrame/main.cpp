#include <iostream>

#define WIDTH 800
#define HEIGHT 600

#define HALF_WIDTH WIDTH/2
#define HALF_HEIGHT HEIGHT/2

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Type.h"

#include "../include/glm/glm.hpp"
#include "Mesh.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


//窗口尺寸重置的时候的回调
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//输入事件
void prcessInput(GLFWwindow* window);

//鼠标回调
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);


float deltaTime, lastFrame;

using namespace std;


int main()
{
    //cout << sizeof(char) << endl;

    //return 0;

    int width, height, nrChannels;
    unsigned char* data = stbi_load("testImg.jpg", &width, &height, &nrChannels, 0);

    fstream fs("Save.dat", ios::out | ios::binary);

    int len = width * height;

    fs.write((char*)data, len);

    system("pause");

    return 0;
    //初始化glfw
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_SAMPLES, 16);

    //创建窗口
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL Window", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Faild To Create Window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //绑定到当前窗口
    glfwMakeContextCurrent(window);

    //初始化 GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Faild To Init GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    //设置窗口宽高和起始坐标
    glViewport(0, 0, WIDTH, HEIGHT);

    //窗口尺寸重置的时候的回调
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //鼠标/焦点回调
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, mouse_callback);

    while (!glfwWindowShouldClose(window))
    {
        prcessInput(window);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
    glViewport(0, 0, width, height);
}


float moveSpeed = 0.1f;
void prcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

bool firstMouse = true;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

}

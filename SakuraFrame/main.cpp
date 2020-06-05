#include <iostream>

#define WIDTH 800
#define HEIGHT 600

#define HALF_WIDTH WIDTH/2
#define HALF_HEIGHT HEIGHT/2

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"

#include "Type.h"
#include "Mesh.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

//窗口尺寸重置的时候的回调
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//输入事件
void prcessInput(GLFWwindow* window);

//鼠标回调
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

//初始化IMGUI
void InitImGUI(GLFWwindow* window, const char* glsl_version);

float deltaTime, lastFrame;

using namespace std;



int main()
{
    int width, height, nrChannels;
    unsigned char* data = stbi_load("testImg.jpg", &width, &height, &nrChannels, 0);

    fstream fs("Save.dat", ios::out | ios::binary);

    int len = width * height;

    fs.write((char*)data, len);

    system("pause");
    return 0;

    //初始化glfw
    glfwInit();
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_SAMPLES, 16);

    //创建窗口
    GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Sakura Frame", NULL, NULL);
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

    //初始化ImGUI
    InitImGUI(window, glsl_version);

    Vector4 clear_color = Vector4{ 0.1f, 0.5f, 0.9f, 1 };

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        prcessInput(window);

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            //ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            //ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            //ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            ImGui::End();
        }

        {
            ImGui::SetNextWindowPos({ 0, 20 }, ImGuiCond_Always);
            ImGui::SetNextWindowSize({ 150, 130 }, ImGuiCond_Always);
            ImGui::Begin("New Frame");
            ImGui::Text("This is some useful text.");
            ImGui::Button("Just A Btn", { 120, 30 });
            ImGui::End();
        }

        ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

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

//初始化ImGUI
void InitImGUI(GLFWwindow* window, const char* glsl_version)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    //ImGui::StyleColorsDark();
    ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}
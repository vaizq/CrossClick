#include <iostream>
#include <string>
#include <random>
#include <cmath>
#include <limits>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers


#include "common.h"

#ifdef __WIN32
#define OS_Windows
#include "windows_utils.h"
#else
#define OS_Linux
#include "linux_utils.h"
#endif

#ifdef OS_Linux
LINUX_BEGIN()
#endif

constexpr int maxInt = std::numeric_limits<int>::max();

constexpr int WINDOW_WIDTH = 600;
constexpr int WINDOW_HEIGHT = 300;
ImVec2 windowSize = ImVec2(WINDOW_WIDTH, WINDOW_HEIGHT);
ImVec2 windowPos = ImVec2(0, 0);

double rndf(double min, double max)
{
    static std::mt19937 g{ std::random_device{}() };
    static std::uniform_int_distribution<int> d{ 0, maxInt };

    double rndNum = 1.0 * d(g) / maxInt; // A number int [0, 1]
    return min + rndNum * (max - min); 
}

int main(int argc, char** argv)
{
#ifdef OS_Linux
    LINUX_SETUP()
#endif

    if(!glfwInit())
        return -1;

    const char* glsl_version = "#version 300 es"; 
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_EGL_CONTEXT_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Random Clicker", NULL, NULL);
    if(window == NULL)
        return -1;    
    glfwMakeContextCurrent(window); 
    glfwSwapInterval(1);
    
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    float startDelay{ 3.0 };
    float maxDelay{ 1.0 };
    double delayBetween{ 1.0 };
    bool clickerOn{ false };
    bool randomOn{ false };
    double lastTime{ 0 };
    double curTime{ 0 };
    bool doneFirstClick{ false };
    
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        ImGui::SetNextWindowSize(windowSize);
        ImGui::SetNextWindowPos(windowPos);

        ImGuiWindowFlags window_flags = 0;
        window_flags |= ImGuiWindowFlags_NoScrollbar;
        window_flags |= ImGuiWindowFlags_MenuBar;
        window_flags |= ImGuiWindowFlags_NoMove;
        window_flags |= ImGuiWindowFlags_NoResize;
        window_flags |= ImGuiWindowFlags_NoCollapse;
        window_flags |= ImGuiWindowFlags_NoNav;
   

        /*----- GUI CODE ------------------------------------------------------------- */
        ImGui::Begin("Random Clicker", NULL, window_flags);

        ImGui::SliderFloat( "Start Delay", &startDelay, 0.0f, 10.0f); 
        ImGui::SliderFloat( randomOn ? "Max Delay Between Clicks" : "Delay Between Clicks", &maxDelay, 0.01f, 10.0f); 

        ImGui::Checkbox("Random", &randomOn);
        ImGui::SameLine();
        if(ImGui::Button( clickerOn ? "Stop" : "Start" ))
        {
            clickerOn = !clickerOn;
            if(clickerOn)
            {
                // Setup times so that it takes start delay to make first click
                delayBetween = maxDelay;
                lastTime = glfwGetTime();
                curTime = lastTime + delayBetween - startDelay;
                doneFirstClick = false;
            }
        } 

        ImGui::End();
        /*------- GUI END ------------------------------------------------------------ */
   
        curTime = glfwGetTime(); 
        if(doneFirstClick && clickerOn && ( curTime - lastTime >= delayBetween ) || 
                ( !doneFirstClick && curTime - lastTime >= startDelay ))
        {
            if(randomOn)
            {
                Mouse::Click(Mouse::LEFT);
                delayBetween = rndf(0.01, maxDelay);
            }
            else
            {
                Mouse::Click(Mouse::LEFT);
            }
            lastTime = curTime;
            doneFirstClick = true;
        }
        

        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

#ifdef OS_Linux
    LINUX_END() 
#endif

    return 0;
}












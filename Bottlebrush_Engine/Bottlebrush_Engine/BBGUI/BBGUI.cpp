//
// Created by Marco Garzon Lara on 10/02/24.
//

#include "BBGUI.h"

void initBBGUI(GLFWwindow *targetWindow)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

// Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(targetWindow, true);          // Second param install_callback=true will install GLFW callbacks and chain to existing ones.
    ImGui_ImplOpenGL3_Init();
}

void updateBBGUIFrameStart()
{
    // (Code calls glfwPollEvents() before this)
    // ...
    // Start the Dear ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

}

/*void BBGui::Text(const std::string_view str)
{
    ImGui::Text(str);
}*/

void updateBBGUIFrameEnd()
{
    // Rendering
    // (Code clears framebuffer, renders other stuff etc. before this)
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    // (Code calls glfwSwapBuffers() etc. after this point)
}

void shutDownBBGUI()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

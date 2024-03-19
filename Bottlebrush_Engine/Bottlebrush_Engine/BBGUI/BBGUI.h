//
// Created by Marco on 10/02/24.
//

#pragma once

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

/**
 *Initialize Bottle Brush GUI
 * @brief initializes the imGUI context for the engine
 * @author Marco Garzon Lara
 */
void initBBGUI(GLFWwindow *targetWindow);

/**
 *GUI Frame Start Updater
 *@brief Calls for a new GUI frame. Supposed to be called at the START of each gameloop/mainloop frame.
 *@author Marco Garzon Lara
 */
void updateBBGUIFrameStart();

/**
 *GUI Frame End Updater
 *@brief Finalizes GUI frame. Supposed to be called at the END of each gameloop/mainloop frame.
 *@author Marco Garzon Lara
 */
void updateBBGUIFrameEnd();

/**
 * Bottle Brush GUI shutdown
 * @brief Destroys the imGUI context
 *
 */
void shutDownBBGUI();

//
//  Created by Alan Brunet 12/03/2024
//
#pragma once

// __debugbreak() = instrinctic to MSVC compiler?
#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

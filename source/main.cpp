#define GLAD_GL_IMPLEMENTATION
#include <glad/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <iostream> 
#include <chrono>
#include <thread>

#include "PixelBuffer.h"
#include "SampleScene.h"
#include "InputSupport.h"
#include "Rendering.h"

namespace
{
    InputSupport inputSupport;
}

void GLFWErrorCallback(int error, const char* description)
{
    std::cerr << "Error: " << description << std::endl;
}

void GLFWKeyCallback(GLFWwindow* window, int keyCode, int scanCode, int action, int mods)
{
    if (action == GLFW_RELEASE)
    {
        inputSupport.registerKeyState(keyCode, false);
    }
    else
    {
        inputSupport.registerKeyState(keyCode, true);
    }
}

void GLFWCursorPosCallback(GLFWwindow* window, double xPos, double yPos)
{
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    auto xPosition = 0.0;
    auto yPosition = 0.0;
    glfwGetCursorPos(window, &xPosition, &yPosition);

    auto mouseXDelta = xPosition - width / 2;
    auto mouseYDelta = height / 2 - yPosition;

    glfwSetCursorPos(window, width / 2, height / 2);

    inputSupport.setMouseDelta(mouseXDelta, mouseYDelta);
}

void checkCompilationSuccess(GLuint shader)
{
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cout << "Error: vs compilation failed\n" << infoLog << std::endl;
    }
}

void checkLinkingSuccess(GLuint program)
{
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cout << "Error: shader linking failed\n" << infoLog << std::endl;
    }
}

int main()
{
    glfwSetErrorCallback(GLFWErrorCallback);

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_RESIZABLE, false);
    GLFWwindow* window = glfwCreateWindow(Rendering::PRESENT_RESOLUTION_X, Rendering::PRESENT_RESOLUTION_Y, "gt", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Couldn't create window" << std::endl;
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    gladLoadGL(glfwGetProcAddress);

    int windowWidth, windowHeight;
    glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);

    glfwSwapInterval(1);

    glfwSetCursorPos(window, windowWidth / 2, windowHeight / 2);
    glfwSetKeyCallback(window, GLFWKeyCallback);
    glfwSetCursorPosCallback(window, GLFWCursorPosCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    struct vert
    {
        float x, y;
    };

    std::vector<vert> fullScreenQuad = {
        {-1.0f, -1.0f}, //t0 BL
        { 1.0f, -1.0f}, //t0 BR
        {-1.0f,  1.0f}, //t0 TL
        {-1.0f,  1.0f}, //t1 TL
        { 1.0f, -1.0f}, //t1 BR
        { 1.0f,  1.0f}  //t1 TR
    };

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vert) * fullScreenQuad.size(), fullScreenQuad.data(), GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);


    const char* vertexShaderSource =
        "#version 330\n"
        "layout (location = 0) in vec2 pos;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = vec4(pos, 1.0, 1.0);\n"
        "}\n";

    const char* fragmentShaderSource =
        "#version 330\n"
        "uniform ivec2 res;\n"
        "uniform sampler2D tex;\n"
        "out vec4 fragColor;\n"
        "void main()\n"
        "{\n"
        "    fragColor = texture(tex, gl_FragCoord.xy / res);\n"
        "}\n";

    GLuint vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShaderObject, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShaderObject);
    checkCompilationSuccess(vertexShaderObject);

    GLuint fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderObject, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShaderObject);
    checkCompilationSuccess(fragmentShaderObject);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShaderObject);
    glAttachShader(shaderProgram, fragmentShaderObject);
    glLinkProgram(shaderProgram);
    checkLinkingSuccess(shaderProgram);

    glDeleteShader(vertexShaderObject);
    glDeleteShader(fragmentShaderObject);
    
    glUseProgram(shaderProgram);

    glUniform2i(glGetUniformLocation(shaderProgram, "res"), Rendering::PRESENT_RESOLUTION_X, Rendering::PRESENT_RESOLUTION_Y);

    GLuint texture;
    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    PixelBuffer pixelBuffer(Rendering::RENDER_RESOLUTION_X, Rendering::RENDER_RESOLUTION_Y);
    SampleScene sampleScene;

    std::chrono::steady_clock::time_point prevDisplayTime = std::chrono::steady_clock::now();

        int numSamples = 0;
        double sampleAccumulator = 0;

    while(!glfwWindowShouldClose(window))
    {
        std::chrono::duration<float, std::milli> currentFrameTime(std::chrono::steady_clock::now() - prevDisplayTime);

        auto underTime = Rendering::MIN_FRAME_TIME - currentFrameTime;


        if (underTime.count() < 0) // it's been long enough since last display
        {
            auto startTime = std::chrono::system_clock::now();

            sampleScene.update(std::chrono::duration_cast<std::chrono::duration<float, std::ratio<1,1>>>(currentFrameTime), inputSupport);
            sampleScene.draw(pixelBuffer);

        

            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Rendering::RENDER_RESOLUTION_X, Rendering::RENDER_RESOLUTION_Y, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixelBuffer.getPixels().data());
            glBindTexture(GL_TEXTURE_2D, texture);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            pixelBuffer.clear();

            prevDisplayTime = std::chrono::steady_clock::now();

            auto endTime = std::chrono::system_clock::now();
            std::chrono::duration<double, std::milli> mills = endTime - startTime;

            inputSupport.update(*window);
            glfwSwapBuffers(window);
            glfwPollEvents();

        }
        else // last display was too recent, wait
        {
            std::this_thread::sleep_for(underTime);
        }

    }

    glfwDestroyWindow(window);
    window = nullptr;

    glfwTerminate();

    return EXIT_SUCCESS;
}

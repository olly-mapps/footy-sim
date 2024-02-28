#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>

#include"shader.h"
#include"vao.h"
#include"vbo.h"
#include"ebo.h"

GLfloat vertices[] =
{
    // First triangle
    -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,   // lower-left
    0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,  // lower-right
    0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,    // top
    // Second triangle
    -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,    // inner-left
    0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,   // inner-right
    0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f     // bottom
};

GLuint indices[] = 
{
    0, 3, 5,
    3, 2, 4,
    5, 4, 1
};

int main()
{

    glfwInit();

    //Gives window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //Defines window
    GLFWwindow* window = glfwCreateWindow(800, 800, "Football Sim", NULL , NULL);

    //Error catching
    if (window == NULL)
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }

    //Open window
    glfwMakeContextCurrent(window);

    //Glad
    gladLoadGL();
    glViewport(0, 0, 800, 800);

    Shader shaderProgram("resources/shaders/default.vert", "resources/shaders/default.frag");

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkVBO(VBO1, 0);
    
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    //Open loop
    while (!glfwWindowShouldClose(window))
    {

        //Render Commands
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shaders
        shaderProgram.Activate();

        // Draw the segment
        VAO1.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        //Check and Call events, and swap buffers
        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }

    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();

    shaderProgram.Deactivate();
    
    //Terminate
    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}
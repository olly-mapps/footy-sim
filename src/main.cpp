#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


// Vertex Shader
const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    void main()
    {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
)";

// Fragment Shader
const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    void main()
    {
        FragColor = vec4(0.0f, 0.5f, 0.0f, 1.0f); // Green
    }
)";

int main()
{

    glfwInit();

    //Gives window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLfloat vertices[] =
    {
        // First triangle
        -0.5f, 0.5f, 0.0f,   // Top-left
        -0.5f, -0.5f, 0.0f,  // Bottom-left
        0.0f, 0.0f, 0.0f,    // Center-bottom
        // Second triangle
        0.5f, 0.5f, 0.0f,    // Top-right
        0.5f, -0.5f, 0.0f,   // Bottom-right
        0.0f, 0.0f, 0.0f     // Center-bottom
    };

    //Defines window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Football Sim", NULL , NULL);

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

    //Shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER); //Create vertex shader object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); //Attach vertex shader source to the object
    glCompileShader(vertexShader); //Compile the shader

    GLuint fragmentShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    //Create shader program
    GLuint shaderProgram = glCreateProgram();

    //Attach shaders to the program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    //Delete shaders since they are now in the program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Vertex Objects
    GLuint VAO, VBO;

    //Generate VAO, VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    //Make VAO the current Vertex Array Object by binding it
    glBindVertexArray(VAO);

    //Make VBO the current Vertex Binding Object by binding it and specifying its a GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //Put the vertices into the VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Make it possible for OpenGL to read 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //Bind these two zero so they dont change
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glfwSwapBuffers(window);

    //Open loop
    while (!glfwWindowShouldClose(window))
    {

        //Render Commands
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Use the shaders
        glUseProgram(shaderProgram);

        // Draw the segment
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        //Check and Call events, and swap buffers
        glfwSwapBuffers(window);
        
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    //Terminate
    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}
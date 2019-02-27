#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <cstring>

typedef unsigned short ushort;
typedef unsigned int uint;

void framebuffer_size_callback(GLFWwindow*, int, int);
void process_input(GLFWwindow*);
const char* get_shader_source(const std::string&);

const std::string VERTEX_SHADER_SOURCE = "./shaders/shader.vert"; 
const std::string FRAGMENT_SHADER_SOURCE = "./shaders/shader.frag";

int main() {
  // Initialize GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(800, 600, "Doom", NULL, NULL);
  if(!window) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  glViewport(0, 0, 800, 600);

  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  float vertices[] = { -0.5f, -0.5f, 0.0f,
		       0.5f, -0.5f, 0.0f,
		       0.0f, 0.5f, 0.0f
  };

  // Create a VAO which will store the VBO's data
  uint VAO;
  glGenVertexArrays(1, &VAO);
 
  // Generate a buffer with the array of vertices
  uint VBO;
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  const GLchar* const vertexShaderSource = get_shader_source(VERTEX_SHADER_SOURCE);
  // Create and compile the vertex shader
  uint vertexShader;
  vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader(vertexShader);

  // Check for shader compilation success
  int success;
  char infoLog[512];
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if(!success) {
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  }


  const char* fragmentShaderSource = get_shader_source(FRAGMENT_SHADER_SOURCE);
  // Create and compile the fragment shader
  uint fragmentShader;
  fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if(!success) {
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
  }

  // Create the Shader program
  uint shaderProgram;
  shaderProgram = glCreateProgram();

  glAttachShader(shaderProgram, vertexShader);
  glAttachShader(shaderProgram, fragmentShader);
  glLinkProgram(shaderProgram);

  // Test to see if the Shader program has compiled
  if(!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER PROGRAM::COMPILATION FAILED\n" << infoLog << std::endl;
  }
  
  // Use the program
  glUseProgram(shaderProgram);

  // Delete shaders as we no longer need them
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  // We must tell OpenGL how to process the vertex data
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);
  
  // render
  while(!glfwWindowShouldClose(window)) {
    // input
    process_input(window);

    // rendering commands here
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // draw triangle
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    // check and call events and swap the buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }


  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glfwTerminate();
  
  return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
  glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
  if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

const char* get_shader_source(const std::string& path) {
  std::ifstream is;
  is.open(path);

  std::string source("");
  if(is.is_open()) {
    char c;
    while(is.get(c)) {
      source += c;
    }
    
    is.close();
  }
  else {
    std::cout << "Was not able to open file " << path << std::endl;
  }


  char* output = new char[source.length()];
  strcpy(output, source.c_str());
  
  return output;
}

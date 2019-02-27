#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>

typedef unsigned short ushort;
typedef unsigned int uint;

void framebuffer_size_callback(GLFWwindow*, int, int);
void process_input(GLFWwindow*);
const GLchar* const get_shader_source(const std::string);

const std::string VERTEX_SHADER_SOURCE = "../shaders/shader.vert"; 
const std::string FRAGMENT_SHADER_SOURCE = "../shaders/shader.frag";

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

  // Generate a buffer with the array of vertices
  uint VBO;
  glGenBuffers(1, &VBO);
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


  const GLchar* const fragmentShaderSource = get_shader_source(FRAGMENT_SHADER_SOURCE);
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

  
  // render
  while(!glfwWindowShouldClose(window)) {
    // input
    process_input(window);

    // rendering commands here
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // check and call events and swap the buffers
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

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

const GLchar* const get_shader_source(std::string path) {
  std::ifstream is(path);
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

  std::cout << source << std::endl;
  return source.c_str();
}

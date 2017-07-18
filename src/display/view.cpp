//
// Created by Dillon Yao on 6/9/17.
//

#include <iostream>
#include "view.h"

const int DEFAULT_HEIGHT = 800;
const int DEFAULT_WIDTH = 1200;

GLFWwindow *View::_window = nullptr;
Application *View::_app = nullptr;
int View::width, View::height;

std::string View::title = "";

View::View() {}

View::~View() {
    glfwDestroyWindow(_window);
    glfwTerminate();
}

void View::init() {
    if (!_app) {
        std::cerr << "Error: No app set for view" << std::endl;
        exit(EXIT_FAILURE);
    }

    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        std::cerr << "Error: Failed to initialize GLFW" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    _window = glfwCreateWindow(DEFAULT_WIDTH, DEFAULT_HEIGHT, "Porthole", NULL, NULL);
    if (!_window) {
        std::cerr << "Error: Failed to create GLFWwindow" << std::endl;
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(_window);

    glfwSetFramebufferSizeCallback(_window, resize_callback);
    glfwSetKeyCallback(_window, key_callback);
    glfwSetCursorPosCallback(_window, cursor_callback);
    glfwSetScrollCallback(_window, scroll_callback);
    glfwSetInputMode(_window, GLFW_STICKY_MOUSE_BUTTONS, 1);
    glfwSetMouseButtonCallback(_window, mouse_button_callback);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Error: Failed to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }

    int width, height;
    glfwGetFramebufferSize(_window, &width, &height);
    resize_callback(_window, width, height);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    _app->init();
}

void View::bind_application(Application *app) {
    _app = app;
}

void View::begin() {
    double sys_last = glfwGetTime();
    double sys_curr, elapsed;
    while(!glfwWindowShouldClose(_window)) {
        sys_curr = glfwGetTime();
        elapsed = sys_curr - sys_last;
        if (elapsed >= 1.0f / 30) {
            update(0.f);
            sys_last = sys_curr;
        }
    }
}

void View::update(float dt) {
    glfwPollEvents();
    _app->update(dt);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _app->render();
    glfwSwapBuffers(_window);
}

void View::error_callback(int error, const char *desc){
    std::cerr << "(!) GLFW Error " << error << ": " << desc << std::endl;
}

void View::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods){
    switch(action) {
        case GLFW_PRESS:
            if (key == GLFW_KEY_ESCAPE) {
                glfwSetWindowShouldClose(_window, GL_TRUE);
            }
            break;
    }
}

void View::resize_callback(GLFWwindow *window, int width, int height){

}

void View::cursor_callback(GLFWwindow *window, double xpos, double ypos){

}

void View::scroll_callback(GLFWwindow *window, double xoffset, double yoffset){

}

void View::mouse_button_callback(GLFWwindow *window, int button, int action, int mods){

}

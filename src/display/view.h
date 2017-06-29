//
// Created by Dillon Yao on 6/29/17.
//

#ifndef PORTHOLE_VIEW_H
#define PORTHOLE_VIEW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "application.h"

class View {
public:
    View();
    ~View();

    void init();
    void begin();
    void bind_application(Application *app);

private:
    static GLFWwindow *_window;
    static Application *_app;

    static int width, height;

    static void update(float dt);

    static void error_callback(int error, const char *desc);
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);
    static void resize_callback(GLFWwindow *window, int width, int height);
    static void cursor_callback(GLFWwindow *window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
    static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

    static std::string title;
};

#endif //PORTHOLE_VIEW_H

//
// Created by Dillon Yao on 6/29/17.
//

#include "porthole.h"
#include "../geometry/icosohedron.h"

void Porthole::init() {
    face_detector.load_cascade("../assets/cascades/haarcascade_frontalface_alt2.xml");
    face_detector.init();

    cam_shader.load("../assets/shaders/billboard.vert", "../assets/shaders/billboard.frag");
    wall_shader.load("../assets/shaders/wall.vert", "../assets/shaders/wall.frag");
    focus_shader.load("../assets/shaders/sphere.vert", "../assets/shaders/sphere.frag");

    const float scale = 0.7f;
    const int padding = 20;

    float left = padding / 1200.f - 1.f;
    float bottom = padding / 800.f - 1.f;
    float right = (padding + scale * 680) / 1200.f - 1.f;
    float top = (padding + (scale * 680) * 480 / 640) / 800.f - 1.f;

    float vertices[] = {
            right, top, 0.0f,       1.0f, 1.0f,
            right, bottom, 0.0f,      1.0f, 0.0f,
            left, bottom, 0.0f,     0.0f, 0.0f,
            left, top, 0.0f,      0.0f, 1.0f,
    };

    unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
    };

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    GLuint VBO, EBO;
    glGenVertexArrays(1, &cam_VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(cam_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    float wall_vertices[] = {
            1.5f, 3.0f, -5.0f,
            1.5f, -3.0f, -5.0f,
            -1.5f, -3.0f, -5.0f,
            -1.5f, 3.0f, -5.0f
    };

    GLuint VBO2, EBO2;
    glGenVertexArrays(1, &wall_VAO);
    glGenBuffers(1, &VBO2);
    glGenBuffers(1, &EBO2);

    glBindVertexArray(wall_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO2);
    glBufferData(GL_ARRAY_BUFFER, sizeof(wall_vertices), wall_vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glGenTextures(1, &cam_texture);

    glBindTexture(GL_TEXTURE_2D, cam_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    cam_zoom_avg = M_PI / 4;

    std::vector<uint32_t> focus_indices;
    std::vector<glm::vec3> focus_vertices;
    generate_icososphere_mesh(3, focus_indices, focus_vertices);
    std::vector<Vertex> processed_vertices;
    for (auto p = focus_vertices.begin(); p != focus_vertices.end(); ++p) {
        Vertex v;
        v.pos = *p;
        v.n = glm::normalize(v.pos);
        processed_vertices.push_back(v);
    }
    focus.set_geometry(processed_vertices, focus_indices);
}

void Porthole::update(float dt) {
    face_detector.process_frame();
    cv::Mat frame = face_detector.get_frame();
    cv::flip(frame, frame, 0);
    cv::flip(frame, frame, 1);

    glBindTexture(GL_TEXTURE_2D, cam_texture);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB,
                 frame.cols,
                 frame.rows,
                 0,
                 GL_BGR,
                 GL_UNSIGNED_BYTE,
                 frame.ptr()
    );

    cv::Rect face = face_detector.get_last_bbox();
    float center_x = ((face.x + face.width / 2.f) / frame.cols - 0.5f) * 5;
    float center_y = ((face.y + face.height / 2.f) / frame.rows - 0.5f) * 5;
    cam_avg = cam_avg * 0.7f + glm::vec3(center_x, center_y, camera.pos.z) * 0.2f;

    float rel_size = (float) face.width / frame.cols + (float) face.height / frame.rows;
    if (rel_size) {
        cam_zoom_avg = 0.1f * (1.f / rel_size * (MAX_ZOOM - MIN_ZOOM) + MIN_ZOOM) + 0.9f * cam_zoom_avg;
    }

    camera.set_position(glm::vec3(cam_avg.x, cam_avg.y, camera.pos.z));

    wall_shader.use();
    glm::mat4 proj = glm::perspective(cam_zoom_avg, (float) 1200 / (float) 800, camera.n_clip, camera.f_clip);
    glUniformMatrix4fv(glGetUniformLocation(wall_shader.program, "proj"), 1, GL_FALSE, glm::value_ptr(proj));

    glm::mat4 view = camera.get_view_matrix();
    glUniformMatrix4fv(glGetUniformLocation(wall_shader.program, "view"), 1, GL_FALSE, glm::value_ptr(view));

    focus_shader.use();
    glUniformMatrix4fv(glGetUniformLocation(focus_shader.program, "proj"), 1, GL_FALSE, glm::value_ptr(proj));
    glUniformMatrix4fv(glGetUniformLocation(focus_shader.program, "view"), 1, GL_FALSE, glm::value_ptr(view));
}

void Porthole::render() {
    focus_shader.use();
    focus.render();

    wall_shader.use();
    glUniform1f(glGetUniformLocation(wall_shader.program, "x_offset"), -3.f);
    glUniform3f(glGetUniformLocation(wall_shader.program, "color"), 1.f, 0.3f, 0.f);
    glBindVertexArray(wall_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glUniform1f(glGetUniformLocation(wall_shader.program, "x_offset"), 0.f);
    glUniform3f(glGetUniformLocation(wall_shader.program, "color"), 0.f, 1.0f, 0.3f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glUniform1f(glGetUniformLocation(wall_shader.program, "x_offset"), 3.f);
    glUniform3f(glGetUniformLocation(wall_shader.program, "color"), 0.3f, 0.0f, 1.f);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    cam_shader.use();
    glUniform1i(glGetUniformLocation(cam_shader.program, "frame"), 0);
    glBindVertexArray(cam_VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

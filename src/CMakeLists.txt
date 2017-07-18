set(PORTHOLE_SRC
        main.cpp

        detection/face_detector.cpp

        display/porthole.cpp
        display/view.cpp

        geometry/icosohedron.h
        geometry/mesh.h
        )

set(PORTHOLE_HDR

        detection/face_detector.h

        display/application.h
        display/porthole.h
        display/view.h

        geometry/mesh.cpp

        misc/camera.h
        misc/shader.h
        )

add_executable(porthole
        ${PORTHOLE_SRC}
        ${PORTHOLE_HDR}
        )

set(OpenCV_LIBS opencv_core opencv_imgproc opencv_calib3d opencv_video opencv_features2d opencv_ml opencv_highgui opencv_objdetect opencv_contrib opencv_legacy opencv_gpu)

include_directories(
        ${OpenCV_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIRS}
        ${GLFW_INCLUDE_DIRS}
        ${FREETYPE_INCLUDE_DIRS}
)

link_directories(
        ${GLEW_LIBRARY_DIRS}
        ${GLFW_LIBRARY_DIRS}
        ${FREETYPE_LIBRARY_DIRS}
)

target_link_libraries(porthole
        glew ${GLEW_LIBRARIES}
        glfw ${GLFW_LIBRARIES}
        ${OPENGL_LIBRARIES}
        ${OpenCV_LIBS}
        )

#-------------------------------------------------------------------------------
# Platform-specific configurations for target
#-------------------------------------------------------------------------------
if(APPLE)
    set_property(TARGET porthole APPEND_STRING PROPERTY COMPILE_FLAGS
            "-Wno-deprecated-declarations -Wno-c++11-extensions")
endif(APPLE)


# Put executable in build directory root
set(EXECUTABLE_OUTPUT_PATH ..)

# Install to project root
install(TARGETS porthole DESTINATION ${porthole_SOURCE_DIR}/..)
set(PORTHOLE_SRC
        main.cpp
        )

set(PORTHOLE_HDR

        )

add_executable(porthole
        ${PORTHOLE_SRC}
        ${PORTHOLE_HDR}
        )

set(OpenCV_LIBS opencv_core opencv_imgproc opencv_calib3d opencv_video opencv_features2d opencv_ml opencv_highgui opencv_objdetect opencv_contrib opencv_legacy opencv_gpu)

include_directories(${OpenCV_INCLUDE_DIR})

target_link_libraries(porthole
        ${OPENGL_LIBRARIES}
        ${OpenCV_LIBS}
        )

message("${OpenCV_LIBRARIES}")
message("${OpenCV_LINK_DIRECTORIES}")

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
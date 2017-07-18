//
// Created by Dillon Yao on 6/29/17.
//

#include <iostream>
#include "face_detector.h"

FaceDetector::FaceDetector() {

}

void FaceDetector::load_cascade(std::string path) {
    if(!face_cascade.load(path)) {
        printf("%s", "--(!)Error loading face cascade\n");
        exit(EXIT_FAILURE);
    };
}

void FaceDetector::init() {
    _capture.open(0);
    if (!_capture.isOpened()) {
        printf("%s", "Error opening capture\n");
        exit(EXIT_FAILURE);
    }
    _capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
    _capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
}

void FaceDetector::process_frame() {
    if (!_capture.read(_frame)) {
        printf("%s\n", "Unable to read from Video Device");
        exit(EXIT_FAILURE);
    };
    if (_frame.empty()) {
        printf("%s\n", "No captured Frame!");
        exit(EXIT_FAILURE);
    }
    std::vector<cv::Rect> faces;
    cv::Mat frame_gray;

    cv::cvtColor(_frame, frame_gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(frame_gray, frame_gray);

    face_cascade.detectMultiScale(
            frame_gray,
            faces,
            1.1,
            2,
            0 | CV_HAAR_SCALE_IMAGE,
            cv::Size(_frame.rows / 5, _frame.rows / 5),
            cv::Size(_frame.rows * 2 /3, _frame.rows * 2 / 3)
    );

    if (faces.size()) {
        for (int i = 1; i < faces.size(); ++i) {
            cv::Point a(faces[i].x, faces[i].y);
            cv::Point b(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
            rectangle(_frame, a, b, cv::Scalar(0, 0, 255), 2, 8, 0);
        }
        _last_face = faces[0];
        cv::Point a(_last_face.x, _last_face.y);
        cv::Point b(_last_face.x + _last_face.width, _last_face.y + _last_face.height);
        rectangle(_frame, a, b, cv::Scalar(0, 255, 0), 2, 8, 0);
    }
}

cv::Mat &FaceDetector::get_frame() {
    return _frame;
}

cv::Rect FaceDetector::get_last_bbox() {
    return _last_face;
}
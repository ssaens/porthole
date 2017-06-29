//
// Created by Dillon Yao on 6/29/17.
//

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
}

void FaceDetector::process_frame() {
    _capture.read(_frame);
    if (_frame.empty()) {
        printf("%s\n", "No captured Frame!");
        exit(EXIT_FAILURE);
    }
    std::vector<cv::Rect> faces;
    cv::Mat frame_gray;

    cv::cvtColor(_frame, frame_gray, cv::COLOR_BGR2GRAY);
    cv::equalizeHist(frame_gray, frame_gray);

    //-- Detect faces
    face_cascade.detectMultiScale(
            frame_gray,
            faces,
            1.1,
            2,
            0 | CV_HAAR_SCALE_IMAGE,
            cv::Size(_frame.rows / 5, _frame.rows / 5),
            cv::Size(_frame.rows * 2 /3, _frame.rows * 2 / 3)
    );

    for (size_t i = 0; i < faces.size(); i++) {
        cv::Point a(faces[i].x, faces[i].y);
        cv::Point b(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
        rectangle(_frame, a, b, cv::Scalar(0, 255, 0), 2, 8, 0);
    }
//    cv::imshow("TEST", _frame);
}

cv::Mat &FaceDetector::get_frame() {
    return _frame;
}

void FaceDetector::get_last_bbox(int *x, int *y, int *w, int *h) {

}
//
// Created by Dillon Yao on 6/29/17.
//

#ifndef PORTHOLE_FACE_DETECTOR_H
#define PORTHOLE_FACE_DETECTOR_H

#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class FaceDetector {
public:
    FaceDetector();

    void init();
    void load_cascade(std::string path);
    void process_frame();
    cv::Mat &get_frame();
    void get_last_bbox(int *x, int *y, int *w, int *h);

private:
    cv::VideoCapture _capture;
    cv::Mat _frame;

    cv::CascadeClassifier face_cascade;


};

#endif //PORTHOLE_FACE_DETECTOR_H

//
// Created by Dillon Yao on 6/7/17.
//

#include <iostream>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

void detect_and_display(Mat frame);
String face_cascade_name = "../cascades/haarcascade_frontalface_alt2.xml";
CascadeClassifier face_cascade;
String window_name = "Capture - Face detection";


int main(int argc, char **argv) {
        VideoCapture capture;
        Mat frame;

        //-- 1. Load the cascades
        if(!face_cascade.load(face_cascade_name)) {
            printf("--(!)Error loading face cascade\n");
            return -1;
        };

        //-- 2. Read the video stream
        capture.open( 0 );
        if (!capture.isOpened()) {
            printf("--(!)Error opening video capture\n");
            return -1;
        }

        while (capture.read(frame)) {
            if (frame.empty()) {
                printf(" --(!) No captured frame -- Break!");
                break;
            }

            //-- 3. Apply the classifier to the frame
            detect_and_display(frame);

            int c = waitKey(10);
            if((char) c == 27) {
                break;
            } // escape
        }
        return 0;
}

void detect_and_display( Mat frame ) {
    std::vector<Rect> faces;
    Mat frame_gray;

    cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    //-- Detect faces
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));

    for (size_t i = 0; i < faces.size(); i++) {
        Point a(faces[i].x, faces[i].y);
        Point b(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
        rectangle(frame, a, b, Scalar(0, 255, 0), 2, 8, 0);
        Mat faceROI = frame_gray(faces[i]);
    }
    //-- Show what you got
    imshow(window_name, frame);
}

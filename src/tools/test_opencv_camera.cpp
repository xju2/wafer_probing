#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;
using namespace std;
// #define CAP_PROP_FPS 60

int main(int argc, char* argv[]) 
{
    VideoCapture cap(0);
    
    if(!cap.isOpened()) {
        cout <<"Cannot open the video camera" << endl;
        return -1;
    } else {
        cout <<"video camera is open" << endl;
    }

    // cap.set(CAP_PROP_FRAME_WIDTH, 320);
    // cap.set(CAP_PROP_FRAME_HEIGHT, 582);
    // cap.set(CAP_PROP_FPS, 60.);

    double dWidth = cap.get(CAP_PROP_FRAME_WIDTH);
    double dHeight = cap.get(CAP_PROP_FRAME_HEIGHT);
    double dFPS = cap.get(CAP_PROP_FPS); 
    
    cout << "Frame size: " << dWidth << " x " << dHeight << endl;
    cout << "FPS: " << dFPS << endl;


    namedWindow("MyVideo", WINDOW_AUTOSIZE);

    while(1) {
        Mat frame;

        bool bSuccess = cap.read(frame);
        
        if (!bSuccess) {
            cout << "Cannot read a frame from video stream" << endl;
            break;
        }

        imshow("MyVideo", frame);

        if(waitKey(30) == 27) {
            cout << "ESC key is pressed by user" << endl;
            break;
        }
    }
    cap.release();

    return 0;
}

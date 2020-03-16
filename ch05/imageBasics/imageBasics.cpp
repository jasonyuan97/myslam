#include <iostream>
#include <chrono>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

int main(int argc, char** argv) {
    cv::Mat image;
    image = cv::imread(argv[1]);

    if(image.data == nullptr) {
        cerr << "File " << argv[1] << "does not exist." << endl;
        return -1;
    }

    cout << "Num of cols: " << image.cols << ", Num of rows: " << image.rows << ", Num of channels: " << image.channels() << endl;
    cv::imshow("iamge", image);
    cv::waitKey(0);

    if(image.type()!=CV_8UC1 && image.type()!=CV_8UC3) {
        cout << "Please provide a greyscale image or a colored image." << endl;
        return -1;
    }

    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    for(int y=0; y<image.rows; ++y) {
        unsigned char* row_ptr = image.ptr<unsigned char>(y);
        for(int x=0; x<image.cols; ++x) {
            unsigned char* data_ptr = &row_ptr[x*image.channels()];
            for(int c=0; c!=image.channels(); ++c) {
                unsigned char data = data_ptr[c];
            }
        } 
    }
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    chrono::duration<double> time_used = chrono::duration_cast<chrono::duration<double>>(t2-t1);
    cout << "Time elapsed: " << time_used.count() << " seconds." << endl;

    // copy an image
    cv::Mat image_another = image; 
    // change image_another will also change image
    image_another(cv::Rect(0, 0, 100, 100)).setTo(0); // set the pixels from (0, 0) to (100, 100) to 0
    cv::imshow("image", image);
    cv::waitKey(0);

    // clone
    cv::Mat image_clone = image.clone();
    image_clone(cv::Rect(0, 0, 100, 100)).setTo(255);
    cv::imshow("image", image);
    cv::imshow("image_clone", image_clone);
    cv::waitKey(0);

    cv::destroyAllWindows();
    return 0;
}

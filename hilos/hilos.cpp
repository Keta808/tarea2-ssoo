#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread>
#include <chrono>

using namespace cv;
using namespace std;

void procesarFilas(Mat& image, Mat& grayImage, int startRow, int endRow) {
    for (int r = startRow; r < endRow; r++) {
        for (int c = 0; c < image.cols; c++) {
            Vec3b pixel = image.at<Vec3b>(r, c);
            uchar luminosity = 0.3 * pixel[2] + 0.59 * pixel[1] + 0.11 * pixel[0];
            grayImage.at<uchar>(r, c) = luminosity;
        }
    }
}

int main(int argc, char*argv[]) {

        string imagenEntrada = argv[1];
        string imagenSalida = argv[2];
        int numThreads = atoi(argv[3]);


    Mat image = imread(imagenEntrada, IMREAD_COLOR);

    if (image.empty()) {
        cout << "No se puede cargar la imagen" << endl;
        return -1;
    }

    Mat grayImage(image.rows, image.cols, CV_8UC1);

    int rowsPerThread = image.rows / numThreads ;

    vector<thread> threads;

    auto start = chrono::high_resolution_clock::now();

    for (int i = 0; i < numThreads; i++) {
        int startRow = i * rowsPerThread;
        int endRow = (i == numThreads - 1) ? image.rows : (i + 1) * rowsPerThread;

        threads.emplace_back(procesarFilas, ref(image), ref(grayImage), startRow, endRow);
    }

    for (auto& t : threads) {
        t.join();
    }

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::duration<double>>(stop - start);

    cout << "Tiempo de ejecución: " << duration.count() << " s" << endl;

    imwrite(imagenSalida, grayImage);

    return 0;
}

//g++ -o hilos hilos.cpp -std=c++11 `pkg-config --cflags --libs opencv4`

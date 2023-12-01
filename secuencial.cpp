#include <opencv2/opencv.hpp>
#include <iostream>
#include <chrono>

using namespace cv;
using namespace std;

int main() {
    // Iniciar el cronómetro
    auto start = chrono::high_resolution_clock::now();

    Mat image = imread("nasa_pesada.png", IMREAD_COLOR);

    if (image.empty()) {
        cout << "No se puede cargar la imagen" << endl;
        return -1;
    }

    Mat grayImage(image.rows, image.cols, CV_8UC1);

    for (int r = 0; r < image.rows; r++) {
        for (int c = 0; c < image.cols; c++) {
            Vec3b pixel = image.at<Vec3b>(r, c);
            uchar luminosity = 0.3 * pixel[2] + 0.59 * pixel[1] + 0.11 * pixel[0];
            grayImage.at<uchar>(r, c) = luminosity;
        }
    }

    // Detener el cronómetro
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);

    cout << "Tiempo de ejecución: " << duration.count() << " ms" << endl;

    // Guardar la imagen en escala de grises
    imwrite("nasa_pesada_secuencial.png", grayImage);

    return 0;
}

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

int main() {
    Mat image = imread("nasa_pesada.png", IMREAD_COLOR);

    if (image.empty()) {
        cout << "No se puede cargar la imagen" << endl;
        return -1;
    }

    Mat grayImage(image.rows, image.cols, CV_8UC1);

    // Número de hilos que deseas utilizar
    const int numThreads = 4;

    // Calcular el número de filas que cada hilo procesará
    int rowsPerThread = image.rows / numThreads;

    // Vector para almacenar los hilos
    vector<thread> threads;

    // Iniciar el cronómetro
    auto start = chrono::high_resolution_clock::now();

    // Iniciar los hilos
    for (int i = 0; i < numThreads; i++) {
        int startRow = i * rowsPerThread;
        int endRow = (i == numThreads - 1) ? image.rows : (i + 1) * rowsPerThread;

        threads.emplace_back(procesarFilas, ref(image), ref(grayImage), startRow, endRow);
    }

    // Esperar a que todos los hilos terminen
    for (auto& t : threads) {
        t.join();
    }

    // Detener el cronómetro
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);

    cout << "Tiempo de ejecución: " << duration.count() << " ms" << endl;

    // Guardar la imagen en escala de grises
    imwrite("nasa_gris.png", grayImage);

    return 0;
}

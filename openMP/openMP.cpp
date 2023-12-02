/*
g++ -o versionOpenMP versionOpenMP.cpp -std=c++11 `pkg-config --cflags --libs opencv4` -fopenmp
/versionOpenMP imagen_rayo.jpg imagen_rayo_gris.jpg 4
*/

#include <omp.h>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

//Codigo que ocupa la API OPenMP para hacer version1.cpp
int main(int argc, char *argv[]) {
    if(argc != 4){
        cout << "Uso: " << argv[0] << " <imagen_entrada> <imagen_salida> <numero_hilos>\n";
        return -1;
    }

    string nombreImagenEntrada = argv[1];
    string nombreImagenSalida = argv[2];
    int numHilos = atoi(argv[3]);

    cout << "Imagen de entrada: " << nombreImagenEntrada << endl;
    Mat image = imread(nombreImagenEntrada, IMREAD_COLOR);

    // Verificar si la imagen se cargó correctamente
    if (image.empty()) {
        cout << "No se pudo cargar la imagen." << endl;
        return -1;
    }

    Mat grayImage(image.rows, image.cols, CV_8UC1);
    // Recorrer la imagen y mostrar los valores de los píxeles (en BGR)
    #pragma omp parallel for num_threads(numHilos)
    for(int r=0; r<image.rows; r++) {
        for(int c=0; c<image.cols; c++) {
            Vec3b pixel = image.at<Vec3b>(r,c);
            // x:B y:G z:R
            uchar luminosity = 0.3*pixel[2] + 0.59*pixel[1] + 0.11*pixel[0];
            grayImage.at<uchar>(r,c) = luminosity;
        }
    }

    imwrite(nombreImagenSalida, grayImage);
    cout << "Imagen en gris creada con exito\n";
    cout << "hola tonotos\n";
    int b = 0;
    cout << "b es igual a: " << b << "\n";

    return 0;
}

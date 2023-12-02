#include <omp.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

using namespace cv;
using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[]) {
    // Verificación de argumentos en la línea de comandos
    if(argc != 4){
        cout << "Uso: " << argv[0] << " <imagen_entrada> <imagen_salida> <numero_hilos>\n";
        return -1;
    }

    // Almacenamiento de argumentos en variables
    string nombreImagenEntrada = argv[1];
    string nombreImagenSalida = argv[2];
    int numHilos = atoi(argv[3]);

    cout << "Imagen de entrada: " << nombreImagenEntrada << endl;

    // Lectura de la imagen desde el archivo
    Mat image = imread(nombreImagenEntrada, IMREAD_COLOR);

    // Verificar si la imagen se cargó correctamente
    if (image.empty()) {
        cout << "No se pudo cargar la imagen." << endl;
        return -1;
    }

    // Creación de una imagen en escala de grises
    Mat grayImage(image.rows, image.cols, CV_8UC1);

    // Comienzo de la medición del tiempo de ejecución
    auto start_time = high_resolution_clock::now();

    // Bucle para convertir la imagen a escala de grises (paralelizado con OpenMP)
    #pragma omp parallel for num_threads(numHilos)
    for(int r=0; r<image.rows; r++) {
        for(int c=0; c<image.cols; c++) {
            Vec3b pixel = image.at<Vec3b>(r,c);
            // Cálculo de luminosidad usando los canales R, G y B
            uchar luminosity = 0.3*pixel[2] + 0.59*pixel[1] + 0.11*pixel[0];
            // Asignación de la luminosidad a la imagen en escala de grises
            grayImage.at<uchar>(r,c) = luminosity;
        }
    }

    // Escritura de la imagen en escala de grises en un archivo
    imwrite(nombreImagenSalida, grayImage);
    cout << "Imagen en gris creada con exito\n";

    // Fin de la medición del tiempo de ejecución y cálculo de la duración
    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<seconds>(end_time - start_time);

    // Mensaje con el tiempo de ejecución
    cout << "Tiempo de ejecucion: " << duration.count() << " segundos" << endl;

    return 0;
}

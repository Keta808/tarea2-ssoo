A continuacion se explica como compilar la version secuencial del codigo para transformar
imagenes a color a escala de grises:

Requisitos previos:
-Tener instalado git.
-Tener instalado OpenCV.
-Ingresar una imagen .jpg a color (que pese al menos MB)

Ejecucion:
1.- Tener una terminal abierta.
1.- Clonar el repositorio usando: git clone <link_repositorio> (eliminar "<>").
2.- Ingresar al directorio del proyecto usando: cd tarea2-ssoo
3.- Ejecutar el comando: make
4.- Ejecutar el comando: ./secuencial imagen_a_color.jpg imagen_gris.jpg 
    Donde imagen_a_color.jpg debe ser reemplazado por el nombre de la imagen que se quiere
    transformar y imagen_gris.jpg es el nombre de la imagen que se obtendra.
5.- Luego de eso se mostrara en la terminal cuanto tardo en llevarse a cabo la transformacion y a la izquierda en el directorio del codigo aparecera la imagen en escala de grises.
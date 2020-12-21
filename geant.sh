#!/bin/bash

#////////////////////////////////////////////
# Proceso de instalación de Geant4 en bash shell
#////////////////////////////////////////////
#=======================================================================
# Definición de variables. Los valores son editables.

PATH_TO_USE="/usr/local"   # Ruta donde se instala Geant
INSTALL_DIR="Geant4"                 # Carpeta donde se instala Geant
FILE_GEANT="geant4.10.06.p01.tar.gz" # Nombre del archivo descargado
VERSION_GEANT="geant4.10.06.p01"         # Versión de Geant a instalar
NUMBER_CORES="2"                     # Número de núcleos del procesador
#=======================================================================

#=======================================================================
#////////////////////////////////
# Descarga geant4 de la pagina web
#////////////////////////////////
echo "......."
echo "......."
echo "Descargando Geant4......."
if [ -e  $FILE_GEANT ]; then
    {
	echo "================================"
	echo "File $FILE_GEANT exists already." 
	echo "No need to download again!!"
	echo "================================"
    }
else
    wget http://cern.ch/geant4-data/releases/geant4.10.06.p01.tar.gz  
fi


#////////////////////////
# Descomprime el archivo
#////////////////////////
echo "......."
echo "......."
echo "Descomprimiendo Geant4......."
if [ -e  $VERSION_GEANT ]; then
    {
	echo "================================"
	echo "Directory $VERSION_GEANT exists already." 
	echo "No need to untar again!!"
	echo "================================"
    }
else
    tar zxvf $FILE_GEANT                                                                                    
fi


#////////////////////////
 # Borra el .tar
 #////////////////////////
#echo "Borrando .tar......"
#rm $FILE_GEANT


#////////////////////////
# Revisa si ya esta instalado Geant4
#////////////////////////
echo "......."
echo "......."
if [ -e  $PATH_TO_USE/$INSTALL_DIR ]; then
    sudo rm -rf $PATH_TO_USE/$INSTALL_DIR
fi


#////////////////////////////////
# Crea carpeta Geant4 en /path_to_use
#////////////////////////////////
echo "................"
echo "Creando carpeta de instalaci'on......"
sudo mkdir -p $PATH_TO_USE/$INSTALL_DIR                             

#///////////////////////////////////////////
 # Mueve carpeta de geant4 a /path_to_use/Geant4
#///////////////////////////////////////////
echo "......."
echo "Moviendo geant4 al directorio de instalación......"
sudo mv $VERSION_GEANT $PATH_TO_USE/$INSTALL_DIR                   

echo "......."
echo "......."
echo "Comienza la instalaci'on......"
echo "......."
echo "......."

#/////////////////////////
# Entra a /usr/local/Geant4
#////////////////////////
cd $PATH_TO_USE/$INSTALL_DIR

#////////////////////////////////////////////
# Crea carpeta /usr/local/Geant4/geant4...-build
#////////////////////////////////////////////
sudo mkdir -p $PATH_TO_USE/$INSTALL_DIR/$VERSION_GEANT-build

#/////////////////////////////////////////////
# Entra carpeta /usr/local/Geant4/geant4...-build 
#/////////////////////////////////////////////
cd $PATH_TO_USE/$INSTALL_DIR/$VERSION_GEANT-build

#////////////////////
# Repositorio y update
#////////////////////
sudo add-apt-repository "deb http://archive.ubuntu.com/ubuntu $(lsb_release -sc) main"
sudo apt-get update

#/////////////////////////////////
# Instalación de paquetes necesarios
#/////////////////////////////////
sudo apt install cmake build-essential libgl1-mesa-dev qt5-default
sudo apt install build-essential autoconf automake libxmu-dev zlibc libxerces-c-dev


#==================
#//////////////////////
#configuración de cmake
#PERRO TENER CUIDADO CON ESTO, PARA LA INSTALACION. 
#//////////////////////
sudo cmake -DCMAKE_INSTALL_PREFIX=$PATH_TO_USE/$INSTALL_DIR/$VERSION_GEANT-install -DGEANT4_INSTALL_DATA=ON -DGEANT4_USE_GDML=ON -DGEANT4_USE_QT=ON -DGEANT4_USE_OPENGL_X11=ON -DGEANT4_USE_SYSTEM_EXPAT=OFF $PATH_TO_USE/$INSTALL_DIR/$VERSION_GEANT

#/////////////////////
# Instalación de Geant4
#/////////////////////
sudo make -j$NUMBER_CORES
sudo make install


### Al tutorial
## https://us02web.zoom.us/rec/play/vJYqdeipqz03GoKX5QSDV_IqW47pLKysgSQY-_FezByyUyEKYQH0YuAXMbEg-gqaxZyj2tGJorse2rNP?continueMode=true&_x_zm_rtaid=OvQrsL05SCO8RZ0FJ8NoJg.1588880279339.76d7947142a634ccd8fa9a8e9cefcfa5&_x_zm_rhtaid=895
## Clave: 5u*$H6w!

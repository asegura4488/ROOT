/******************************************************************
 *                                                                 *
 *                                                                 *
 *                                                                 *
 *   Programa de procesos de dispersión  (README)                  *
 *                                                                 *
 *                                                                 *
 *                                                                 *
 *   Este programa genera eventos A+B -> C+D  	                   *
 *                       					   *
 *                          					   *
 *                                                                 *
 *   Autor:       Manuel Alejandro Segura D                        *
 *                Universidad Distrital FJC                        *
 *                Proyecto de Licenciatura en Física               *   	 
 *                Grupo de investigación FISINFOR                  *
 ******************************************************************/ 

En el presente readme se busca contestar las preguntas más frecuentes de los usuarios 
de este recurso educativo, respecto a la programación y el uso de esta simulación en 
el ambiente Linux.

Grupo de Archivos:
En la carpeta proceso de ubican los archivos principales de la simulación. Estos archivos son:

proceso.C  El archivo del código fuente principal

Makefile: El archivo de compilación

/include: Carpeta que contiene el archivo de variables (variables.h), el de histogramas (hist_dec.h), las características del los histogramas (booking.h) y el llamado a bibliotecas de ROOT-C++ (ROOT.h).

Código fuente: 
Al ejecutar la simulación a través de ejecutable ./proceso se encuentran las siguientes opciones:

Este programa tiene opciones de comando, aquí se da un ejemplo:

/*./proceso -[opción] 
-E<Energía del fotón>   :Energía del fotón -E2.0  (Significa 2.0GeV)
-e<Número de eventos>   :Número de eventos para ser generados -e20000
-o<Archivo de salida>   :Nombre del archivo de datos -omisdatos
                         La extensión esta hecha por el código
-l<Distribución-energía>:Eventos de energía por eventos generados
                      Por defecto se tiene un beam de energía E única*/


cada opción determina el valor de algunas variables necesarias para la ejecución de la simulación:
-E   es la energía del fotón en el marco de referencia del laboratorio y se mide en GeV

-e   es el número de eventos que se van a generar en la simulación

-o   es la opción para darle un nombre al archivo de datos que se genera con la simulación 

-l   es un opción para tener por defecto un haz distribuido de manera uniforme en el intervalo 0-E

Los archivos de datos y de histogramas se crean a partir de la clase TFile de la siguiente forma:

/*
sprintf(file_dat,"%s_%d.dat",file_name,run);
  sprintf(file_root,"%s_%d.root",file_name,run);
  TFile *f = new TFile(file_root,"RECREATE");		//Creando los archivos Dat y Root
  ofstream outfile(file_dat);
  outfile.precision(DIGIT);  
  outfile << NEVENT << endl;    */        

la distribución de energía esta relacionada con la función 

/*for(int j = 0; j<loope; j++){
     if(loope==1){					//condicion para distribucion de energia
     n=EG;
     }else{n=gRandom->Uniform(0,EG);}
  
     TLorentzVector pgl(0.0, 0.0, n, n);    	}	// Cuadrimomento de Beam*/

Esta función genera un número aleatorio de manera uniforme entre 0-EG y se asigna ese valor al cuadri-momento del fotón.

Para hacer el Boost en el centro de masas se tienen las siguientes funciones:

/*     
     beta = w.Rho()/w.E();			//Calculando la velocidad del centro de masas
      
     beta_w.SetZ(-beta);
      
     TLorentzRotation LAB_CM;

     LAB_CM.Boost(beta_w);    
*/   

(Mirar el Manual de ROOT-C++ para ampliar la información de estas clases)


Para llenar los histogramas se utiliza el servicio Fill. Ejemplo:
 
Para la distribución angular del coseno de \theta para el \K^{+} se tiene:
 
dkcos->Fill(pkpl.CosTheta());    			 //Distribucion en coseno theta del kaon

El arhivo de compilación Makefile tiene la siguiente configuración:

Para configurar el sistema Linux de modo que se pueda compilar códigos fuentes (de ROOT-C++) a través de un archivo Makefile se debe ajustar el archivo {\bfseries .bashrc} del sistema. Para encontrar y abrir el archivo se ejecuta lo siguiente en la carpeta personal:


[alejandro@localhost ~]\$ gedit ~ .bashrc

Agregar las siguientes lineas después de abrir el archivo, guardar y cerrar todas las terminales para establecer la configuración. 

export ROOTSYS=(Ubicación de los archivos de ROOT-C++)
export PATH=$PATH:$ROOTSYS/bin
#Add $ROOTSYS/lib to your $LD_LIBRARY_PATH
export LD_LIBRARY_PATH=${ROOTSYS}/lib:${LD_LIBRARY_PATH}

export ROOTSYS=!Ojo aquí se escribe la ubicación 
de los archivos de ROOT-C++!, por ejemplo: 

---------------------------------------------------------
export ROOTSYS=/home/alejandro/software/root/
export PATH=$PATH:$ROOTSYS/bin
#Add $ROOTSYS/lib to your $LD_LIBRARY_PATH
export LD_LIBRARY_PATH=${ROOTSYS}/lib:${LD_LIBRARY_PATH}
---------------------------------------------------------

El arhivo Makefile tiene el siguiente aspecto:

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

######################
### Edit this part ###
######################

//ROOTSYS     = /cygdrive/c/root5.12/root
ROOTSYS       = /usr/local/root   //UBICACIÓN DE ROOT-C++
CXX           = g++
LD            = g++

#############################
### Do NOT edit this part ###
#############################

CXXFLAGS      = -O -Wall -I$(ROOTSYS)/include 
LDFLAGS       = -g
ROOTLIBS      = $(shell $(ROOTSYS)/bin/root-config --libs)
#ROOTLIBS      = -L$(ROOTSYS)/lib -lRoot -lCint
LIBS          = $(ROOTLIBS) -lm
LIBSALL       = $(ROOTLIBS) -lXm -lXt -lX11 -lm -lPW -lcurses
 

proceso:  proceso.o
	$(LD) $(LDFLAGS) proceso.o $(LIBS) -o proceso 
 
.C.o:
	
	$(CXX) $(CXXFLAGS) -c $<
clean: 
	rm *.o 
	rm *.dat
	rm *.root
	rm proceso

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


Una vez realizada la configuración anterior se ejecuta dentro de la carpeta principal (proceso) la siguiente instrucción:


[alejandro@localhost proceso]\$ make


Cuando se modifica el software se debe limpiar la compilación anterior y luego compilar nuevamente:



[alejandro@localhost proceso]\$ make clean  //limpiar
[alejandro@localhost proceso]\$ make        //compilar

-------------------------------------------------------------------------------------------

En el tercer bloque se definen tres archivos para el manejo de la simulación, con las siguientes características:

/include/variables.h

En este archivo se declaran todas las variables y los cuadri-vectores que se utilizan en la 
simulación. Ejemplo: TLorentzVector A; Int_t e;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/include/hist_dec.h
En este archivo se declaran los directorios contenedores y los histogramas. Ejemplo: 
TDirectoryFile *Kaon;  TH1F* masaKaon;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

/include/booking.h|
Aquí se escriben las características de los histogramas (nbines, intervalo, título, etiqueta de las variables, etc).

Ejemplo del canal t:

  canalt1 = new TH1F("canalt1","Canal t, Momentum transferido",1000, -6,6);
  
  /*número de bines 1000. intervalo de gráfica (-6, 6)*/
 
  canalt1->GetXaxis()->SetTitle("Canal t, laboratorio");
  canalt1->GetYaxis()->SetTitle("Frecuencia");
  canalt1->GetXaxis()->CenterTitle();
  canalt1->GetYaxis()->CenterTitle();
  canalt1->SetLineColor(4);

  /*Etiquetas*/ 
  
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%










Back_folder="$HOME/Libros/Data/ISR/background"
Signal_folder="$HOME/Libros/Data/ISR/signal"
Data_folder="$HOME/Libros/Data/ISR/data"

#Back_folder="$HOME/Libros/Data/PhenoISR/background"
#Signal_folder="$HOME/Libros/Data/PhenoISR/signal"
#Data_folder="$HOME/Libros/Data/PhenoISR/data"


MyHistos="histos"
MySignal="signal"
MyBackground="background"
MyData="data"
MyPseudoData="pseudodata"
MySB="Sbhistos"

#Folder="PhenoConfig"
Folder="config"


# Creating folders:
 echo Creating Histos directory...
 if [ -d $MyHistos ]; then
   rm -r $MyHistos
   mkdir -p $MyHistos
 else
   mkdir -p $MyHistos
 fi


 cd $MyHistos
 echo Creating signal directory...
 if [ -d $MySignal ]; then
   rm -r $MySignal
   mkdir -p $MySignal
 else
   mkdir -p $MySignal
 fi
 echo Creating background directory...
 if [ -d $MyBackground ]; then
   rm -r $MyBackground
   mkdir -p $MyBackground
 else
   mkdir -p $MyBackground
 fi
 echo Creating data directory...
 if [ -d $MyData ]; then
   rm -r $MyData
   mkdir -p $MyData
 else
   mkdir -p $MyData
 fi
 cd -

# Copying original file locally

for i in `cat $Folder/signal.in`
do
    echo Copying signal $i file ...
	cp $Signal_folder/$i.root ./$MyHistos/$MySignal/ &
done

for i in `cat $Folder/background.in`
do
        echo Copying background $i file ...
	cp $Back_folder/$i.root ./$MyHistos/$MyBackground/ &
done

for i in `cat $Folder/data.in`
do
        echo Copying data $i file ...
	cp $Data_folder/$i.root ./$MyHistos/$MyData/ &
done
    wait

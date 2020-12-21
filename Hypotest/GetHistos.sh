Back_folder="$HOME/Libros/Data/PhenoISR/background"
Signal_folder="$HOME/Libros/Data/PhenoISR/signal"
Data_folder="$HOME/Libros/Data/PhenoISR/data"

#Back_folder="$HOME/Libros/Data/ISR_Obin/background"
#Signal_folder="$HOME/Libros/Data/ISR_Obin/signal"
#Data_folder="$HOME/Libros/Data/ISR_Obin/data"

MyHistos="histos"
MySignal="signal"
MyBackground="background"
MyData="data"
MyPseudoData="pseudodata"
MySB="Sbhistos"

Folder="config"
#Folder="ISRconfig"

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
 echo Creating pseudodata directory...
 if [ -d $MyPseudoData ]; then
   rm -r $MyPseudoData
   mkdir -p $MyPseudoData
 else
   mkdir -p $MyPseudoData
 fi
 echo Creating S+B histo directory...
 if [ -d $MySB ]; then
   rm -r $MySB
   mkdir -p $MySB
 else
   mkdir -p $MySB
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
# All MC file

if [ -s "./$MyHistos/$MyBackground/MC.root" ]; then
        rm ./$MyHistos/$MyBackground/MC.root
        hadd -f ./$MyHistos/$MyBackground/MC.root ./$MyHistos/$MyBackground/*.root
else
        hadd -f ./$MyHistos/$MyBackground/MC.root ./$MyHistos/$MyBackground/*.root
fi

# creating S+B histos

for i in `cat $Folder/signal.in`
do
        echo Adding signal $i plus total background in parallel ...
        hadd -f  ./$MyHistos/$MySB/Sb_$i.root ./$MyHistos/$MySignal/$i.root ./$MyHistos/$MyBackground/MC.root  &
done
        wait
        ls ./$MyHistos/$MySB/ > ./$Folder/signalb.in
        sed -i 's|.root||g' "./$Folder/signalb.in"

echo    "************************************************************************************"
echo -e "Building library zip file for Mega2560_Ports\n"

#update our version
VERSION=`cat VERSION`

#update our filename
ZIPNAME=Mega2560_Ports-$VERSION.zip
echo "Filename is: " $ZIPNAME
echo ""

#Checking for zip
zip --version > /dev/null 2>&1
if [ $? == 0 ]
then
   echo "Zipping base directory of the project..."
   zip    lib-out/$ZIPNAME library.properties keywords.txt README.md LICENSE
   echo "Zipping src files for the library..."
   zip -r lib-out/$ZIPNAME src/*.h src/*.c src/*.hpp src/*.cpp 
   echo "Zipping test system for the library..."
   zip -r lib-out/$ZIPNAME tests/*.ino tests/*.h tests/*.c tests/*.hpp tests/*.cpp 
   echo "Zipping examples directory..."
   zip -r lib-out/$ZIPNAME examples/*
   
fi




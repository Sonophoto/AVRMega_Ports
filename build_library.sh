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
   zip    lib-out/$ZIPNAME library.properties keywords.txt README.md LICENSE
   zip -r lib-out/$ZIPNAME src/*
   zip -r lib-out/$ZIPNAME tests/*
   zip -r lib-out/$ZIPNAME examples/*
   zip -r lib-out/$ZIPNAME schematics/*
   
fi




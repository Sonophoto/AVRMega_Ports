echo    "************************************************************************************"
echo -e "Building library zip file for Mega2560_Ports\n"


zip -rm lib-out/Mega2560_Ports.zip examples/*
zip -rm lib-out/Mega2560_Ports.zip src/*
zip -rm lib-out/Mega2560_Ports.zip tests/*
zip -rm lib-out/Mega2560_Ports.zip schematics/*
zip -m  lib-out/Mega2560_Ports.zip library.properties keywords.txt README.md LICENSE

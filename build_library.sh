echo    "************************************************************************************"
echo -e "Building library zip file for Mega2560_Ports\n"

zip lib-out/Mega2560_Ports.zip library.properties keywords.txt README.md LICENSE
zip -r lib-out/Mega2560_Ports.zip src/*
zip -r lib-out/Mega2560_Ports.zip tests/*
zip -r lib-out/Mega2560_Ports.zip examples/*
zip -r lib-out/Mega2560_Ports.zip schematics/*

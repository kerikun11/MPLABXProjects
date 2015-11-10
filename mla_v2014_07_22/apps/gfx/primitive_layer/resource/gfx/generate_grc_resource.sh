#!/bin/sh
# Unzip the file first
#echo Unzipping target
#targetName="$(ls *.zip)"
#unzip -o $targetName

# run as ./generate_grc_resource.sh

echo Creating primitive test routine resources
# set grc.jar path
grcpath=../../../../../framework/gfx/utilities/grc

# set xml file name
xmlfile=internal_resource_primitive_layer.xml
java -jar $grcpath/grc.jar -XML $xmlfile -O ../../firmware/src/internal_resource.S


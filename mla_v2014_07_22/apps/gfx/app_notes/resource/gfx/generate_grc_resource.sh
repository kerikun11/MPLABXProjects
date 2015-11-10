#!/bin/sh
# Unzip the file first
#echo Unzipping target
#targetName="$(ls *.zip)"
#unzip -o $targetName

# run as ./generate_grc_resource.sh

echo Creating application note demo resources
# set grc.jar path
grcpath=../../../../../framework/gfx/utilities/grc

# set xml file name
xmlfile=an1136_resource/an1136_graphics_resource.xml
java -jar $grcpath/grc.jar -XML $xmlfile -O ../../firmware/src/internal_resource_an1136.S

# set xml file name
xmlfile=an1182_resource/an1182_graphics_resource.xml
java -jar $grcpath/grc.jar -XML $xmlfile -O ../../firmware/src/internal_resource_an1182.S

# set xml file name
xmlfile=collated_appnotes.xml
java -jar $grcpath/grc.jar -XML $xmlfile -O ../../firmware/src/internal_resource_main.S

# set xml file name
xmlfile=collated_appnotes_external.xml
java -jar $grcpath/grc.jar -XML $xmlfile -O ../../firmware/src/external_resource_main.hex



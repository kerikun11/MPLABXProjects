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
xmlfile=1BPP/internal_resource_color_depth_1bpp_mode_ipu.xml
java -jar $grcpath/grc.jar -XML $xmlfile -O ../../firmware/src/internal_resource_1bpp_mode_ipu.S

# set xml file name
xmlfile=1BPP/internal_resource_color_depth_1bpp_mode.xml
java -jar $grcpath/grc.jar -XML $xmlfile -O ../../firmware/src/internal_resource_1bpp_mode.S

# set xml file name
xmlfile=4BPP/internal_resource_color_depth_4bpp_mode_ipu.xml
java -jar $grcpath/grc.jar -XML $xmlfile -O ../../firmware/src/internal_resource_4bpp_mode_ipu.S

# set xml file name
xmlfile=4BPP/internal_resource_color_depth_4bpp_mode.xml
java -jar $grcpath/grc.jar -XML $xmlfile -O ../../firmware/src/internal_resource_4bpp_mode.S

# set xml file name
xmlfile=8BPP/internal_resource_color_depth_8bpp_mode_ipu.xml
java -jar $grcpath/grc.jar -XML $xmlfile -O ../../firmware/src/internal_resource_8bpp_mode_ipu.S

# set xml file name
xmlfile=8BPP/internal_resource_color_depth_8bpp_mode.xml
java -jar $grcpath/grc.jar -XML $xmlfile -O ../../firmware/src/internal_resource_8bpp_mode.S




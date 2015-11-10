REM @echo off
REM Set the path to the Graphics Resource Converter (grc.jar)
@set GRCPATH=%../../../../../framework/gfx/utilities/grc
java -jar %GRCPATH%/grc.jar -XML an1136_resource/an1136_graphics_resource.xml -O "../../firmware/src/internal_resource_an1136.S"
java -jar %GRCPATH%/grc.jar -XML an1182_resource/an1182_graphics_resource.xml -O "../../firmware/src/internal_resource_an1182.S"
java -jar %GRCPATH%/grc.jar -XML collated_appnotes.xml -O "../../firmware/src/internal_resource_main.S"

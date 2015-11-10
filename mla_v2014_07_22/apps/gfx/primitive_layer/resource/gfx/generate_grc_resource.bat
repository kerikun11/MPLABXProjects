REM @echo off
REM set the project name
@set PROJECTNAME=%primitive_layer
REM Set the path to the Graphics Resource Converter (grc.jar)
@set GRCPATH=%../../../../../framework/gfx/utilities/grc
java -jar %GRCPATH%/grc.jar -XML "internal_resource_%PROJECTNAME%.xml" -O ../internal_resource.S

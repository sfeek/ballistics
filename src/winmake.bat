#echo off
del *.obj
del *.exe
cl bc.c ..\lib\ballistics.c ..\lib\bclib.c
@echo off

SET source=libraries
SET destination=%USERPROFILE%\Documents\Arduino\libraries

ECHO Copying files from "%source%" to "%destination%"...

XCOPY "%source%" "%destination%" /W /F /T /E

ECHO Done.

PAUSE

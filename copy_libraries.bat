@echo off

SET source=libraries
SET destination=C:\Program Files (x86)\Arduino\libraries

ECHO Copying files from "%source%" to "%destination%"...

XCOPY "%source%" "%destination%" /t /e

ECHO Done.

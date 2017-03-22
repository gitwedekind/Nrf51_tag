rem @echo off
REM Module Name: clean.cmd
REM Description: clean auto-generated files 

setlocal

del EventRecorderStub.scvd
del JlinkLog.txt
del JLinkSettings.ini
del RI-tag.uvguix.*
rmdir /S /Q _build

CLS
DIR

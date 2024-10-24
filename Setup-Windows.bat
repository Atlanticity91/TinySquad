@echo off

set scriptpath=%~dp0

pushd ..
cls

echo === TinyEngine Setup ===

rmdir /s /q TinySquad\bin-int\

del /s TinySquad\TinySquad.sln
del /s TinySquad\bin\TinyEngine.lib TinySquad\bin\TinyMicro.lib TinySquad\bin\TinyThirdparty.lib
del /s TinySquad\bin\*.exp TinySquad\bin\*.pdb TinySquad\bin\*.idb TinySquad\bin\*.exe
del /s TinySquad\*.vcxproj TinySquad\*.filters TinySquad\*.user
del /s TinySquad\*.csproj

TinySquad\Premake\Windows\premake5.exe --file=TinySquad\Build.lua vs2022
popd

pause

@echo off

pushd ..
TinySquad\Premake\Windows\premake5.exe --file=TinySquad\Build.lua vs2022
popd

pause

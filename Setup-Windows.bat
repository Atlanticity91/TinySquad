@echo off

pushd ..
cls

echo === TinyEngine Setup ===

rmdir /s /q TinySquad\bin-int\

del TinySquad\TinySquad.sln
del /s TinySquad\bin\TinyEngine.lib TinySquad\bin\TinyMicro.lib TinySquad\bin\TinyThirdparty.lib
del /s TinySquad\bin\*.exp TinySquad\bin\*.pdb TinySquad\bin\*.idb TinySquad\bin\*.exe
del /s TinySquad\*.vcxproj TinySquad\*.filters TinySquad\*.user

TinySquad\Premake\Windows\premake5.exe --file=TinySquad\Build.lua vs2022
popd

pause

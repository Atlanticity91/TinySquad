#!/bin/bash

pushd ..
TinySquad/Premake/Linux/premake5 --cc=clang --file=TinySquad/Build.lua gmake2
popd

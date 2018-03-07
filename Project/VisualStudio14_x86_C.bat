@echo off
set PATH="C:\Program Files (x86)\CMake\bin\";%PATH%
mkdir VisualStudio14
cd VisualStudio14
cmake -G "Visual Studio 14" ../
pause
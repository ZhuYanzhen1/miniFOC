md cmake-build-debug
cd cmake-build-debug
cmake.exe -DCMAKE_BUILD_TYPE=Debug -DCMAKE_DEPENDS_USE_COMPILER=FALSE -G "CodeBlocks - MinGW Makefiles" ..\
cmake.exe --build .\ --target miniFOC.elf -- -j 12
echo Build Firmware Success!!!
pause 0
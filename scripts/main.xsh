mkdir build
cd build

runFile ./../tools/cmake/CMake.app/Contents/bin/cmake ..

runFile make

cd ../bin/debug

chmod +x ./main
runFile ./main

cd ../..
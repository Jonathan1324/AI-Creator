mkdir build
cd build

runFile ./../tools/cmake/CMake.app/Contents/bin/cmake -G Ninja -DCMAKE_MAKE_PROGRAM=/Users/jonathan/Desktop/Develop/AI-Creator/tools/ninja/ninja ..

runFile ../tools/ninja/ninja

cd ..

call chmod

cd ./bin/debug

runFile ./main
mkdir build
cd build

runFile ./../tools/cmake/CMake.app/Contents/bin/cmake -G Ninja -DCMAKE_MAKE_PROGRAM=/Users/jonathan/Desktop/Develop/AI-Creator/tools/ninja/ninja ..

runFile ../tools/ninja/ninja

cd ../bin/debug

chmod +x ./main
runFile ./main

chmod +x ../release/main

cd ../..
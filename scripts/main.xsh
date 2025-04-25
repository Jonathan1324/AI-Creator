mkdir build
cd build

runWindows ./../tools/cmake/bin/cmake -G Ninja -DCMAKE_MAKE_PROGRAM=..\tools\ninja\ninja ..
runMac ./../tools/cmake/CMake.app/Contents/bin/cmake -G Ninja -DCMAKE_MAKE_PROGRAM=../tools/ninja/ninja ..
runLinux ./../tools/cmake/bin/cmake -G Ninja -DCMAKE_MAKE_PROGRAM=../tools/ninja/ninja ..

runFile ../tools/ninja/ninja

cd ../bin

call ../$BUILD_DIR/chmod

cd ./debug

runFile ./main
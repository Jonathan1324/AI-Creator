runBatch setlocal
call ./$BUILD_DIR/mkdir

getPath abs

cd build

runWindows ./../tools/cmake/bin/cmake -G Ninja -DCMAKE_MAKE_PROGRAM=%abs%\tools\ninja\ninja ..
runMac ./../tools/cmake/CMake.app/Contents/bin/cmake -G Ninja -DCMAKE_MAKE_PROGRAM=$abs/tools/ninja/ninja ..
runLinux ./../tools/cmake/bin/cmake -G Ninja -DCMAKE_MAKE_PROGRAM=$abs/tools/ninja/ninja ..

runFile ../tools/ninja/ninja

cd ../bin

call ../$BUILD_DIR/chmod

cd ./debug

runBatch if "%1"=="--run" ( .\main )
runBatch if "%1"=="-r" ( .\main )

runShell if [ "$1" == "--run" ]; then ./main
runShell if [ "$1" == "-r" ]; then ./main

runBatch endlocal
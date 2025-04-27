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

runBatch if "%1"=="--run" ( .\main ) else (
runBatch set /p input="Enter 1 to execute: "
runBatch if "%input%"=="1" .\main )

runShell if [ "$1" == "--run" ]; then ./main; else
runShell read -p "Enter 1 to execute: " input
runShell if [ "$input" -eq 1 ]; then ./main; fi; fi

runBatch endlocal
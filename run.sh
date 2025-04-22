chmod +x ./toolchain/bootstrap/bootstrap.sh
sh ./toolchain/bootstrap/bootstrap.sh

./tools/deno run --allow-read --allow-run --allow-net --allow-write ./toolchain/main.ts

mkdir build
cd build

./../tools/cmake/CMake.app/Contents/bin/cmake ..

make

cd ../debug

chmod +x ./main
./main

cd ..
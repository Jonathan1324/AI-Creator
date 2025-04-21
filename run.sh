chmod +x ./bootstrap/bootstrap.sh
sh ./bootstrap/bootstrap.sh

./tools/deno run --allow-read --allow-run --allow-net --allow-write ./toolchain/setup.ts

#make clean
#make all
#cd debug
#./main
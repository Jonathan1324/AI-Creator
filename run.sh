chmod +x ./toolchain/bootstrap/bootstrap.sh
sh ./toolchain/bootstrap/bootstrap.sh

./tools/deno run --allow-read --allow-run --allow-net --allow-write ./toolchain/main.ts

source ./build_scripts/main.sh $1
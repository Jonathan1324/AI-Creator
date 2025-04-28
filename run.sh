chmod +x ./toolchain/deno-setup/deno-setup.sh
sh ./toolchain/deno-setup/deno-setup.sh

./tools/deno run --allow-read --allow-run --allow-net --allow-write ./toolchain/main.ts

source ./build/build_scripts/main.sh $1
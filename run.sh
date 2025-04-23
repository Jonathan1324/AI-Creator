chmod +x ./toolchain/bootstrap/bootstrap.sh
sh ./toolchain/bootstrap/bootstrap.sh

./tools/deno run --allow-read --allow-run --allow-net --allow-write ./toolchain/main.ts

./build-scripts/main.sh
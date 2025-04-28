import { install } from "./install/main.ts"
import { transpileXsh } from "./extendedshell/main.ts"

import { deleteFolderRecursive } from "./utils/folder.js"

async function main() {
    await install();

    await deleteFolderRecursive("build/build_scripts");
    await transpileXsh("./toolchain/scripts/", "build/build_scripts");
}

await main();
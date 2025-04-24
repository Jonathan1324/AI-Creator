import { setup } from "./setup/setup.ts"
import { transpileXsh } from "./extendedshell/main.ts"

import { deleteFolderRecursive } from "./files/folder.js"

async function main() {
    await setup();

    await deleteFolderRecursive("./build_scripts/");
    await transpileXsh("./scripts/", "./build_scripts/");
}

await main();
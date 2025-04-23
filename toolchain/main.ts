import { setup } from "./setup/setup.ts"
import { transpileXsh } from "./extendedshell/main.ts"

import { deleteFolderRecursive } from "./files/folder.ts"

async function main() {
    await setup();

    await deleteFolderRecursive("./build-scripts/");
    await transpileXsh("./scripts/", "./build-scripts/");
}

await main();
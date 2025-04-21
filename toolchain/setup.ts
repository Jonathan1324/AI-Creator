import { downloadTool, unzipFile, fileExists, createDir, deleteFile } from "./setup/util.ts";

let makeExecutable = "";

async function installMake() {
    // placeholder
}

async function main() {
    await installMake();

    if (Deno.build.os !== "windows") {
        await Deno.run({
            cmd: ["chmod", "+x", makeExecutable],
        }).status();
    }
}

await main();
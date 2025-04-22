import { downloadTool, unzipFile, fileExists, createDir, deleteFile } from "./setup/util.ts";

async function installCMake(): Promise<string> {
    const cmakeVersion: string = "4.0.1";

    const cmakeUrlWindows: string = `https://github.com/Kitware/CMake/releases/download/v${cmakeVersion}/cmake-${cmakeVersion}-windows-x86_64.zip`;
    const cmakeUrlLinux: string = `https://github.com/Kitware/CMake/releases/download/v${cmakeVersion}/cmake-${cmakeVersion}-linux-x86_64.tar.gz`;
    const cmakeUrlMac: string = `https://github.com/Kitware/CMake/releases/download/v${cmakeVersion}/cmake-${cmakeVersion}-macos10.10-universal.tar.gz`;
    const cmakeDestWindows: string = "./tools/cmake.zip";
    const cmakeDestLinuxMac: string = "./tools/cmake.tar.gz";
    const installDir: string = "./tools";

    var cmakeFile: string = "./tools/cmake/";
  
    if (Deno.build.os === "windows") {
        cmakeFile += "bin/cmake.exe";

        const cmakeExists = await fileExists(cmakeFile);
        if (cmakeExists) {
            return cmakeFile;
        }
  
        await downloadTool(cmakeUrlWindows, cmakeDestWindows);
  
        await unzipFile(cmakeDestWindows, installDir);

        await Deno.rename(`./tools/cmake-${cmakeVersion}-windows-x86_64`, "./tools/cmake");

        deleteFile(cmakeDestWindows);
    } else {
        cmakeFile += Deno.build.os === "linux" ? "bin/cmake" : "CMake.app/Contents/bin/cmake"

        const cmakeExists = await fileExists(cmakeFile);
        if (cmakeExists) {
            return cmakeFile;
        }
  
        await downloadTool(Deno.build.os === "linux" ? cmakeUrlLinux : cmakeUrlMac, cmakeDestLinuxMac);

        await Deno.run({
            cmd: ["tar", "-xvzf", cmakeDestLinuxMac, "-C", installDir],
            stdout: "null",
            stdeer: "piped",
        }).status();

        await Deno.rename(Deno.build.os === "linux" ? `./tools/cmake-${cmakeVersion}-linux-x86_64` : `./tools/cmake-${cmakeVersion}-macos10.10-universal`, "./tools/cmake");

        deleteFile(cmakeDestLinuxMac);
    }

    return cmakeFile;
}

async function installNinja(): Promise<string> {
    const ninjaVersion: string = "1.12.1";

    const ninjaUrlWindows: string = `https://github.com/ninja-build/ninja/releases/download/v${ninjaVersion}/ninja-win.zip`;
    const ninjaUrlLinux: string = `https://github.com/ninja-build/ninja/releases/download/v${ninjaVersion}/ninja-linux.zip`;
    const ninjaUrlMac: string = `https://github.com/ninja-build/ninja/releases/download/v${ninjaVersion}/ninja-mac.zip`;
    const ninjaDest: string = "./tools/ninja.zip";
    const installDir: string = "./tools/ninja";

    var ninjaFile: string = "./tools/ninja/ninja";
  
    if (Deno.build.os === "windows") {
        ninjaFile += ".exe"
        const ninjaExists = await fileExists(ninjaFile);
        if (ninjaExists) {
            return ninjaFile;
        }
  
        await downloadTool(ninjaUrlWindows, ninjaDest);
  
        await unzipFile(ninjaDest, installDir);
    } else {
        const ninjaExists = await fileExists(ninjaFile);
        if (ninjaExists) {
            return ninjaFile;
        }
        await downloadTool(Deno.build.os === "linux" ? ninjaUrlLinux : ninjaUrlMac, ninjaDest);
  
        await unzipFile(ninjaDest, installDir);
    }

    deleteFile(ninjaDest);

    return ninjaFile
}

async function downloadFiles() {
    const ninja: string = await installNinja();

    if (Deno.build.os !== "windows") {
        await Deno.run({
            cmd: ["chmod", "+x", ninja],
        }).status();
    }

    const cmake: string = await installCMake();

    if (Deno.build.os !== "windows") {
        await Deno.run({
            cmd: ["chmod", "+x", cmake],
        }).status();
    }
}

async function main() {
    await downloadFiles();
}

await main();
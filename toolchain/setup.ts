import { downloadTool, unzipFile, fileExists, createDir, deleteFile } from "./setup/util.ts";

async function installGNUGCC() {
    const gnugccUrlWindows: string = "https://github.com/brechtsanders/winlibs_mingw/releases/download/14.2.0posix-12.0.0-ucrt-r3/winlibs-x86_64-posix-seh-gcc-14.2.0-llvm-19.1.7-mingw-w64ucrt-12.0.0-r3.zip";
    const gnugccUrlLinux: string = "https://toolchains.bootlin.com/downloads/releases/toolchains/x86-64/tarballs/x86-64--glibc--bleeding-edge-2021.11-5.tar.bz2";
    const gnugccUrlMac: string = "https://www.dropbox.com/scl/fi/nbuzxjqclvsvqn21aziqs/gcc-macos.tar.gz?rlkey=64vwqeo5c7gfxbi1r9y5t6hhe&st=f6ybu0qi&dl=0";

    const gnugccDestWindows: string = "./tools/inlibs-x86_64-posix-seh-gcc-14.2.0-llvm-19.1.7-mingw-w64ucrt-12.0.0-r3.zip";
    const gnugccDestLinux: string = "./tools/x86-64--glibc--bleeding-edge-2021.11-5.tar.bz2"
    const gnugccDestMac: string = "./tools/gcc-macos.tar.gz";

    const installDir: string = "./tools/gnugcc/"

    Deno.mkdir(installDir, { recursive: true });

    if (Deno.build.os === "windows") {
        // TEST IT !!!!

        const gnugccInstalled = await fileExists("./tools/gnugcc/installed.txt");
        if (gnugccInstalled) {
            return;
        }

        await downloadTool(gnugccUrlWindows, gnugccDestWindows);
  
        await unzipFile(gnugccDestWindows, installDir);

        deleteFile(gnugccDestWindows);
    } else {
        const gnugccInstalled = await fileExists("./tools/gnugcc/installed.txt");
        if (gnugccInstalled) {
            return;
        }

        if(Deno.build.os === "linux") {
            // TEST IT !!!!

            await downloadTool(gnugccUrlLinux, gnugccDestLinux);

            await Deno.run({
                cmd: ["tar", "-xjzf", gnugccDestLinux, "-C", installDir],
                stdout: "null",
                stdeer: "piped",
            }).status();

            deleteFile(gnugccDestLinux);
        } else {
            await downloadTool(gnugccUrlMac, gnugccDestMac);

            await Deno.run({
                cmd: ["tar", "-xvzf", gnugccDestMac, "-C", installDir],
                stdout: "null",
                stdeer: "piped",
            }).status();

            deleteFile(gnugccDestMac);
        }
    }

    Deno.writeTextFile("./tools/gnugcc/installed.txt", ".");
}

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

    Deno.mkdir(installDir, { recursive: true });
  
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
    console.log("Installing Ninja...")
    const ninja: string = await installNinja();

    if (Deno.build.os !== "windows") {
        await Deno.run({
            cmd: ["chmod", "+x", ninja],
        }).status();
    }

    console.log("Installing CMake...")
    const cmake: string = await installCMake();

    if (Deno.build.os !== "windows") {
        await Deno.run({
            cmd: ["chmod", "+x", cmake],
        }).status();
    }

    console.log("Installing GNU GCC...")
    await installGNUGCC();
}

export async function setup() {
    await downloadFiles();
}
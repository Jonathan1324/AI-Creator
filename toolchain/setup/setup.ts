import { downloadTool, unzipFile, fileExists, _createDir, deleteFile, chmod } from "./util.ts";

async function installDocker(): Promise<string> {
    const version: string = "28.1.1";
    
    const dockerUrlWindows: string = `https://download.docker.com/win/static/stable/x86_64/docker-${version}.zip`;
    const dockerUrlLinux: string = `https://download.docker.com/linux/static/stable/x86_64/docker-${version}.zip`;
    const dockerUrlMac: string = `https://download.docker.com/mac/static/stable/x86_64/docker-${version}.zip`;

    const dockerDest: string = `./tools/docker-${version}.zip`;

    const installDir: string = "./tools/";

    let dockerFile: string = "./tools/docker/docker";

    Deno.mkdir(installDir, { recursive: true });

    if (Deno.build.os === "windows") {
        dockerFile += ".exe"
        const ninjaExists = await fileExists(dockerFile);
        if (ninjaExists) {
            return dockerFile;
        }

        console.log("Installing Docker...");
  
        await downloadTool(dockerUrlWindows, dockerDest);
  
        await unzipFile(dockerDest, installDir, false, false);
    } else {
        const ninjaExists = await fileExists(dockerFile);
        if (ninjaExists) {
            return dockerFile;
        }

        console.log("Installing Docker...");

        await downloadTool(Deno.build.os === "linux" ? dockerUrlLinux : dockerUrlMac, dockerDest);
  
        await unzipFile(dockerDest, installDir, false, false);
    }

    deleteFile(dockerDest);

    return dockerFile;
}

async function installGNUGCC(): Promise<string> {
    const gnugccUrlWindows: string = "https://github.com/brechtsanders/winlibs_mingw/releases/download/14.2.0posix-12.0.0-ucrt-r3/winlibs-x86_64-posix-seh-gcc-14.2.0-llvm-19.1.7-mingw-w64ucrt-12.0.0-r3.zip";
    const gnugccUrlLinux: string = "https://www.dropbox.com/scl/fi/hph006c1nrok9kkakel2n/gcc-linux.tar.gz?rlkey=0r7xrzgf1sv7mejowinn7mpd8&st=rfznlxq1&dl=0";
    const gnugccUrlMac: string = "https://www.dropbox.com/scl/fi/nbuzxjqclvsvqn21aziqs/gcc-macos.tar.gz?rlkey=64vwqeo5c7gfxbi1r9y5t6hhe&st=f6ybu0qi&dl=0";

    const gnugccDestWindows: string = "./tools/inlibs-x86_64-posix-seh-gcc-14.2.0-llvm-19.1.7-mingw-w64ucrt-12.0.0-r3.zip";
    const gnugccDestLinux: string = "./tools/x86-64--glibc--bleeding-edge-2021.11-5.tar.bz2"
    const gnugccDestMac: string = "./tools/gcc-macos.tar.gz";

    const installDir: string = "./tools/"

    Deno.mkdir(installDir, { recursive: true });

    const file = "./tools/gnugcc/installed.txt";

    if (Deno.build.os === "windows") {
        const gnugccInstalled = await fileExists(file);
        if (gnugccInstalled) {
            return file;
        }

        console.log("Installing GNU GCC...");

        await downloadTool(gnugccUrlWindows, gnugccDestWindows);
  
        await unzipFile(gnugccDestWindows, installDir, false, false);

        await Deno.rename(`./tools/mingw64`, "./tools/gnugcc");

        deleteFile(gnugccDestWindows);
    } else {
        const gnugccInstalled = await fileExists(file);
        if (gnugccInstalled) {
            return file;
        }

        console.log("Installing GNU GCC...");

        if(Deno.build.os === "linux") {
            await downloadTool(gnugccUrlLinux, gnugccDestLinux);

            await unzipFile(gnugccDestLinux, installDir, true, false);

            deleteFile(gnugccDestLinux);
        } else {
            await downloadTool(gnugccUrlMac, gnugccDestMac);

            await unzipFile(gnugccDestMac, installDir, true, false);

            deleteFile(gnugccDestMac);
        }
    }

    Deno.writeTextFile(file, ".");

    return file;
}

async function installCMake(): Promise<string> {
    const cmakeVersion: string = "4.0.1";

    const cmakeUrlWindows: string = `https://github.com/Kitware/CMake/releases/download/v${cmakeVersion}/cmake-${cmakeVersion}-windows-x86_64.zip`;
    const cmakeUrlLinux: string = `https://github.com/Kitware/CMake/releases/download/v${cmakeVersion}/cmake-${cmakeVersion}-linux-x86_64.tar.gz`;
    const cmakeUrlMac: string = `https://github.com/Kitware/CMake/releases/download/v${cmakeVersion}/cmake-${cmakeVersion}-macos10.10-universal.tar.gz`;
    const cmakeDestWindows: string = "./tools/cmake.zip";
    const cmakeDestLinuxMac: string = "./tools/cmake.tar.gz";
    const installDir: string = "./tools";

    let cmakeFile: string = "./tools/cmake/";
  
    if (Deno.build.os === "windows") {
        cmakeFile += "bin/cmake.exe";

        const cmakeExists = await fileExists(cmakeFile);
        if (cmakeExists) {
            return cmakeFile;
        }

        console.log("Installing CMake...");
  
        await downloadTool(cmakeUrlWindows, cmakeDestWindows);
  
        await unzipFile(cmakeDestWindows, installDir, false, false);

        await Deno.rename(`./tools/cmake-${cmakeVersion}-windows-x86_64`, "./tools/cmake");

        deleteFile(cmakeDestWindows);
    } else {
        cmakeFile += Deno.build.os === "linux" ? "bin/cmake" : "CMake.app/Contents/bin/cmake"

        const cmakeExists = await fileExists(cmakeFile);
        if (cmakeExists) {
            return cmakeFile;
        }

        console.log("Installing CMake...");
  
        await downloadTool(Deno.build.os === "linux" ? cmakeUrlLinux : cmakeUrlMac, cmakeDestLinuxMac);

        await unzipFile(cmakeDestLinuxMac, installDir, true, false);

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

    let ninjaFile: string = "./tools/ninja/ninja";

    Deno.mkdir(installDir, { recursive: true });
  
    if (Deno.build.os === "windows") {
        ninjaFile += ".exe"
        const ninjaExists = await fileExists(ninjaFile);
        if (ninjaExists) {
            return ninjaFile;
        }

        console.log("Installing Ninja...");
  
        await downloadTool(ninjaUrlWindows, ninjaDest);
  
        await unzipFile(ninjaDest, installDir, false, false);
    } else {
        const ninjaExists = await fileExists(ninjaFile);
        if (ninjaExists) {
            return ninjaFile;
        }

        console.log("Installing Ninja...");

        await downloadTool(Deno.build.os === "linux" ? ninjaUrlLinux : ninjaUrlMac, ninjaDest);
  
        await unzipFile(ninjaDest, installDir, false, false);
    }

    deleteFile(ninjaDest);

    return ninjaFile
}

async function downloadFiles() {
    const ninja: string = await installNinja();
    chmod(ninja, "x");

    const cmake: string = await installCMake();
    chmod(cmake, "x");

    await installGNUGCC();

    const docker: string = await installDocker();
    chmod(docker, "x");
}

export async function setup() {
    await downloadFiles();
}
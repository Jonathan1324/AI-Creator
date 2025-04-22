export async function downloadTool(url: string, dest: string) {
    console.log(`⬇️  Lade von ${url} herunter...`);
  
    let cmd: string[];

    if (Deno.build.os === "windows") {
      cmd = ["powershell", "-Command", `Invoke-WebRequest -Uri '${url}' -OutFile '${dest}'`];
    } else {
      cmd = ["curl", "-L", url, "-o", dest];
    }
  
    const process = Deno.run({
      cmd: cmd,
      stdout: "null",
      stderr: "piped",
    });
  
    const status = await process.status();
    if (!status.success) {
      const error = await process.stderrOutput();
      console.error(new TextDecoder().decode(error));
      Deno.exit(1);
    }
}

export async function unzipFile(zipPath: string, destDir: string) {
    let unzipCmd: string[];
  
    if (Deno.build.os === "windows") {
      unzipCmd = ["powershell", "-Command", `Expand-Archive -Path '${zipPath}' -DestinationPath '${destDir}'`]; // Windows
    } else {
      unzipCmd = ["unzip", "-o", zipPath, "-d", destDir];
    }
  
    const process = Deno.run({
      cmd: unzipCmd,
      stdout: "null",
      stderr: "piped",
    });
    
    const status = await process.status();
    
    if (!status.success) {
      const error = await process.stderrOutput();
      console.error(new TextDecoder().decode(error));
      Deno.exit(1);
    }
}

export async function fileExists(filePath: string): Promise<boolean> {
    try {
      const fileInfo = await Deno.stat(filePath);
      
      return true;
    } catch (error) {
      if (error instanceof Deno.errors.NotFound) {
        return false;
      }
      throw error;
    }
}

export async function createDir(path: string) {
  try {
    await Deno.mkdir(path, { recursive: true });
  } catch (error) {
    if (error instanceof Deno.errors.AlreadyExists) {} else {
      throw error;
    }
  }
}

export async function deleteFile(path: string) {
  try {
    await Deno.remove(path);
  } catch (error) {
    if (error instanceof Deno.errors.NotFound) {
    } else {
      throw error;
    }
  }
}
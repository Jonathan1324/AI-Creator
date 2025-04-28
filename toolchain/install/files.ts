export async function unzipFile(zipPath: string, destDir: string, tar: boolean, bz2: boolean) {
    let cmd: string = "";
    let args: string[] = [];

    if (tar) {
      if (Deno.build.os !== "windows") {
        cmd = "tar";
        args = bz2
          ? ["-xjf", zipPath, "-C", destDir]
          : ["-xzf", zipPath, "-C", destDir];
      }
    } else {
      if (Deno.build.os === "windows") {
        cmd = "powershell";
        args = [
          "-Command",
          `Expand-Archive -Path '${zipPath}' -DestinationPath '${destDir}'`,
        ];
      } else {
        cmd = "unzip";
        args = ["-q", "-o", zipPath, "-d", destDir];
      }
    }

    const command = new Deno.Command(cmd, {
      args: args,
      stdout: "null",
      stderr: "piped",
    });
    
    const { code, success, stderr } = await command.output();

    if (!success) {
      const errorText = new TextDecoder().decode(stderr);
      console.error(errorText);
      Deno.exit(code);
    }
}

export async function fileExists(filePath: string): Promise<boolean> {
    try {
      const fileInfo = await Deno.stat(filePath);
      fileInfo;
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
        if (!(error instanceof Deno.errors.AlreadyExists)) {
            throw error;
        }
    }
}

export async function deleteFile(path: string) {
  try {
    await Deno.remove(path);
  } catch (error) {
    if (!(error instanceof Deno.errors.NotFound)) {
      throw error;
    }
  }
}

export async function chmod(file: string, args: string) {
  if (Deno.build.os !== "windows") {
    const command = new Deno.Command("chmod", {
      args: ["+" + args, file],
      stdout: "null",
      stderr: "piped",
    });
    
    const { code, success, stderr } = await command.output();

    if (!success) {
      const errorText = new TextDecoder().decode(stderr);
      console.error(errorText);
      Deno.exit(code);
    }
  }
}
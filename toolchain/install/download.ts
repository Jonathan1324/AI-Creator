export async function downloadTool(url: string, dest: string) {
    let cmd: string;
    let args: string[];

    if (Deno.build.os === "windows") {
      cmd = "powershell";
      args = ["powershell", "-Command", `Invoke-WebRequest -Uri '${url}' -OutFile '${dest}'`];
    } else {
      cmd = "curl";
      args = ["-L", url, "-o", dest];
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
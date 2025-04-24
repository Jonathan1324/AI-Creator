import { convertFile } from "./main.js"

async function* walkDir(dir: string): AsyncGenerator<Deno.DirEntry & { path: string }> {
    for await (const entry of Deno.readDir(dir)) {
        const fullPath = `${dir}/${entry.name}`;
        if (entry.isDirectory) {
            yield* walkDir(fullPath);
        } else {
            yield { ...entry, path: fullPath };
        }
    }
}

export async function transpileXsh(inputRoot: string, outputRoot: string) {
    for await (const entry of walkDir(inputRoot)) {
        if (entry.isFile && entry.name.endsWith(".xsh")) {
            const inputPath = entry.path;
            const relative = inputPath.slice(inputRoot.length + 1); // z.B. "util/file.xsh"
            const outputDir = `${outputRoot}/${relative.substring(0, relative.lastIndexOf("/"))}/`.replace(/\/+/g, "/");
            const fileName = entry.name;

            await convertFile(inputPath, outputDir, fileName.slice(0, -4));

            if (Deno.build.os !== "windows") {
                await Deno.chmod(outputDir + fileName.slice(0, -4) + ".sh", 0o755);
            }
        }
    }
}
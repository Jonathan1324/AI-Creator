import { transpileToBatch } from "./batch.js"
import { transpileToShell } from "./shell.js"

function transpileScript(script, outputDir) {
    const lines = script.split(/\r?\n/);

    const batchLines = [];
    const shellLines = [];

    for (const line of lines) {
        const trimmed = line.trim();
        if (trimmed === "" || trimmed.startsWith('#')) continue;
    
        try {
            batchLines.push(transpileToBatch(trimmed, outputDir));
            shellLines.push(transpileToShell(trimmed, outputDir));
        } catch (error) {
            console.error(error + "");
        }
    }

    const batchScript = batchLines.join("\r\n");
    const shellScript = shellLines.join("\n");

    return { batchScript, shellScript };
}

export async function convertFile(inputPath, outputDir, fileName) {
    const content = await Deno.readTextFile(inputPath);
    
    const { batchScript, shellScript } = transpileScript(content, outputDir);

    await Deno.mkdir(outputDir, { recursive: true });

    await Deno.writeTextFile(outputDir + fileName + ".bat", batchScript);
    await Deno.writeTextFile(outputDir + fileName + ".sh", shellScript);
}
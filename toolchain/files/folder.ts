export async function deleteFolderRecursive(folderPath: string) {
    try {
        const info = await Deno.stat(folderPath);
        if (!info.isDirectory) {
            return;
        }
    } catch (err) {
        return;
    }

    for await (const entry of Deno.readDir(folderPath)) {
        const entryPath = `${folderPath}/${entry.name}`;
  
        if (entry.isDirectory) {
            await deleteFolderRecursive(entryPath);
        } else {
            await Deno.remove(entryPath);
        }
    }
  
    await Deno.remove(folderPath);
}
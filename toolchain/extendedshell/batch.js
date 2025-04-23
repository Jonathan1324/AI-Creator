function normalizePathForBatch(path) {
    return path.replace(/\//g, "\\");
}

export function transpileToBatch(command, outputDir) {
    if (command.startsWith('echo ')) {
        return `@echo ${command.slice(5).trim()}`;
    }
    if (command.startsWith('cd ')) {
        return 'cd ' + normalizePathForBatch(command.slice(3).trim());
    }
    if (command.startsWith('call ')) {
        return 'call ' + normalizePathForBatch(outputDir) + normalizePathForBatch(command.slice(5).trim()) + '.bat';
    }
    throw new Error("Unsupported command: " + command);
}
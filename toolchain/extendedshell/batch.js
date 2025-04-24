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
        return 'cmd /c ' + normalizePathForBatch(outputDir) + normalizePathForBatch(command.slice(5).trim()) + '.bat';
    }
    if (command.startsWith('mkdir ')) {
        return 'mkdir ' + normalizePathForBatch(command.slice(6).trim());
    }
    if (command.startsWith('chmod ')) {
        return '';
    }
    if (command.startsWith('runFile ')) {
        const args = command.slice(8).trim().split(' ');
        const firstArg = normalizePathForBatch(args[0]);
        const restArgs = args.slice(1).join(' ');
        return `runFile ${firstArg}${restArgs ? ' ' + restArgs : ''}`;
    }
    if (command.startsWith('pwd')) {
        return 'echo %cd%';
    }
    if (command.startsWith('ls')) {
        return 'dir';
    }
    if (command.startsWith('rm ')) {
        return 'del ' + normalizePathForBatch(command.slice(3).trim());
    }
    throw new Error("Unsupported command: " + command);
}
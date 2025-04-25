function normalizePathForBatch(path) {
    return path.replace(/\//g, "\\");
}

export function transpileToBatch(cmd, outputDir) {
    let command = cmd;
    command = command.replace("$BUILD_DIR", normalizePathForBatch(outputDir));


    if (command.startsWith('echo ')) {
        return `@echo ${command.slice(5).trim()}`;
    }
    if (command.startsWith('cd ')) {
        return '@cd ' + normalizePathForBatch(command.slice(3).trim());
    }
    if (command.startsWith('call ')) {
        return '@cmd /c ' + normalizePathForBatch(command.slice(5).trim()) + '.bat';
    }
    if (command.startsWith('mkdir ')) {
        return '@if not exist "' + normalizePathForBatch(command.slice(6).trim()) + '" mkdir "' + normalizePathForBatch(command.slice(6).trim()) + '"';
    }
    if (command.startsWith('chmod ')) {
        return '';
    }
    if (command.startsWith('runFile ')) {
        const args = command.slice(8).trim().split(' ');
        const firstArg = normalizePathForBatch(args[0]);
        const restArgs = args.slice(1).join(' ');
        return `@${firstArg}${restArgs ? ' ' + restArgs : ''}`;
    }
    if (command.startsWith('pwd')) {
        return '@echo %cd%';
    }
    if (command.startsWith('ls')) {
        return '@dir';
    }
    if (command.startsWith('rm ')) {
        return '@del ' + normalizePathForBatch(command.slice(3).trim());
    }
    if (command.startsWith('runWindows ')) {
        const args = command.slice(11).trim().split(' ');
        const firstArg = normalizePathForBatch(args[0]);
        const restArgs = args.slice(1).join(' ');
        return `@${firstArg}${restArgs ? ' ' + restArgs : ''}`;
    }
    if (command.startsWith('runMac ')) {
        return "";
    }
    if (command.startsWith('runLinux ')) {
        return "";
    }
    throw new Error("Unsupported command: " + command);
}
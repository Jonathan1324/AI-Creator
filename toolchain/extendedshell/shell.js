export function transpileToShell(command, outputDir) {
    if (command.startsWith('echo ')) {
        return command;
    }
    if (command.startsWith('cd ')) {
        return 'cd ' + command.slice(3).trim();
    }
    if (command.startsWith('call ')) {
        return 'source ' + outputDir + command.slice(5).trim() + '.sh';
    }
    throw new Error("Unsupported command: " + command);
}
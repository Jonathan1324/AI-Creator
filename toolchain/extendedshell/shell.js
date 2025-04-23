export function transpileToShell(command, outputDir) {
    if (command.startsWith('echo ')) {
        return 'echo ' + command.slice(5).trim();
    }
    if (command.startsWith('cd ')) {
        return 'cd ' + command.slice(3).trim();
    }
    if (command.startsWith('call ')) {
        return 'source ' + outputDir + command.slice(5).trim() + '.sh';
    }
    if (command.startsWith('mkdir ')) {
        return 'mkdir ' + command.slice(6).trim();
    }
    if (command.startsWith('chmod ')) {
        return 'chmod ' + command.slice(6).trim();
    }
    if (command.startsWith('runFile ')) {
        return command.slice(8).trim();
    }
    throw new Error("Unsupported command: " + command);
}
export function transpileToShell(cmd, outputDir) {
    let command = cmd;
    command = command.replace("$BUILD_DIR", outputDir);

    if (command.startsWith('echo ')) {
        return 'echo ' + command.slice(5).trim();
    }
    if (command.startsWith('cd ')) {
        return 'cd ' + command.slice(3).trim();
    }
    if (command.startsWith('call ')) {
        return 'sh ' + command.slice(5).trim() + '.sh';
    }
    if (command.startsWith('mkdir ')) {
        return 'mkdir -p' + command.slice(6).trim();
    }
    if (command.startsWith('chmod ')) {
        return 'chmod ' + command.slice(6).trim();
    }
    if (command.startsWith('runFile ')) {
        return command.slice(8).trim();
    }
    if (command.startsWith('pwd')) {
        return 'pwd';
    }
    if (command.startsWith('ls')) {
        return 'ls';
    }
    if (command.startsWith('rm ')) {
        return 'rm ' + command.slice(3).trim();
    }
    if (command.startsWith('runWindows ')) {
        return "";
    }
    if (command.startsWith('runMac ')) {
        return "if [ \"$(uname)\" = \"Darwin\" ]; then\n" + command.slice(7).trim() + "\nfi";
    }
    if (command.startsWith('runLinux ')) {
        return "if [ \"$(uname)\" = \"Linux\" ]; then\n" + command.slice(9).trim() + "\nfi";
    }
    throw new Error("Unsupported command: " + command);
}
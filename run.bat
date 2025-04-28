@cmd /c .\toolchain\deno-setup\deno-setup.bat

@.\tools\deno run --allow-read --allow-run --allow-net --allow-write .\toolchain\main.ts

@call .\build\build_scripts\main.bat %1
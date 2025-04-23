cmd /c .\toolchain\bootstrap\bootstrap.bat

.\tools\deno run --allow-read --allow-run --allow-net --allow-write ./toolchain/main.ts

call .\build_scripts\main.bat
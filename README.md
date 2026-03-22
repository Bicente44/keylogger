# keylogger
- This program is entirely made in C and is used to capture user keyboard input
- This is purely for educational purposes and I strongly advise keyloggers to be used with permission and caution

## TODO
- Add an output file to both keyloggers
- Add a timeout option

## LINUX
- Runs if preprocessor detects Linux, excluding WSL.
- Reads from /dev/input/ key stream

bash
```
# Install dependencys:
- GCC (or some C compiler)

# Build:
gcc -Wall -Wextra main.c linux_keylogger.c -o keylogger
```

## keylogger - WINDOWS
- Runs if the preprocessor detects Windows or WSL.
- 

bash
```
# Install dependencys:
- mingw-w64 (Including WSL (WindowsSubsystemLinux))

# Build:
x86_64-w64-mingw32-gcc -Wall -Wextra main.c windows_keylogger.c -o keylogger.exe
```

import sys, os
def run(cmd):
    r = os.system(cmd)
    if r != 0:
        print(f"Command '{cmd}' failed with error code {r}", file=sys.stderr)
        sys.exit(1)

if os.name == "nt":
    run("gcc -g -Werror=implicit-function-declaration -std=c17 -Wall sdl.c sprites.c mainloop.c -Isdl2\\include -Lsdl2\\lib -lmingw32 -lpsapi -lSDL2main -lSDL2 -lSDL2_image -o main.exe")  # -Wl,-subsystem,windows
    run("main.exe")

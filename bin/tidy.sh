#!/bin/bash

# use command substitution to assign the value from the function pwd
# to the variable cur_dir
# cur_dir=$(pwd)

# check if everything works correctly
# echo "This is the current dir: $cur_dir"

if [ ! -e main.c ]; then
    touch main.c
    echo "created main.c file"
    # adding the -e flag makes the echo interpret backlash escapes
    echo -e "#include <stdio.h>\n\nint main(void) {\n\treturn 0;\n}" > main.c
    echo "added content to main.c"
fi

if [ ! -e start.sh ]; then
    touch start.sh
    echo "created start.sh file"
    echo -e "mpirun -n 4 ./build/my_program" > start.sh 
    chmod +x ./start.sh
    echo "added content to start.sh and made it executable"
fi

if [ ! -e makefile ]; then
    touch makefile
    echo "created makefile"
    echo -e "main: main.c\n\tmpicc main.c -o build/my_program" > makefile
    echo "added content to makefile"
fi

mkdir build
echo "added build directory"

echo "All done. Happy coding!"

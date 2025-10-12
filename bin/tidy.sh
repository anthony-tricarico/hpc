#!/bin/bash

# use command substitution to assign the value from the function pwd
# to the variable cur_dir
# cur_dir=$(pwd)

# check if everything works correctly
# echo "This is the current dir: $cur_dir"

touch main.c
echo "created main.c file"
touch makefile
echo "created makefile"
mkdir build
echo "added build directory"

# adding the -e flag makes the echo interpret backlash escapes
echo -e "#include <stdio.h>\n\nint main(void) {\n\treturn 0;\n}" > main.c
echo "added content to main.c"
echo -e "main: main.c\n\tmpicc main.c -o build/my_program" > makefile
echo "added content to makefile"
echo "All done. Happy coding!"

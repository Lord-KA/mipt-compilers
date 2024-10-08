This is a MIPT compilers cource HW.

# Build
```bash
$ mkdir build && cd build && cmake .. && make -j
```
# Run
```
Usage: frontend [options]
Options:
  -h, --help           Show this help message
  -v, --verbose        Enable verbose mode
  -p, --print FILE     Print the AST of the program
  -i, --interpret FILE Interpret the program
  -o, --output FILE    Write output to the specified FILE
```

You can find a program example in `source.txt`.

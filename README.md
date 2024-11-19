# 42 Get Next Line

## Description

The `get_next_line` project is a function that reads a line from a file descriptor and returns it. This function is designed to handle multiple file descriptors and read efficiently from them.

## Features

- Read a line from a file descriptor.
- Handle multiple file descriptors simultaneously.
- Efficient memory usage.

## Usage

To use the `get_next_line` function, include the header file and call the function with a valid file descriptor.

```c
#include "get_next_line.h"

int fd = open("file.txt", O_RDONLY);
char *line;

while ((line = get_next_line(fd)) != NULL) {
 printf("%s\n", line);
 free(line);
}

close(fd);
```

## Files

- `get_next_line.c`: Contains the main logic for reading a line.
- `get_next_line.h`: Header file with function prototypes.
- `get_next_line_utils.c`: Utility functions used by `get_next_line`.

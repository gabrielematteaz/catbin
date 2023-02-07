# catbin
This is a command-line utility for displaying binary files in a formatted manner. It provides functionality similar to the "cat" command, but allows for more control over the output.

# Usage
```
./catbin [options] filename
```

# Options
The utility supports the following flags:

-o: Specifies the offset from the start of the file to begin reading.<br />
-l: Limits the number of bytes to be read from the file.<br />
-c: Specifies the number of columns per section.<br />
-s: Specifies the number of sections to format the file with.<br />

# Examples

### Display the first 16 bytes of a binary file
```
./catbin -l 16 filename.bin
```
#### Result
Offset: 0 (Default)<br />
Limit: -1 (No limit, default)<br />
Columns: 8 (Default)<br />
Sections: 2 (Default)<br />
```
80 16 45 8f 12 5f 12 90    00 00 0f 1a 16 60 00 aa
```

### Display the entire file formatted into 4 sections of 4 columns each, starting from byte 64
```
./catbin -o 64 -c 4 -s 4 filename.bin
```
#### Result
Offset: 64<br />
Limit: -1 (No limit, default)<br />
Columns: 4<br />
Sections: 4<br />
```
80 16 45 8f    12 5f 12 90    00 00 0f 1a    16 60 00 aa
34 00 23 89    55 33 0f 0a    11 22 00 4d    dd 3d 12 12
22 33

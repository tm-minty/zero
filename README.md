# Zero
====
Generating N files with 1Gb of zeros

## Building
### Linux
```
> gcc zero.c -o zero
```

### Windows
```
> gcc.exe zero.c -o zero.exe
```

## Usage
```
> zero <output_filename_template> <count>
```
example:
```
> zero output_ 5
```
will generate 5 files with names: output_1, output_2, output_3, etc...
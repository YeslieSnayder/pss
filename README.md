# PSS
## About

This repository is used for PSS's homework projects.

Now available: 1st homework.

# "Homework 1" description

The program starts with `task` file.

The program gives the input text with special words from file `input.txt`. Output of the program are sentences with HIGHLIGHTED special words.

### Input

- 1st line: large text
- 2nd line: number `n` of special words
- `n` lines: special word

### Output

- 1st line: number `m` of sentences which contains the special word
- `m` lines: sentence which contains the highlighted special word

The program repeats output `n` times with `n` different words from input. If the text doesn't contain special word, then the program skips the output for this word.

### Libraries

- `<vector>` - is used instead of array. (to contain sentences)
- `<fstream>` - is used to read information from file `input.txt` and write the output to file `output.txt`
- `<sstream>` - is used to split a string into parts separated by some symbol

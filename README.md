# Unix Shell

This is a simple Unix shell implemented in C. It can read user input, parse it into arguments, and execute the specified command.

## Getting Started
To compile and run the Unix shell on your local machine, follow these steps:

1. Clone the repository

```bash
git clone https://github.com/b05702117/simpeUnixShell.git
```

2. Navigate to the directory

3. Compile the program:

```bash
gcc -o myUnixShell myUnixShell.c
```

4. Run the program:

```bash
./shell
```

5. The shell will start running, and you can enter commands:

```bash
osh>
```

## Usage

The Unix shell supports the following commands:

- `exit`: terminate the shell
- `!!`: repeats the previous command entered


## Test the code
```
(base) tu@tuyubaodeMacBook-Air UnixShell % gcc -o myUnixShell myUnixShell.c
(base) tu@tuyubaodeMacBook-Air UnixShell % ./myUnixShell                   
osh>ls
README.rd       myUnixShell     myUnixShell.c
osh>!!
ls
README.rd       myUnixShell     myUnixShell.c
osh>exit
```
# Command Line Interpreter (CLI) Project

------------------------------------------------------------------------

# Overview

This project requires implementing a simplified **Command Line
Interpreter (CLI)** similar to those found in operating systems.\
Although simplified, it includes many real OS concepts such as:

-   Command execution
-   Input/output streams
-   Redirection
-   Pipes
-   Batch command execution

The interpreter reads commands from **standard input**, executes them,
and prints results to **standard output**.

Commands can be executed:

-   **Interactively** (typed by the user)
-   **Batch mode** (read from a text file)

------------------------------------------------------------------------

# Interpreter Behavior

The interpreter runs in a loop:

1.  Print a **prompt** (default: `$`)
2.  Read a **command line**
3.  Execute the command
4.  Print the prompt again

Example:

    $ wc -w "Lorem ipsum dolor sit amet"
    8
    $

------------------------------------------------------------------------

# Command Syntax

General format:

    command [-option] [argument]

Where:

-   `command` -- command name
-   `option` -- modifies command behavior
-   `argument` -- command input (text or filename)

Example:

    wc -w "Lorem ipsum dolor sit amet"

Counts words in the given string.

------------------------------------------------------------------------

# Lexical Rules

1.  Maximum command length: **512 characters**
2.  Commands are **case sensitive**
3.  Arguments are separated by **whitespace** (`space` or `tab`)
4.  Text in **quotes `" "`** is treated as a single argument
5.  Special characters:

```{=html}
    | < >
```

have special meaning unless inside quotes.

Invalid syntax causes the interpreter to print an error message and skip
execution.

Example:

    Error - unexpected characters:
    wc& -w *"Lorem ipsum dolor sit amet" +?
      ^    ^                             ^^

------------------------------------------------------------------------

# Input Streams

Commands read input from one of the following:

### 1. Keyboard (default)

    $ wc -w

User types text and ends input with:

-   Windows: `Ctrl + Z`
-   Unix: `Ctrl + D`

### 2. Quoted text

    $ wc -w "Lorem ipsum dolor sit amet"

### 3. Text file

    $ wc -w input.txt

### 4. Input redirection

    $ wc -w < input.txt

------------------------------------------------------------------------

# Output Streams

### Default output

Console:

    $ wc -w "Lorem ipsum"
    2

### Redirect output to file

    $ wc -w "Lorem ipsum" > output.txt

### Append output

    >> output.txt

Appends instead of overwriting.

------------------------------------------------------------------------

# Supported Commands

## echo

    echo [argument]

Copies input stream directly to output stream.

------------------------------------------------------------------------

## prompt

    prompt argument

Changes the command prompt.

Example:

    prompt ">"

------------------------------------------------------------------------

## time

    time

Prints the current system time.

------------------------------------------------------------------------

## date

    date

Prints the current system date.

------------------------------------------------------------------------

## touch

    touch filename

Creates an empty file.

Error if the file already exists.

------------------------------------------------------------------------

## truncate

    truncate filename

Clears the contents of a file.

------------------------------------------------------------------------

## rm

    rm filename

Deletes a file.

------------------------------------------------------------------------

## wc

    wc -opt [argument]

Options:

  Option   Meaning
  -------- ------------------
  `-w`     count words
  `-c`     count characters

Words are sequences separated by whitespace (`std::isspace`).

------------------------------------------------------------------------

## tr

    tr "what" ["with"]

Replaces occurrences of `what` with `with`.

If `with` is missing, occurrences are removed.

Example:

    tr ":" "."

------------------------------------------------------------------------

## head

    head -n<count> [argument]

Outputs the first **N lines** of input.

Example:

    head -n10 file.txt

------------------------------------------------------------------------

## batch

    batch filename

Reads commands from a file and executes them sequentially.

Characteristics:

-   Executes commands line by line
-   Continues execution even if a command fails
-   Allows recursive batch execution

------------------------------------------------------------------------

# Pipes

Commands can be chained using pipes:

    command1 | command2 | command3

Example:

    time | tr ":" "." | wc -c > time.txt

Flow:

1.  `time` outputs current time
2.  `tr` replaces `:` with `.`
3.  `wc` counts characters
4.  Result is written to `time.txt`

Rules:

-   Commands without input must be **first**
-   Commands without output must be **last**
-   Streams cannot be redefined inside pipes

------------------------------------------------------------------------

# Error Handling

The interpreter must detect and report errors:

1.  Lexical errors
2.  Unknown commands

```{=html}
    Unknown command: command
```

3.  Syntax errors
4.  Invalid input/output stream definitions
5.  Command-specific errors
6.  Operating system errors (file not found, permission errors, etc.)

------------------------------------------------------------------------

# Revision History

**Version 1.0**\
Initial document.

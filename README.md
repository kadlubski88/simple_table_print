# Simple table print
Simple Table Print(STP) is a simple command to get one entry from a certain line of a file.

Entries(colums) can be multiple space or tab separated.

It is intended to replace awk or other complex program for such a simple task.
In my opinion, this functionality should be part of the GNU Core Utilities.

## Usage
With a specified file:
~~~bash
stp -c <[optional]column number> -l <[optional]line number> -f <path to file>
~~~
With pipe:
~~~bash
cat <file to parse> | stp -c <[optional]column number> -l <[optional]line number>
~~~
> Note: Column and line number are starting at 1. Default for column and line are also 1.

Get version:
~~~bash
stp -v
~~~

## Example
Get second CPU core idle time:
~~~bash
$: stp -l 3 -c 5 -f /proc/stat
1015671

#OR

$: cat /proc/stat | grep "cpu1" | stp -c 5
1015671
~~~

## Installation
Compile the source file with gcc:
~~~bash
gcc -o stp stp.c
~~~
Make the output file executable
~~~bash
chmod +x stp
~~~
Copy the executable in one of the folder mentioned in the PATH environement variable(e.g. /usr/bin/).
~~~bash
cp ./stp /usr/bin/stp
~~~

## TODO
- Add a help option

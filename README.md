# Simple table print
A simple command to get one entry from a certain line of a file.

For example get the cpu idle time from the file /proc/stat.
Is meant to replace awk for such a simple task.
Entries can be multiple space or tab separated.
## Usage
~~~bash
stp -c <column number> -l <line number> -f <path to file>
~~~
Column and line number are starting at 1. Default for column and line are also 1.
## Todo
- Usage with pipe
~~~bash
cat /proc/uptime | stp -c 2
~~~
- Only first line with a certain text(simple pattern) in a certain column
~~~bash
cat /proc/stat | stp -c 4 -p cpu1
~~~

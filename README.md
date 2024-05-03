# minishell

Knowledge from the evaluation from M.Furnica

- Throwing a SIGINT (Ctrl+C) in a heredoc (exit code?)
- Handle space in terminal as empty input.
- Yesterday they had memory leaks when using exit (check during building "exit")
- ls -l also NOT quote sensitive
- echo -n should behave the same as echo -nnnnnnnnnn (if not n, then treat as string)

  EXAMPLE:
  amirfatt@c3r8p6:~$ echo -n "hallo"
  halloamirfatt@c3r8p6:~$ echo -nnnnnnnnnnnnnnnnn "hallo"
  halloamirfatt@c3r8p6:~$ echo -nnnnnnnnnnnnnnnann "hallo"
  -nnnnnnnnnnnnnnnann hallo

  amirfatt@c3r8p6:~$ echo '-n' "hallo"
  halloamirfatt@c3r8p6:~$ echo "-n" "hallo"
  halloamirfatt@c3r8p6:~$ echo "-nnnnn" "hallo"
  halloamirfatt@c3r8p6:~$ echo "-nnsnnn" "hallo"
  -nnsnnn hallo
  amirfatt@c3r8p6:~$ 

- Unclosed quotes check at the beginning at program to avaid random heredocs lol
- Opening minishell in minishell -> Shell Levels (running them manually)

- QUESTION: exit with numeric arguments only

EXAMPLE:
  Correct: 
    amirfatt@c3r8p6:~$ exit
    exit
    amirfatt@c3r8p6:~/Desktop/Common_Core/GRAPH_04/minishell_tester_ground$ exit 2222222
    exit
    c3r8p6% bash
    amirfatt@c3r8p6:~/Desktop/Common_Core/GRAPH_04/minishell_tester_ground$ exit "22222"
    exit
    c3r8p6% bash

Syntax Error: 
  amirfatt@c3r8p6:~/Desktop/Common_Core/GRAPH_04/minishell_tester_ground$ exit 22 exit
  exit
  bash: exit: too many arguments

  amirfatt@c3r8p6:~/Desktop/Common_Core/GRAPH_04/minishell_tester_ground$ exit !!
  exit exit "22222"
  exit
  bash: exit: exit: numeric argument required

- Skip spaces when writing into files through expanded variables
- Also this
amirfatt@c3r8p6:~$ export A='echo hi'
amirfatt@c3r8p6:~$ $A
hi
amirfatt@c3r8p6:~$ 

- export values are overwritten

- Also this
- amirfatt@c3r8p6:~$ export A="ls -l"
amirfatt@c3r8p6:~$ $A
total 4
-rw-r--r-- 1 amirfatt 2022_vienna    0 Apr  5 13:43 cat
drwxr-xr-x 6 amirfatt 2022_vienna   75 Apr  8 13:45 Desktop
drwxr-xr-x 2 amirfatt 2022_vienna    6 Mar 18 14:34 Documents
drwxr-xr-x 3 amirfatt 2022_vienna 4096 Apr 12 14:06 Downloads
-rw-r--r-- 1 amirfatt 2022_vienna    0 Apr  5 13:43 echo
-rw-r--r-- 1 amirfatt 2022_vienna    0 Apr  5 13:43 Export
-rw-r--r-- 1 amirfatt 2022_vienna    0 Apr  5 13:27 file_out
drwxr-xr-x 9 amirfatt 2022_vienna  176 Mar 19 10:49 funcheck
lrwxrwxrwx 1 amirfatt 2022_vienna   17 Mar 18 14:34 goinfre -> /goinfre/amirfatt
-rw-r--r-- 1 amirfatt 2022_vienna    0 Apr  5 13:43 ls
drwxr-xr-x 2 amirfatt 2022_vienna    6 Mar 18 14:34 Music
-rw-r--r-- 1 amirfatt 2022_vienna    0 May  3 14:42 out
drwxr-xr-x 3 amirfatt 2022_vienna   25 Mar 19 15:48 Pictures
drwxr-xr-x 2 amirfatt 2022_vienna    6 Mar 18 14:34 Public
lrwxrwxrwx 1 amirfatt 2022_vienna   32 Mar 19 10:44 sgoinfre -> /sgoinfre/goinfre/Perso/amirfatt
drwxr-xr-x 2 amirfatt 2022_vienna    6 Mar 18 14:34 Templates
drwxr-xr-x 2 amirfatt 2022_vienna    6 Mar 18 14:34 Videos
amirfatt@c3r8p6:~$ export A=ls -l
bash: export: `-l': not a valid identifier
amirfatt@c3r8p6:~$ export A=ls
amirfatt@c3r8p6:~$ $A
cat  Desktop  Documents  Downloads  echo  Export  file_out  funcheck  goinfre  ls  Music  out  Pictures  Public  sgoinfre  Templates  Videos
amirfatt@c3r8p6:~$ export A="ls -l"
amirfatt@c3r8p6:~$ $A
total 4
-rw-r--r-- 1 amirfatt 2022_vienna    0 Apr  5 13:43 cat
drwxr-xr-x 6 amirfatt 2022_vienna   75 Apr  8 13:45 Desktop
drwxr-xr-x 2 amirfatt 2022_vienna    6 Mar 18 14:34 Documents
drwxr-xr-x 3 amirfatt 2022_vienna 4096 Apr 12 14:06 Downloads
-rw-r--r-- 1 amirfatt 2022_vienna    0 Apr  5 13:43 echo
-rw-r--r-- 1 amirfatt 2022_vienna    0 Apr  5 13:43 Export
-rw-r--r-- 1 amirfatt 2022_vienna    0 Apr  5 13:27 file_out
drwxr-xr-x 9 amirfatt 2022_vienna  176 Mar 19 10:49 funcheck
lrwxrwxrwx 1 amirfatt 2022_vienna   17 Mar 18 14:34 goinfre -> /goinfre/amirfatt
-rw-r--r-- 1 amirfatt 2022_vienna    0 Apr  5 13:43 ls
drwxr-xr-x 2 amirfatt 2022_vienna    6 Mar 18 14:34 Music
-rw-r--r-- 1 amirfatt 2022_vienna    0 May  3 14:42 out
drwxr-xr-x 3 amirfatt 2022_vienna   25 Mar 19 15:48 Pictures
drwxr-xr-x 2 amirfatt 2022_vienna    6 Mar 18 14:34 Public
lrwxrwxrwx 1 amirfatt 2022_vienna   32 Mar 19 10:44 sgoinfre -> /sgoinfre/goinfre/Perso/amirfatt
drwxr-xr-x 2 amirfatt 2022_vienna    6 Mar 18 14:34 Templates
drwxr-xr-x 2 amirfatt 2022_vienna    6 Mar 18 14:34 Videos
amirfatt@c3r8p6:~$ export A=ls -l
bash: export: `-l': not a valid identifier
amirfatt@c3r8p6:~$ $A
cat  Desktop  Documents  Downloads  echo  Export  file_out  funcheck  goinfre  ls  Music  out  Pictures  Public  sgoinfre  Templates  Videos
amirfatt@c3r8p6:~$

- echo does not care about spaces
amirfatt@c3r8p6:~$ >> out_test.txt echo hello
amirfatt@c3r8p6:~$ >> out_test.txt echo hello
amirfatt@c3r8p6:~$ >> out_test.txt echo hello
amirfatt@c3r8p6:~$ >> out_test.txt echo he
amirfatt@c3r8p6:~$ cat out_test.txt 
hello
hello
hello
hello
he

- New line in Heredoc
(1)
amirfatt@c3r8p6:~$ cat <<"h"
> 
> 
> 
> 
> 
> 
> 
> 
> h








amirfatt@c3r8p6:~$ 
(2)
amirfatt@c3r8p6:~$ echo <<h
> 
> 
> 
> 
> h

amirfatt@c3r8p6:~$ 

- Expansion with no space
amirfatt@c3r8p6:~$ echo $USER$SHLVL
amirfatt2
amirfatt@c3r8p6:~$ bash
amirfatt@c3r8p6:~$ $SHlLVL
amirfatt@c3r8p6:~$ $SHLVL
3: command not found
amirfatt@c3r8p6:~$ $USER
amirfatt: command not found
amirfatt@c3r8p6:~$ echo $USER
amirfatt
amirfatt@c3r8p6:~$ echo $USER$SHLVL
amirfatt3
amirfatt@c3r8p6:~$ 




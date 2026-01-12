 <h1 align="center">Pipex</h1>


<div align="center">

  <h3>Reproduction of shell pipes</h3>

</div>


<div align="center">
  <a href="https://github.com/joaopedrogiancolidev/42_pipex/stargazers">
  <img src="https://img.shields.io/github/stars/joaopedrogiancolidev/42_pipex?style=flat&color=purple" alt="Stars">
  </a>
  <a href="https://github.com/joaopedrogiancolidev/42_pipex/network/members">
  <img src="https://img.shields.io/github/forks/joaopedrogiancolidev/42_pipex?style=flat&color=87CEEB" alt="Forks">
  </a>
  <img src="https://img.shields.io/github/languages/top/joaopedrogiancolidev/42_pipex?style=flat&color=4c1" alt="Top Language">
  <img src="https://img.shields.io/github/languages/count/joaopedrogiancolidev/42_pipex?style=flat&color=yellow" alt="Language Count">
  <img src="https://img.shields.io/github/last-commit/joaopedrogiancolidev/42_pipex?style=flat&color=e05d44" alt="Last Commit">
  <a href="https://www.linkedin.com/in/jpgusp/">
  <img src="https://img.shields.io/badge/LinkedIn-João%20Pedro-blue?style=flat&logo=linkedin" alt="LinkedIn">
  </a>

</div>

---

## 📚 Table of Contents
1. [Introduction](#pipex)
2. [Setting the Pipe](#setting-the-pipe)
3. [Forking the Processes](#forking-the-processes)
4. [File Descriptors (FD)](#fd)
5. [Swapping FDs with Dup2](#swapping-fds-with-dup2)

--- 

Pipex is a project that re-creates in C the way two commands are piped together via | in the shell

```bash
./pipex infile cmd1 cmd2 outfile
pipe()
 |
 |-- fork()
      |
      |-- child // cmd1
      :     |--dup2()
      :     |--close end[0]
      :     |--execve(cmd1)
      :
      |-- parent // cmd2
            |--dup2()
            |--close end[1]
            |--execve(cmd2)
 
# pipe() sends the output of the first execve() as input to the second execve()
# fork() runs two processes (i.e. two commands) in one single program
# dup2() swaps our files with stdin and stdout
```
---

##  Setting the pipe

```bash
void    pipex(int f1, int f2)
{
    int end[2];    pipe(end);
}

# pipe() takes an array of two int, and links them together
# what is done in end[0] is visible to end[1], and vice versa
# pipe() assigns an fd to each end
# Fds are file descriptors
# since files can be read and written to, by getting an fd each, the two ends can communicate
# end[1] will write to the its own fd, and end[0] will read end[1]’s fd and write to its own
```

---

##  Forking the processes

```bash
void    pipex(int f1, int f2)
{
    int   end[2];
    pid_t parent;    pipe(end);
    parent = fork();
    if (parent < 0)
         return (perror("Fork: "));
    if (!parent) // if fork() returns 0, we are in the child process
        child_process(f1, cmd1);
    else
        parent_process(f2, cmd2);
}

# fork() splits the process in two sub-processes -> parallel, simultaneous, happen at the same time
# it returns 0 for the child process, a non-zero for the parent process, -1 in case of error
```
end[1] is the child process, end[0] the parent process; the child writes, the parent reads
Since for something to be read, it must be written first, so cmd1 will be executed by the child, and cmd2 by the parent.

---

##  FD

pipex is run like this ./pipex infile cmd1 cmd2 outfile
FDs 0, 1 and 2 are by default assigned to stdin, stdout and stderr
infile, outfile, the pipe, the stdin and stdout are all FDs
On linux, you can check your fds currently open with the command ls -la /proc/$$/fd

Our fd table right now looks like this:

```bash
                           -----------------    
                 0         |     stdin     |  
                           -----------------    
                 1         |     stdout    |    
                           -----------------    
                 2         |     stderr    |  
                           -----------------
                 3         |     infile    |  // open()
                           -----------------
                 4         |     outfile   |  // open()
                           -----------------
                 5         |     end[0]    | 
                           -----------------
                 6         |     end[1]    |  
                           -----------------
```

---

##  Swaping Fds with Dup2

For the child process, we want infile to be our stdin (as input), and end[1] to be our stdout (we write to end[1] the output of cmd1)
In the parent process, we want end[0] to be our stdin (end[0] reads from end[1] the output of cmd1), and outfile to be our stdout (we write to it the output of cmd2)

```bash

// each cmd needs a stdin (input) and returns an output (to stdout)
   
    infile                                             outfile
as stdin for cmd1                                 as stdout for cmd2            
       |                        PIPE                        ↑
       |           |---------------------------|            |
       ↓             |                       |              |
      cmd1   -->    end[1]       ↔       end[0]   -->     cmd2           
                     |                       |
            cmd1   |---------------------------|  end[0]
           output                             reads end[1]
         is written                          and sends cmd1
          to end[1]                          output to cmd2
       (end[1] becomes                      (end[0] becomes 
        cmd1 stdout)                           cmd2 stdin)
```
---

## 📞 Contact

João Pedro Giancoli - [LinkedIn Profile](https://www.linkedin.com/in/jpgusp/)

---



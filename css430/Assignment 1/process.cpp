/* Jun Zhen
    CSS430
    Shell.java
*/
#include<stdio.h> 
#include<stdlib.h> 
#include<sys/wait.h> 
#include<unistd.h> 

int main(int argc, char** argv)
{
    //Creating file Descriptors and two pipes
	int fd[2];
	int fd2[2];
	pipe(fd);
    pipe(fd2);

    //Creating a new process pid1 = child
	pid_t pid1 = fork();
	if (pid1 == 0)
	{
        //pid2 = grandchild
	    pid_t pid2 = fork();
		if(pid2 == 0)
        {
            //Redirect the standard output to pipe 2's write side
            dup2(fd2[1], STDOUT_FILENO);
            close(fd2[1]);
            close(fd2[0]);
            close(fd[1]);
            close(fd[0]);
            //Change this process to execute "ps"
            execlp("ps", "ps","-A",NULL);
        }
        else
        {
            //Child will wait for the grandchild
            pid_t wait(pid2);
            //Change the standard input to pipe 2's read side
            dup2(fd2[0], STDIN_FILENO);
            close(fd2[0]);
            close(fd2[1]);
            //Change the standard output to pipe 1's write side
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
            close(fd[0]);
            //Change this process to execute "grep"
            execlp("grep", "grep", argv[1], NULL);
        }
	}
	else
	{
        //The parent wait for the child
		pid_t wait(pid1);
        //Change the standard input to pipe 1's read side
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
        close(fd[1]);
        close(fd2[0]);
        close(fd2[1]);     
        //Change this process to execute "wc"
        execlp("wc", "wc","-l",NULL);
	}
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(void)
{
    int pipes[4];
    int val = 0, i;
    pid_t pid;

    for (i=0; i<2; ++i)
    {
        pipe(pipes+(i*2));
    }

		pid = fork();
   
    if (pid == 0)
    {
      close(pipes[0]);
      close(pipes[3]);

    	pid = getpid();

      read(pipes[2], &val, sizeof(val));

    	printf("Child: My PID is %d\n", pid);
			printf("Child: Parent sent %d\n", val);

           
      val += pid;

      printf("Child: Sending %d\n", val);
      write(pipes[1], &val, sizeof(val));
           
      close(pipes[2]);
      close(pipes[1]);

      return 0;
    }

    close(pipes[2]);
    close(pipes[1]);

    pid = getpid();

    val = pid;
    printf("Parent: My PID is %d\n", pid);
    write(pipes[3], &val, sizeof(val));
   
    read(pipes[0], &val, sizeof(val));
   
    printf("Parent: The sum is %d\n", val);
    
    close(pipes[0]);
    close(pipes[3]);

    wait(NULL);

    return 0;
}



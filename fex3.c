#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int pid, pid1, pid2;
    int count = 0;
    if(pid<0)

	pid = fork();
    if (pid == 0) {
		// Primer hijo
        for (int i = 0; i < 5; i++) {
            count++;
            printf("Soy el primer hijo (PID %d) y mi padre es %d. La cuenta es %d.\n", getpid(), getppid(), count);
        }
        printf("\n");
    }
    

	else {
		pid1 = fork();
		if (pid1 == 0) {
			// Segundo hijo
            for (int i = 0; i < 5; i++) {
                count++;
                printf("Soy el segundo hijo (PID %d) y mi padre es %d. La cuenta es %d.\n", getpid(), getppid(), count);
            }
            printf("\n");
		}
		else {
			pid2 = fork();
			if (pid2 == 0) {
				// Tercer hijo
                for (int i = 0; i < 5; i++) {
                    count++;
                    printf("Soy el tercer hijo (PID %d) y mi padre es %d. La cuenta es %d.\n", getpid(), getppid(), count);
                }
                printf("\n");
			}
			else {
				// Proceso padre
                wait(NULL);
                wait(NULL);
                wait(NULL);
                for (int i = 0; i < 5; i++)
                {
                    count++;
                    printf("Soy el padre (PID %d) y mis hijos son: %d, %d y %d. La cuenta es %d.\n", getpid(), pid, pid1, pid2, count);
                }
            }
		}
	}

	return 0;
}

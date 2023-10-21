#include <stidio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
    struct FLOCK fl= 
    {
        F_WRLCK, 
        SEEK_SET,
        0,0,0
    };

    int fd;  // File descriptor for the opened file

    fl.l_pid = getpid();  // Set the process ID for locking to the current process

    if (argc > 1) {
        fl.l_type = F_RDLCK;  // Change the lock type to read lock (shared) if an argument is provided
    }

    if ((fd = open("MUTEX.c", O_RDWR)) == -1) {
        perror("open");  // Print an error message if opening the file fails
        exit(1);         // Exit the program with an error code
    }

    printf("Press <Enter> Key to get lock: \n");
    getchar();  // Wait for user input (Enter key press)

    printf("Locking... \n");

    if (fcntl(fd, F_SETLKW, &fl) == -1) {
        perror("fcntl");  // Print an error message if locking the file fails
        exit(1);         // Exit the program with an error code
    }

    printf("LOCKED \n");
    printf("Press Return to Unlock \n");
    getchar();  // Wait for user input (Enter key press) to unlock

    fl.l_type = F_UNLCK;  // Set the lock type to unlock

    if (fcntl(fd, F_SETLK, &fl) == -1) {
        perror("fcntl");  // Print an error message if unlocking the file fails
        exit(1);         // Exit the program with an error code
    }

    // Program ends
}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0) {
        perror("Errore fork");
        exit(1);
    }

    if (pid == 0) {
        // Codice del figlio
        int n, i, primo = 1;

        printf("Inserisci un numero intero: ");
        fflush(stdout);
        scanf("%d", &n);

        if (n < 2) {
            primo = 0;
        } else {
            for (i = 2; i <= n / i; i++) {
                if (n % i == 0) {
                    primo = 0;
                    break;
                }
            }
        }

        if (primo) {
            exit(1);
        } else if (n % 2 == 0) {
            exit(2);
        } else {
            exit(3);
        }
    }

    // Codice del padre
    wait(&status);

    if (WIFEXITED(status)) {
        int codice = WEXITSTATUS(status);

        switch (codice) {
            case 1:
                printf("Padre: il numero e' primo.\n");
                break;

            case 2:
                printf("Padre: il numero e' pari e non primo.\n");
                break;

            case 3:
                printf("Padre: il numero e' dispari e non primo.\n");
                break;

            default:
                printf("Padre: codice di uscita sconosciuto.\n");
        }
    }

    return 0;
}
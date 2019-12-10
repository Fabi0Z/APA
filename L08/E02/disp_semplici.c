void disp(int pos, int *val, int *sol, int *mark, int n, int k) {
    int i;
    if (pos >= k) { // Terminazione
        for (i = 0; i < k; i++) {
            printf("%d ", sol[i]);
        }
        printf("\n");
        return;
    }
    for (i = 0; i < n; i++) {                    // Iterazione sulle n scelte
        if (mark[i] == 0) {                      // Controllo ripetizione
            mark[i]  = 1;                        // Marcamento
            sol[pos] = val[i];                   // Scelta
            disp(pos + 1, val, sol, mark, n, k); // Ricorsione
            mark[i] = 0;                         // Smarcamento
        }
    }
}
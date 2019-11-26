void disp_ripet(int pos, int *val, int *sol, int n, int k) {
    int i, j, t, ok = 1, *occ;
    if (pos >= n) {
        occ = calloc(k, sizeof(int));
        for (j = 0; j < k; j++)
            occ[sol[j]]++;
        i = 0;
        while ((i < k) && ok) {
            if (occ[i] == 0)
                ok = 0;
            i++;
        }
        free(occ);
        if (ok == 0)
            return;
        else { /*STAMPA SOLUZIONE */
        }
    }
    for (i = 0; i < k; i++) {
        sol[pos] = i;
        disp_ripet(pos + 1, val, sol, n, k);
    }
}
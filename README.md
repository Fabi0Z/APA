# Soluzioni APA

Le soluzioni sono suddivise per i vari laboratori, se pensi che certe cose possano esser corrette e realizzate diversamente sentiti libero di fare una merge request

## Riguardo ai branch

Spesso non faccio merge sul branch principale sinché non sono sicuro che il mio codice sia pronto alla consegna, quindi se ancora non trovi un esercizio prova a controllare nel branch del relativo laboratorio, la struttura che uso per nominare i branch è `lab/{{ NUMERO_LABORATORIO }}`

## APA e VS Code

Nella cartella `.vscode` sono presenti delle configurazioni per poter avviare e debuggare programmi in C/C++ su sistemi GNU/Linux, le attuali configurazioni sono pensate per usare come compilatore `clang`, debugger `gdb` e funzionano mediante l'estensione ufficiale Microsoft per C/C++, più info [qui](https://code.visualstudio.com/docs/languages/cpp)

## Script per la consegna

È presente anche un piccolo script in Bash chiamato `consegna.sh` che restituisce l'archivio da consegnare per i vari laboratori seguendo le regole presenti in `AP1920_RegoleLab.pdf`, prende due argomenti in input e sono in ordine il numero di consegna e il numero di matricola, ecco un comando d'esempio

```bash
./consegna.sh 1 251489
# Crea l'archivio per la consegna 1 contenente i Lab 1, 2, 3 
# tramite il numero di matricola 251489
```

Lo script richiede di aver `tar` installato, anche se sarebbe strano non averlo preinstallato
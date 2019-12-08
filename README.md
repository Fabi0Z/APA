# Soluzioni APA

Le soluzioni sono suddivise per i vari laboratori, se pensi che certe cose possano esser corrette e realizzate diversamente sentiti libero di fare una merge request

## Riguardo ai branch

Spesso non faccio merge sul branch principale sinché non sono sicuro che il mio codice sia pronto alla consegna, quindi se ancora non trovi un esercizio prova a controllare nel branch del relativo laboratorio, la struttura che uso per nominare i branch è `lab/{{ NUMERO_LABORATORIO }}`

## APA e VS Code

Nella cartella `.vscode` sono presenti delle configurazioni per poter avviare e debuggare programmi in C/C++ su sistemi GNU/Linux e macOS, le attuali configurazioni sono pensate per usare come compilatori `clang` o `gcc` e come debugger `gdb` o `lldb`.

### tasks.json

- `Build linking libraries` : Compila il file `.c` attivo linkando tutti i file `*.o` presenti nella cartella dello stesso
- `Build folder` : Compila tutti i file `.c` nella cartella del file attivo in un unico eseguibile
- `Build` : Compila il file `.c` attivo
- `Build library` : Compila il file `.c` attivo come libreria
- `Build all libraries in folder` : Compila tutti i file `.c` presenti nella cartella del file attivo come librerie ad eccezione del file attivo che non viene Compilato
- `Makeheaders` : Crea il file `.h` rispettivo al file attivo (richiede [makeheaders](https://www.hwaci.com/sw/mkhdr/) installato)
- `Build folder clang` : Stessa cosa di `Build folder` ma con `clang` invece che `gcc`

Nel file `launch.json` sono presenti varie configurazioni per le rispettive alle task elencate.
Il tutto è pensato per funzionare mediante l'estensione ufficiale Microsoft per C/C++, più info [qui](https://code.visualstudio.com/docs/languages/cpp)

### Configurazione per Windows

C'è una configurazione già pronta anche per Windows, ma non l'ho mai testata, eventuali miglioramenti son benvenuti, per completarla in maniera decente seguite la [guida apposita](https://code.visualstudio.com/docs/cpp/config-mingw)

## Script per la consegna

È presente anche un piccolo script in Bash chiamato `consegna.sh` che restituisce l'archivio da consegnare per i vari laboratori seguendo le regole presenti in `AP1920_RegoleLab.pdf`, prende due argomenti in input e sono in ordine il numero di consegna e il numero di matricola, ecco un comando d'esempio

```bash
./consegna.sh 1 251489
# Crea l'archivio per la consegna 1 contenente i Lab 1, 2, 3
# tramite il numero di matricola 251489
```

Lo script richiede di aver `tar` installato, anche se sarebbe strano non averlo preinstallato

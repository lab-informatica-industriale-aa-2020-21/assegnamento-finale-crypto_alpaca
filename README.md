Blockchain Demo
============
![alt text](./docs/pictures/schermata_introduttiva.png "Schermata del funzionamento dell'applicazione")

Semplice simulatore di una blockchain per la gestione della criptovaluta Bitcoin.


---
## Introduzione

![Current Version](https://img.shields.io/badge/version-1.0.0-green.svg)

Lo scopo del progetto è poter simulare le dinamiche che sorgono durante la gestione delle transazioni di monete elettroniche, in un sistema decentralizzato e condiviso come una blockchain.


---
## Features

Alcune feature rese disponibili dalla nostra applicazione:

- Inserimento manuale delle transazioni
- Inserimento automatico delle transazioni
- Mining basato su SHA-256
- Visualizzazione del blocco di transazioni
- Salvataggio su file della blockchain


---
## Setup & Installazione

Per compilare il programma, dopo aver clonato questa repo, installa la libreria grafica `ncurses`.

Se usi una distribuzione basata su Ubuntu / Debian:

```bash
sudo apt-get install libncurses-dev
```

Abbiamo previsto anche la generazione **facoltativa** della documentazione con il programma `doxygen`.

Su una distribuzione basata su Ubuntu / Debian, lo puoi installare così:

```bash
sudo apt install doxygen
```

Successivamente, crea una cartella `build` dal percorso principale, e da tale cartella esegui il comando `cmake`:

```bash
cmake .. && make && ./app/application
```

*Nota: assicurati di eseguire l'applicazione dalla cartella build.*


---
## Roadmap

Il progetto è predisposto per la gestione dei conflitti di più blockchain.
Sono già presenti le cartelle `./lib/conflicts` e `./test/test_conflicts` con i relativi file per lo sviluppo.


---
## Contribuenti ✨

Si ringraziano queste fantastiche persone per la deterinazione nel portare a termine questo progetto:

<table>
  <tr>
    <td align="center"><a href="https://github.com/Binotto-Andrea"><img src="https://avatars.githubusercontent.com/u/81315168?v=4" width="100px;" alt=""/><br /><sub><b>Andrea Binotto
    <td align="center"><a href="https://github.com/filippo-toffano-unipd"><img src="https://avatars.githubusercontent.com/u/81314989?v=4" width="100px;" alt=""/><br /><sub><b>Filippo Toffano
    <td align="center"><a href="https://github.com/alberto-trabacchin-unipd"><img src="https://avatars.githubusercontent.com/u/81315216?v=4" width="100px;" alt=""/><br /><sub><b>Alberto Trabacchin
    <td align="center"><a href="https://github.com/emanuelezanoni"><img src="https://avatars.githubusercontent.com/u/81314774?v=4" width="100px;" alt=""/><br /><sub><b>Emanuele Zanoni
    
  </tr>
</table>
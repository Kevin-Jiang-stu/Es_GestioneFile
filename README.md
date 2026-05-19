# Es_GestioneFile

🎬 Gestore Cinema in C++
<div align="center">

Un semplice gestionale CRUD per la gestione di film cinematografici sviluppato in C++

</div>
📖 Descrizione

Questo progetto permette di gestire una programmazione cinematografica tramite terminale.

Il programma consente di:

✅ Aggiungere film
✅ Modificare film esistenti
✅ Eliminare film
✅ Cercare film per titolo o ID
✅ Filtrare i film per sala o genere
✅ Visualizzare solo i film con posti disponibili
✅ Ordinare i film per orario
✅ Salvare e caricare automaticamente i dati da file

Tutti i dati vengono memorizzati nel file:

filmlist.txt
🛠️ Funzionalità principali
➕ Aggiunta Film

Inserimento completo di:

Titolo
Regista
Genere
Durata
Sala
Orario
Posti disponibili
✏️ Modifica Film

Aggiornamento dei dati di un film tramite ID.

❌ Eliminazione Film

Rimozione sicura con richiesta di conferma.

🔍 Ricerca e Filtri

Il programma permette di:

📋 Visualizzare:
Tutti i film
🔎 Cercare:
Per titolo
Per ID
🎭 Filtrare:
Per genere
Per sala
🎟️ Mostrare:
Solo film con posti disponibili
⏰ Ordinare:
Per orario di proiezione
💾 Gestione File

I dati vengono:

✅ Caricati automaticamente all'avvio
✅ Salvati automaticamente alla chiusura
✅ Salvati manualmente dal menu

📂 Struttura del progetto
📁 GestoreCinema
│
├── 📄 main.cpp
├── 📄 filmlist.txt
📝 Formato del file filmlist.txt

Ogni riga del file rappresenta un film:

ID,Titolo,Regista,Genere,Durata,Sala,Orario,PostiDisponibili
🎬 Esempio
1,Inception,Christopher Nolan,Fantascienza,148,1,18:30,120
2,Interstellar,Christopher Nolan,Fantascienza,169,2,21:00,80
3,Avatar,James Cameron,Azione,162,3,20:15,0
⚙️ Compilazione
🖥️ Compilare con g++
g++ main.cpp -o cinema
▶️ Esecuzione
Windows
cinema.exe
Linux / macOS
./cinema
🧾 Menu Principale
===== GESTORE CINEMA =====

1. Aggiungi Film
2. Modifica Film
3. Elimina Film
4. Visualizza Film
5. Salva su File
0. Esci
🧰 Tecnologie utilizzate
<div align="center">
Tecnologia	Utilizzo
C++	Linguaggio principale
STL Vector	Gestione dinamica dati
fstream	Lettura/Scrittura file
algorithm	Ordinamento film
</div>
🚀 Possibili miglioramenti futuri
🔐 Sistema Login Admin
🎟️ Prenotazione posti cinema
🪑 Gestione posti per sala
🖼️ Interfaccia grafica
🗄️ Database SQL
🌐 Versione Web
🔎 Ricerca avanzata
📊 Statistiche film
👨‍💻 Autore

Progetto realizzato in C++ come esercizio CRUD e gestione file. 🎬
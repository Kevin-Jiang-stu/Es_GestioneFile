#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

struct Film
{
    int id;
    string titolo;
    string regista;
    string genere;
    int durata; // in minuti
    int Num_Sala;
    string Orario;
    int Num_Posti_Disponibili;
};

vector<Film> filmList;

void LetturaFile(string NomeFile, string Separatore = ",")
{
    ifstream file(NomeFile);
    if (!file.is_open())
    {
        cerr << "Errore nell'apertura del file: " << NomeFile << endl;
        return;
    }
    string line;
    while (getline(file, line))
    {
        Film film;
        size_t pos = 0;

        film.id = stoi(line.substr(pos, line.find(Separatore)));
        pos = line.find(Separatore) + 1;
        film.titolo = line.substr(pos, line.find(Separatore, pos) - pos);
        pos = line.find(Separatore, pos) + 1;
        film.regista = line.substr(pos, line.find(Separatore, pos) - pos);
        pos = line.find(Separatore, pos) + 1;
        film.genere = line.substr(pos, line.find(Separatore, pos) - pos);
        pos = line.find(Separatore, pos) + 1;
        film.durata = stoi(line.substr(pos, line.find(Separatore, pos) - pos));
        pos = line.find(Separatore, pos) + 1;
        film.Num_Sala = stoi(line.substr(pos, line.find(Separatore, pos) - pos));
        pos = line.find(Separatore, pos) + 1;
        film.Orario = line.substr(pos, line.find(Separatore, pos) - pos);
        pos = line.find(Separatore, pos) + 1;
        film.Num_Posti_Disponibili = stoi(line.substr(pos, line.find(Separatore, pos) - pos));

        filmList.push_back(film);
    }
}

void AggiungiFilm()
{
    Film film;
    if (filmList.empty())
        film.id = 1;
    else
        film.id = filmList.back().id + 1;

    cout << "Inserisci Titolo: ";
    cin.ignore();
    getline(cin, film.titolo);
    cout << "Inserisci Regista: ";
    getline(cin, film.regista);
    cout << "Inserisci Genere: ";
    getline(cin, film.genere);
    cout << "Inserisci Durata (in minuti): ";
    cin >> film.durata;
    cout << "Inserisci Numero Sala: ";
    cin >> film.Num_Sala;
    cout << "Inserisci Orario (HH:MM): ";
    cin.ignore();
    getline(cin, film.Orario);
    cout << "Inserisci Numero Posti Disponibili: ";
    cin >> film.Num_Posti_Disponibili;

    filmList.push_back(film);
}

bool ChiedoConferma(string messaggio)
{
    char risposta;
    cout << messaggio << " (S/N): ";
    cin >> risposta;
    return (risposta == 'S' || risposta == 's');
}

void EliminaFilm(int id)
{
    for (int i = 0; i < filmList.size(); ++i)
    {
        if (filmList[i].id == id)
        {
            if (ChiedoConferma("Sei sicuro di voler eliminare questo film?"))
            {
                filmList.erase(filmList.begin() + i);
                cout << "Film con ID " << id << " eliminato." << endl;
            }
            return;
        }
    }
}

void ModificaFilm(int id)
{
    for (int i = 0; i < filmList.size(); ++i)
    {
        if (filmList[i].id == id)
        {
            cout << "Modifica Titolo (attuale: " << filmList[i].titolo << "): ";
            cin.ignore();
            getline(cin, filmList[i].titolo);
            cout << "Modifica Regista (attuale: " << filmList[i].regista << "): ";
            getline(cin, filmList[i].regista);
            cout << "Modifica Genere (attuale: " << filmList[i].genere << "): ";
            getline(cin, filmList[i].genere);
            cout << "Modifica Durata (attuale: " << filmList[i].durata << "): ";
            cin >> filmList[i].durata;
            cout << "Modifica Numero Sala (attuale: " << filmList[i].Num_Sala << "): ";
            cin >> filmList[i].Num_Sala;
            cout << "Modifica Orario (attuale: " << filmList[i].Orario << "): ";
            cin.ignore();
            getline(cin, filmList[i].Orario);
            cout << "Modifica Numero Posti Disponibili (attuale: " << filmList[i].Num_Posti_Disponibili << "): ";
            cin >> filmList[i].Num_Posti_Disponibili;
            cout << "Film con ID " << id << " modificato." << endl;
            return;
        }
    }
}

void VisualizzaFilm()
{
    cout << "1. Lista completa di tutti i film in programmazione" << endl;
    cout << "2. Ricerca di un film per titolo o per ID" << endl;
    cout << "3. Filtro per sala o per genere" << endl;
    cout << "4. Visualizzazione dei film con posti disponibili" << endl;
    cout << "5. Film ordinati per orario di proiezione" << endl;
    cout << "Scegli un'opzione: ";
    int scelta;
    cin >> scelta;

    vector<Film> risultati;
    string input;

    switch (scelta)
    {
    case 1:
        StampaFilm();
        break;
    case 2:
        cout << "Inserisci titolo o ID del film: ";
        cin.ignore();
        getline(cin, input);

        for (auto i : filmList)
        {
            if (i.titolo == input || to_string(i.id) == input)
            {
                risultati.push_back(i);
            }
        }

        StampaFilm(risultati);
        break;
    case 3:
        cout << "Filtra per (1) Sala o (2) Genere: ";
        int filtro;
        cin >> filtro;
        cin.ignore();
        if (filtro == 1)
        {
            cout << "Inserisci numero sala: ";
            int sala;
            cin >> sala;
            for (auto i : filmList)
            {
                if (i.Num_Sala == sala)
                {
                    risultati.push_back(i);
                }
            }
        }
        else if (filtro == 2)
        {
            cout << "Inserisci genere: ";
            string genere;
            getline(cin, genere);
            for (auto i : filmList)
            {
                if (i.genere == genere)
                {
                    risultati.push_back(i);
                }
            }
        }
        StampaFilm(risultati);
        break;
    case 4:
        for (auto i : filmList)
        {
            if (i.Num_Posti_Disponibili > 0)
            {
                risultati.push_back(i);
            }
        }
        StampaFilm(risultati);
        break;
    case 5:
        risultati = filmList;
        sort(risultati.begin(), risultati.end(), [](const Film &a, const Film &b)
             { return a.Orario < b.Orario; });
        StampaFilm(risultati);
        break;
    default:
        cout << "Opzione non valida." << endl;
        break;
    }
}

void StampaFilm(vector<Film> FiltroFilm = filmList)
{
    cout << "ID | Titolo | Regista | Genere | Durata | Sala | Orario | Posti Disponibili" << endl;
    for (const auto &film : FiltroFilm)
    {
        cout << film.id << " | " << film.titolo << " | " << film.regista << " | "
             << film.genere << " | " << film.durata << " min | Sala "
             << film.Num_Sala << " | " << film.Orario << " | "
             << film.Num_Posti_Disponibili << endl;
    }
}

void Menu()
{
    cout << "===== GESTORE CINEMA =====" << endl;
    cout << "1. Aggiungi Film" << endl;
    cout << "2. Modifica Film" << endl;
    cout << "3. Elimina Film" << endl;
    cout << "4. Visualizza Film" << endl;
    cout << "5. Salva su File" << endl;
    cout << "6. Carica da File" << endl;
    cout << "0. Esci" << endl;
    cout << "Scegli un'opzione: ";
}

void SalvaSuFile(string NomeFile = "film.txt", string Separatore = ",")
{
    ofstream file(NomeFile);
    if (!file.is_open())
    {
        cerr << "Errore nell'apertura del file: " << NomeFile << endl;
        return;
    }
    for (const auto &film : filmList)
    {
        file << film.id << Separatore
             << film.titolo << Separatore
             << film.regista << Separatore
             << film.genere << Separatore
             << film.durata << Separatore
             << film.Num_Sala << Separatore
             << film.Orario << Separatore
             << film.Num_Posti_Disponibili << endl;
    }
    file.close();
}

int main()
{
    int scelta;
    while (scelta != 0)
    {

        string Separatore;
        string NomeFile;

        Menu();
        cin >> scelta;
        switch (scelta)
        {
        case 1:
            AggiungiFilm();
            break;
        case 2:
            cout << "Inserisci ID del film da modificare: ";
            int id;
            cin >> id;
            ModificaFilm(id);
            break;
        case 3:
            cout << "Inserisci ID del film da eliminare: ";
            int id;
            cin >> id;
            EliminaFilm(id);
            break;
        case 4:
            VisualizzaFilm();
            break;
        case 5:
            cout << "Inserisci nome del file da salvare (default 'film.txt'): ";
            cin.ignore();
            getline(cin, NomeFile);
            cout << "Separatore (default ','): ";
            getline(cin, Separatore);
            SalvaSuFile(NomeFile.empty() ? "film.txt" : NomeFile, Separatore.empty() ? "," : Separatore);
            break;
        case 6:
            cin.ignore();
            cout << "Inserisci nome del file da caricare: ";
            getline(cin, NomeFile);
            cout << "Separatore (default ','): ";

            getline(cin, Separatore);
            LetturaFile(NomeFile, Separatore.empty() ? "," : Separatore);
            break;
        case 0:
            cout << "Uscita dal programma." << endl;
            break;
        default:
            cout << "Opzione non valida." << endl;
            break;
        }
    }
    return 0;
}
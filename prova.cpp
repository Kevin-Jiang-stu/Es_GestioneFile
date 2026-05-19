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

void StampaFilm(vector<Film> FiltroFilm = {});

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

        film.Num_Posti_Disponibili = stoi(line.substr(pos));

        filmList.push_back(film);
    }

    file.close();
}

void ScritturaFile(string NomeFile, string Separatore = ",")
{
    ofstream file(NomeFile);

    if (!file.is_open())
    {
        cerr << "Errore nella scrittura del file." << endl;
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

void AggiungiFilm()
{
    Film film;

    if (filmList.empty())
        film.id = 1;
    else
        film.id = filmList.back().id + 1;

    cin.ignore();

    cout << "Inserisci Titolo: ";
    getline(cin, film.titolo);

    cout << "Inserisci Regista: ";
    getline(cin, film.regista);

    cout << "Inserisci Genere: ";
    getline(cin, film.genere);

    cout << "Inserisci Durata (in minuti): ";
    cin >> film.durata;

    cout << "Inserisci Numero Sala: ";
    cin >> film.Num_Sala;

    cin.ignore();

    cout << "Inserisci Orario (HH:MM): ";
    getline(cin, film.Orario);

    cout << "Inserisci Numero Posti Disponibili: ";
    cin >> film.Num_Posti_Disponibili;

    filmList.push_back(film);

    cout << "Film aggiunto correttamente." << endl;
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

                cout << "Film eliminato correttamente." << endl;
            }

            return;
        }
    }

    cout << "Film non trovato." << endl;
}

void ModificaFilm(int id)
{
    for (int i = 0; i < filmList.size(); ++i)
    {
        if (filmList[i].id == id)
        {
            cin.ignore();

            cout << "Modifica Titolo (" << filmList[i].titolo << "): ";
            getline(cin, filmList[i].titolo);

            cout << "Modifica Regista (" << filmList[i].regista << "): ";
            getline(cin, filmList[i].regista);

            cout << "Modifica Genere (" << filmList[i].genere << "): ";
            getline(cin, filmList[i].genere);

            cout << "Modifica Durata (" << filmList[i].durata << "): ";
            cin >> filmList[i].durata;

            cout << "Modifica Sala (" << filmList[i].Num_Sala << "): ";
            cin >> filmList[i].Num_Sala;

            cin.ignore();

            cout << "Modifica Orario (" << filmList[i].Orario << "): ";
            getline(cin, filmList[i].Orario);

            cout << "Modifica Posti Disponibili (" << filmList[i].Num_Posti_Disponibili << "): ";
            cin >> filmList[i].Num_Posti_Disponibili;

            cout << "Film modificato correttamente." << endl;

            return;
        }
    }

    cout << "Film non trovato." << endl;
}

void VisualizzaFilm()
{
    cout << endl;

    cout << "1. Lista completa film" << endl;
    cout << "2. Ricerca per titolo o ID" << endl;
    cout << "3. Filtro per sala" << endl;
    cout << "4. Filtro per genere" << endl;
    cout << "5. Film con posti disponibili" << endl;
    cout << "6. Film ordinati per orario" << endl;

    cout << "Scelta: ";

    int scelta;
    cin >> scelta;

    vector<Film> risultati;

    switch (scelta)
    {
    case 1:
    {
        StampaFilm();
        break;
    }

    case 2:
    {
        string input;

        cin.ignore();

        cout << "Inserisci titolo o ID: ";
        getline(cin, input);

        for (int i = 0; i < filmList.size(); i++)
        {
            if (filmList[i].titolo == input ||
                to_string(filmList[i].id) == input)
            {
                risultati.push_back(filmList[i]);
            }
        }

        StampaFilm(risultati);

        break;
    }

    case 3:
    {
        int sala;

        cout << "Inserisci sala: ";
        cin >> sala;

        for (int i = 0; i < filmList.size(); i++)
        {
            if (filmList[i].Num_Sala == sala)
            {
                risultati.push_back(filmList[i]);
            }
        }

        StampaFilm(risultati);

        break;
    }

    case 4:
    {
        string genere;

        cin.ignore();

        cout << "Inserisci genere: ";
        getline(cin, genere);

        for (int i = 0; i < filmList.size(); i++)
        {
            if (filmList[i].genere == genere)
            {
                risultati.push_back(filmList[i]);
            }
        }

        StampaFilm(risultati);

        break;
    }

    case 5:
    {
        for (int i = 0; i < filmList.size(); i++)
        {
            if (filmList[i].Num_Posti_Disponibili > 0)
            {
                risultati.push_back(filmList[i]);
            }
        }

        StampaFilm(risultati);

        break;
    }

    case 6:
    {
        risultati = filmList;

        sort(risultati.begin(), risultati.end(),
             [](Film a, Film b)
             {
                 return a.Orario < b.Orario;
             });

        StampaFilm(risultati);

        break;
    }

    default:
    {
        cout << "Opzione non valida." << endl;
        break;
    }
    }
}

void StampaFilm(vector<Film> FiltroFilm)
{
    if (FiltroFilm.empty())
    {
        FiltroFilm = filmList;
    }

    cout << endl;

    cout << "ID | Titolo | Regista | Genere | Durata | Sala | Orario | Posti" << endl;

    for (const auto &film : FiltroFilm)
    {
        cout << film.id << " | "
             << film.titolo << " | "
             << film.regista << " | "
             << film.genere << " | "
             << film.durata << " min | "
             << film.Num_Sala << " | "
             << film.Orario << " | "
             << film.Num_Posti_Disponibili << endl;
    }

    cout << endl;
}

int main()
{
    int scelta;

    LetturaFile("film.txt");

    do
    {
        cout << endl;

        cout << "===== GESTORE CINEMA =====" << endl;

        cout << "1. Aggiungi Film" << endl;
        cout << "2. Modifica Film" << endl;
        cout << "3. Elimina Film" << endl;
        cout << "4. Visualizza Film" << endl;
        cout << "5. Salva su File" << endl;
        cout << "0. Esci" << endl;

        cout << "Scelta: ";
        cin >> scelta;

        switch (scelta)
        {
        case 1:
        {
            AggiungiFilm();
            break;
        }

        case 2:
        {
            int id;

            cout << "Inserisci ID del film da modificare: ";
            cin >> id;

            ModificaFilm(id);

            break;
        }

        case 3:
        {
            int id;

            cout << "Inserisci ID del film da eliminare: ";
            cin >> id;

            EliminaFilm(id);

            break;
        }

        case 4:
        {
            VisualizzaFilm();
            break;
        }

        case 5:
        {
            ScritturaFile("film.txt");

            cout << "File salvato correttamente." << endl;

            break;
        }

        case 0:
        {
            ScritturaFile("film.txt");

            cout << "Uscita dal programma..." << endl;

            break;
        }

        default:
        {
            cout << "Scelta non valida." << endl;
            break;
        }
        }

    } while (scelta != 0);

    return 0;
}
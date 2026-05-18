#include <iostream>
#include <vector>
#include <fstream>
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
            if(ChiedoConferma("Sei sicuro di voler eliminare questo film?"))
            {
                filmList.erase(filmList.begin() + i);
                cout << "Film con ID " << id << " eliminato." << endl;
            }
            return;
        }
    }
}

int main()
{
    cout << "Benvenuto al Gestore del Cinema!" << endl;
}
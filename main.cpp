
// Registro elettronico sviluppato da
// Marco

#include <cstdlib>
#include <iostream>
#include <print>
#include <string>
#include <vector>

using namespace std;

typedef struct alunno
{
    int matricola;
    string nome;
    string cognome;
    int eta;
    int anno;
    string classe;
    bool bocciato;
} alunno;

typedef struct voto
{
    int IDVoto;
    int matricola;
    string materia;
    int valutazione;
} voto;

static int IDVoto = 0;
static int matricola = 0;

int menu();
void caricaAlunno(vector<alunno> &alunni);
void cancellaAlunno(vector<alunno> &alunni, vector<voto> &voti);
void caricaVoto(vector<alunno> &alunni, vector<voto> &voti);
void modificaVoto(vector<voto> &voti);
void cancellaVoto(vector<voto> &voti);
void visualizzaAlunni(vector<alunno> &alunni);
void visualizzaVoti(vector<alunno> &alunni, vector<voto> &voti);

int main()
{

    vector<alunno> alunni;
    vector<voto> voti;

    int scelta = 0;

    do
    {
        system("cls");
        scelta = menu();
        switch (scelta)
        {
            case 1:
                caricaAlunno(alunni);
                break;
            case 2:
                cancellaAlunno(alunni, voti);
                break;
            case 3:
                caricaVoto(alunni, voti);
                break;
            case 4:
                modificaVoto(voti);
                break;
            case 5:
                cancellaVoto(voti);
                break;
            case 6:
                visualizzaAlunni(alunni);
                break;
            case 7:
                visualizzaVoti(alunni, voti);
                break;
            case 0:
                print("Arrivederci!\n");
                break;
            default:
                print("Scelta non valida, riprova\n");
                break;
        }
    } while (scelta != 0);
}

int menu()
{
    int s;
    print("Benvenuto nel registro elettronico, cosa vuoi fare?\n");
    print("1. Caricare un alunno\n");
    print("2. Cancellare un alunno");
    print("3. Caricare un voto\n");
    print("4. Modificare un voto\n");
    print("5. Cancellare un voto\n");
    print("6. Visualizza tutti gli alunni\n");
    print("7. Visualizza i voti di un alunno e la sua media totale\n");
    print("0. Esci\n");

    cin >> s;
    fflush(stdin);
    system("cls");
    return s;
}

void caricaAlunno(vector<alunno> &alunni)
{
    string nome, cognome, classe;
    int eta, anno;
    bool bocciato;

    print("Inserisci il nome dell'alunno");
    cin >> nome;
    print("Inserisci il cognome dell'alunno");
    cin >> cognome;
    print("Inserisci l'età dell'alunno");
    cin >> eta;
    print("Inserisci l'anno di nascita dell'alunno");
    cin >> anno;
    print("Inserisci la classe dell'alunno");
    cin >> classe;
    print("L'alunno \x82 stato bocciato? ");
    cin >> bocciato;

    if (nome.length() < 2)
    {
        print("Inserisci un nome valido!\n");
    }
    else if (cognome.length() < 2)
    {
        print("Inserisci un cognome valido!\n");
    }
    else if (eta < 14 || eta > 20)
    {
        print("Inserisci un'eta valida! tra i 14 e 20 anni\n");
    }
    else if (anno < 1900 || anno > 2020)
    {
        print("Inserisci un anno di nascita valido! (Tra 1900 e 2020)\n");
    }
    else if (classe.length() != 5)
    {
        print("Inserisci una classe valida nel seguente formato: SezioneCorsoIndirizzo (Esempio: 3CINF)\n");
    }
    else
    {
        alunno temp;
        temp.matricola = matricola;
        temp.nome = nome;
        temp.cognome = cognome;
        temp.eta = eta;
        temp.anno = anno;
        temp.classe = classe;
        temp.bocciato = bocciato;
        alunni.push_back(temp);
        matricola++;

        print("Alunno {} {} caricato con successo\n", alunni.back().nome, alunni.back().cognome);
    }

    system("pause");
}
void cancellaAlunno(vector<alunno> &alunni, vector<voto> &voti)
{
    int matricola;
    println("Inserisci la matricola dell'alunno che vuoi cancellare");
    cin.ignore();
    cin >> matricola;

    int j = 0;

    bool ok = false;
    while (j < alunni.size() && !ok)
    {
        if (alunni[j].matricola == matricola)
        {
            alunni.erase(alunni.begin() + j);
            ok = true;
        }
        j++;
    }

    if (ok)
    {
        bool votoCancellato = false;
        for (int i = voti.size() - 1; i >= 0; i--)
        {
            if (voti[i].matricola == matricola)
            {
                voti.erase(voti.begin() + i);
                votoCancellato = true;
            }
        }

        if (!votoCancellato)
        {
            println("Nessun voto cancellato, l'alunno non aveva voti");
        }

        println("Alunno cancellato con successo");
    }
    else
    {
        println("Alunno non trovato");
    }
}

void caricaVoto(vector<alunno> &alunni, vector<voto> &voti)
{
    int mat;
    println("Inserisci la matricola dell'alunno a cui vuoi aggiungere un voto: ");
    cin >> mat;

    bool trovato = false;
    int i = 0;

    while (i < alunni.size() && !trovato)
    {
        if (alunni[i].matricola == mat)
        {
            trovato = true;
        }
        i++;
    }

    if (!trovato)
    {
        println("Matricola non trovata. Impossibile caricare il voto.");
    }
    else
    {
        string materia;
        int valutazione;

        println("Inserisci la materia: ");
        cin.ignore();
        getline(cin, materia); // per spazi

        println("Inserisci la valutazione (da 1 a 10): ");
        cin >> valutazione;

        if (valutazione < 1 || valutazione > 10)
        {
            println("Valutazione non valida. Deve essere tra 1 e 10.");
        }
        else
        {
            voto nuovoVoto;
            nuovoVoto.IDVoto = IDVoto++;
            nuovoVoto.matricola = mat;
            nuovoVoto.materia = materia;
            nuovoVoto.valutazione = valutazione;

            voti.push_back(nuovoVoto);

            println("Voto caricato con successo per l'alunno con matricola {}",mat);
        }
    }
}

void modificaVoto(vector<voto> &voti)
{
    int id;
    println("Inserisci l'ID del voto che vuoi modificare: ");
    cin.ignore();
    cin >> id;

    bool trovato = false;

    for (int i = 0; i < voti.size(); i++)
    {
        if (voti[i].IDVoto == id)
        {
            trovato = true;
            println("Voto trovato! Materia attuale: {} \n valutazione attuale: {} ",voti[i].materia,voti[i].valutazione);

            string nuovaMateria;
            int nuovaValutazione;

            println("Inserisci la nuova materia (oppure premi invio per non modificarla): ");
            cin.ignore();
            cin >> nuovaMateria;

            if (!nuovaMateria.empty())
            {
                voti[i].materia = nuovaMateria;
            }

            println("Inserisci la nuova valutazione (da 1 a 10): ");
            cin.ignore();
            cin >> nuovaValutazione;

            if (nuovaValutazione < 1 || nuovaValutazione > 10)
            {
                println("Valutazione non valida. Deve essere tra 1 e 10. Modifica annullata.");
                return;
            }

            voti[i].valutazione = nuovaValutazione;

            println("Voto modificato con successo!");
        }
    }

    if (!trovato)
    {
        println("Voto con ID {} non trovato",id);
    }
}

void cancellaVoto(vector<voto> &voti)
{
    int id;
    println("Inserisci l'ID del voto che vuoi cancellare: ");
    cin >> id;

    bool trovato = false;

    int i = 0;

    while (i < voti.size())
    {
        if (voti[i].IDVoto == id)
        {
            voti.erase(voti.begin() + i);
            trovato = true;
            println("Voto cancellato con successo!");
            // non incrementiamo i perché abbiamo già trovato e cancellato
            // e vogliamo uscire dal ciclo

            i = voti.size(); // forza uscita
        }
        else
        {
            i++;
        }
    }

    if (!trovato)
    {
        println("Nessun voto trovato con l'ID specificato.");
    }

    if (!trovato)
    {
        println("Voto con ID {} non trovato",id);
    }
}

void visualizzaAlunni(vector<alunno> &alunni)
{
    if (!alunni.empty())
    {
        print("\nLista degli alunni:\n");
        for (int i = 0; i < alunni.size(); i++)
        {
            println("Matricola: {}",alunni[i].matricola);
            println("Nome: {} {} ", alunni[i].nome,alunni[i].cognome);
            println("Eta: {} anni",alunni[i].eta);
            println("Anno di nascita: {} ",alunni[i].anno);
            println("Classe: {}", alunni[i].classe);
            println("Bocciato: {} ",alunni[i].bocciato ? "Sì" : "No");
            println("-----------------------------");
        }
    }
    else
    {
        println("Nessun alunno presente.");
    }
}

void visualizzaVoti(vector<alunno> &alunni, vector<voto> &voti)
{
    int mat;
    println("Inserisci la matricola dell'alunno: ");
    cin >> mat;

    bool alunnoTrovato = false;
    string nome, cognome;

    int i = 0;
    while (i < alunni.size() && !alunnoTrovato)
    {
        if (alunni[i].matricola == mat)
        {
            alunnoTrovato = true;
            nome = alunni[i].nome;
            cognome = alunni[i].cognome;
        }
        i++;
    }

    if (!alunnoTrovato)
    {
        println("Alunno non trovato.");
        return;
    }

    println("\nVoti dell'alunno {} {} (Matricola: {})",nome,cognome,mat);

    int somma = 0;
    int conteggio = 0;

    int j = 0;
    while (j < voti.size())
    {
        if (voti[j].matricola == mat)
        {
            println("Materia: {} | Valutazione: {}",voti[j].materia,voti[j].valutazione);
            somma += voti[j].valutazione;
            conteggio++;
        }
        j++;
    }

    if (conteggio == 0)
    {
        println("Nessun voto registrato per questo alunno.");
    }
    else
    {
        double media = static_cast<double>(somma) / conteggio; // cast di somma
        println("Media totale: ", media);
    }
}

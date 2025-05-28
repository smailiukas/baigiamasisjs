#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cctype>
#include <algorithm>

using namespace std;

// Deklaracijos
void rodytiTaisykles();
void rodytiKartuves(int klaidos);
vector<string> gautiZodziuSarasa();
string pasirinktiAtsitiktiniZodi(const vector<string>& zodziai);
string paruostiSlepiamaZodi(const string& zodis);
bool arRaideBuvoSpeta(char raide, const vector<char>& spetosRaides);
void atnaujintiSlepiamaZodi(string& slepiamas, const string& tikrasisZodis, char speta);
bool arZodisAtspetas(const string& slepiamas);
void zaisti();

int main() {
    // Atsitiktinių skaiciu generatorius
    srand(static_cast<unsigned int>(time(nullptr)));
    
    // Sveikinam zaideja
    cout << "\n=== KARTUVES (HANGMAN) ===\n" << endl;
    
    char pasirinkimas;
    do {
        // Rodom pagr meniu
        cout << "\nPasirink:\n";
        cout << "1. Žaisti\n";
        cout << "2. Taisyklės\n";
        cout << "3. Išeiti\n";
        cout << "Tavo pasirinkimas: ";
        cin >> pasirinkimas;
        
        // Apdorojam vartotojo pasirinkima
        switch (pasirinkimas) {
            case '1':
                zaisti();
                break;
            case '2':
                rodytiTaisykles();
                break;
            case '3':
                cout << "Ačiū, kad žaidei! Iki kito karto!\n";
                break;
            default:
                cout << "Neteisingas pasirinkimas. Bandyk dar kartą.\n";
        }
    } while (pasirinkimas != '3');
    
    return 0;
}

// Funkcija, kuri rodo zaidimo taisykles
void rodytiTaisykles() {
    cout << "\n=== ŽAIDIMO TAISYKLĖS ===\n";
    cout << "1. Kompiuteris parenka slaptą žodį.\n";
    cout << "2. Tu turi atspėti žodį, spėliojant po vieną raidę.\n";
    cout << "3. Kiekvienas neteisingas spėjimas priartina tave prie pralaimėjimo.\n";
    cout << "4. Po 6 neteisingų spėjimų, žaidimas baigiasi pralaimėjimu.\n";
    cout << "5. Jei atspėji visas žodžio raides prieš pasibaigiant bandymams, tu laimi!\n";
    cout << "\nSėkmės!\n";
}

// Funkcija, kuri rodo kartuviu grafika pagal klaidu skaiciu
void rodytiKartuves(int klaidos) {
    cout << "\n";
    cout << " +---+\n";
    
    // Piesiam kartuviu elementus pagal klaidu skaiciu
    if (klaidos >= 1) {
        cout << " |   |\n";
    } else {
        cout << " |    \n";
    }
    
    if (klaidos >= 2) {
        cout << " |   O\n";
    } else {
        cout << " |    \n";
    }
    
    if (klaidos == 3) {
        cout << " |   |\n";
    } else if (klaidos == 4) {
        cout << " |  /|\n";
    } else if (klaidos >= 5) {
        cout << " |  /|\\\n";
    } else {
        cout << " |    \n";
    }
    
    if (klaidos == 6) {
        cout << " |  / \n";
    } else if (klaidos >= 7) {
        cout << " |  / \\\n";
    } else {
        cout << " |    \n";
    }
    
    cout << " |    \n";
    cout << "=======\n";
}

// Funkcija, kuri grazina zodziu sarasa
vector<string> gautiZodziuSarasa() {
    // Zodeliu sarasas
    vector<string> zodziai = {
        "programavimas", "kompiuteris", "algoritmas", "internetas",
        "duomenys", "funkcija", "kintamasis", "objektas", "metodas",
        "masyvas", "ciklas", "salyga", "klasė", "paveldėjimas",
        "biblioteka", "kompiliatorius", "klaida", "sistema", "tinklapis",
        "serveris", "aplikacija", "vartotojas", "slaptažodis", "saugumas",
        "grafika", "animacija", "žaidimas", "virtuali", "realybė"
    };
    
    return zodziai;
}

// Funkcija, kuri pasirenka atsitiktini zodeli is saraso
string pasirinktiAtsitiktiniZodi(const vector<string>& zodziai) {
    // Pasirenkame atsitiktini index is zodeliu saraso
    int indeksas = rand() % zodziai.size();
    return zodziai[indeksas];
}

// Funkcija, kuri paruosia slepiama zodi (su bruksneliais vietoj raidziu)
string paruostiSlepiamaZodi(const string& zodis) {
    // Pakeičiame visas raides brūkšneliais
    return string(zodis.length(), '_');
}

// Funkcija, kuri tikrina, ar raide jau buvo speta
bool arRaideBuvoSpeta(char raide, const vector<char>& spetosRaides) {
    // Tikriname, ar raide yra spetu raidziu sarase
    return find(spetosRaides.begin(), spetosRaides.end(), raide) != spetosRaides.end();
}

// Funkcija, kuri atnaujina slepiamą zodi, kai atspejama raide
void atnaujintiSlepiamaZodi(string& slepiamas, const string& tikrasisZodis, char speta) {
    // Einame per visa zodi ir atnaujiname slepiama žodi, jei raide atitinka
    for (size_t i = 0; i < tikrasisZodis.length(); ++i) {
        if (tolower(tikrasisZodis[i]) == tolower(speta)) {
            slepiamas[i] = tikrasisZodis[i];
        }
    }
}

// Funkcija, kuri tikrina, ar zodis jau pilnai atspetas
bool arZodisAtspetas(const string& slepiamas) {
    // Tikrinam, ar slepiamame zodyje nebera bruksneliu
    return slepiamas.find('_') == string::npos;
}

// Pagrindine zaidimo funkcija
void zaisti() {
    // Gaunam zodeliu sarasa
    vector<string> zodziai = gautiZodziuSarasa();
    
    // Pasirenkam atsitiktini zodeli
    string tikrasisZodis = pasirinktiAtsitiktiniZodi(zodziai);
    
    // Paruosiam slepiamą zodi
    string slepiamas = paruostiSlepiamaZodi(tikrasisZodis);
    
    // Kintamieji zaidimo eigai sekti
    int likusiosBandymai = 7;  // Max klaidos
    vector<char> spetosRaides;  // Spetos raides
    bool zaidimasBaigtas = false;
    
    // Pagrindinis zaidimo ciklas
    while (!zaidimasBaigtas) {
        // Rodom dabartine zaidino busena
        system("clear");  // Isvalom ekrana
        
        // Rodom pacias kartuves
        rodytiKartuves(7 - likusiosBandymai);
        
        // Rodom slepiama zodi
        cout << "\nŽodis: ";
        for (char c : slepiamas) {
            cout << c << " ";
        }
        cout << endl;
        
        // Rodom spetas raides
        cout << "\nSpėtos raidės: ";
        for (char c : spetosRaides) {
            cout << c << " ";
        }
        cout << endl;
        
        // Rodom likusius bandymus
        cout << "\nLikę bandymai: " << likusiosBandymai << endl;
        
        // Jei nebera bandymu, nutraukiam zaidima
        if (likusiosBandymai <= 0) {
            cout << "\nTu pralaimėja! Teisingas žodis buvo: " << tikrasisZodis << endl;
            zaidimasBaigtas = true;
            break;
        }
        
        // Jei zodis spetas, nutraukiam zaidima
        if (arZodisAtspetas(slepiamas)) {
            cout << "\nSveikinu! Tu atspėjai žodį: " << tikrasisZodis << endl;
            zaidimasBaigtas = true;
            break;
        }
        
        // Prasom zaidejo speti raide
        char speta;
        cout << "\nĮvesk raidę: ";
        cin >> speta;
        
        // Konvertuojam i mazaja raide
        speta = tolower(speta);
        
        // Funkcija, kuri tikrina, ar ivestis yra raide (įskaitant lietuviškas raides)
        // Lietuviškų raidžių ASCII kodai yra už standartinio ASCII diapazono ribų
        // Todėl naudojame paprastą patikrinimą, ar tai yra raidė arba lietuviška raidė
        bool yraRaide = isalpha(speta) || 
                       speta == 'ą' || speta == 'č' || speta == 'ę' || speta == 'ė' || 
                       speta == 'į' || speta == 'š' || speta == 'ų' || speta == 'ū' || speta == 'ž';
        
        if (!yraRaide) {
            cout << "Prašau įvesti tik raides!" << endl;
            cin.ignore(10000, '\n');  // Isvalom ivesties buferi
            cin.get();  // Laukiam, kol vartotojas paspaus Enter
            continue;
        }
        
        // Tikrinam, ar raide jau buvo speta
        if (arRaideBuvoSpeta(speta, spetosRaides)) {
            cout << "Šią raidę jau spėjai!" << endl;
            cin.ignore(10000, '\n');  // Isvalom ivesties buferi
            cin.get();  // Laukiam, kol vartotojas paspaus Enter
            continue;
        }
        
        // Pridedam raide prie spetu raidziu saraso
        spetosRaides.push_back(speta);
        
        // Tikrinam, ar raide yra zodyje
        // Naudojame savo patikrinimą vietoj find(), kad galėtume apdoroti lietuviškas raides
        bool raideYraZodyje = false;
        for (char c : tikrasisZodis) {
            if (tolower(c) == tolower(speta)) {
                raideYraZodyje = true;
                break;
            }
        }
        
        if (raideYraZodyje) {
            // Jei raide yra zodyje, atnaujinam slepiama zodi
            atnaujintiSlepiamaZodi(slepiamas, tikrasisZodis, speta);
            cout << "Teisingai! Raidė \"" << speta << "\" yra žodyje." << endl;
        } else {
            // Jei raides nera zodyje, sumazinam likusiu bandymu skaičiu
            likusiosBandymai--;
            cout << "Deja, raidės \"" << speta << "\" nėra žodyje." << endl;
        }
        
        // Laukiam, kol vartotojas paspaus Enter
        cin.ignore(10000, '\n');
        cin.get();
    }
    
    // Pabaigos pranesimas
    cout << "\nŽaidimas baigtas! Spausk Enter, kad grįžtum į meniu...";
    cin.ignore(10000, '\n');
    cin.get();
}
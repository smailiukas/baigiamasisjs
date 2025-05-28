#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

class Kartuves {
private:
    vector<string> zodziuSarasas;
    string pasirinktasZodis;
    string uzmaskuotasZodis;
    set<char> spejimai;
    map<char, bool> raidesZemelapis;
    int maxBandymu;
    int dabartinisBandymas;

    void pasirinkZodi() {
        srand(time(0));
        int indeksas = rand() % zodziuSarasas.size();
        pasirinktasZodis = zodziuSarasas[indeksas];
        uzmaskuotasZodis = string(pasirinktasZodis.length(), '_');
        for (char c : pasirinktasZodis) {
            raidesZemelapis[c] = false;
        }
    }

    void atnaujintiUzmaskuotaZodi(char raide) {
        for (size_t i = 0; i < pasirinktasZodis.length(); i++) {
            if (pasirinktasZodis[i] == raide) {
                uzmaskuotasZodis[i] = raide;
                raidesZemelapis[raide] = true;
            }
        }
    }

    void rodytiKartuves() {
        vector<string> kartuves = {
            "  +---+\n"
            "  |   |\n"
            "      |\n"
            "      |\n"
            "      |\n"
            "      |\n"
            "=========\n",

            "  +---+\n"
            "  |   |\n"
            "  O   |\n"
            "      |\n"
            "      |\n"
            "      |\n"
            "=========\n",

            "  +---+\n"
            "  |   |\n"
            "  O   |\n"
            "  |   |\n"
            "      |\n"
            "      |\n"
            "=========\n",

            "  +---+\n"
            "  |   |\n"
            "  O   |\n"
            " /|   |\n"
            "      |\n"
            "      |\n"
            "=========\n",

            "  +---+\n"
            "  |   |\n"
            "  O   |\n"
            " /|\\  |\n"
            "      |\n"
            "      |\n"
            "=========\n",

            "  +---+\n"
            "  |   |\n"
            "  O   |\n"
            " /|\\  |\n"
            " /    |\n"
            "      |\n"
            "=========\n",

            "  +---+\n"
            "  |   |\n"
            "  O   |\n"
            " /|\\  |\n"
            " / \\  |\n"
            "      |\n"
            "=========\n"
        };
        cout << kartuves[dabartinisBandymas];
    }

public:
    Kartuves(vector<string> zodziai, int maxLeidimu = 6)
        : zodziuSarasas(zodziai), maxBandymu(maxLeidimu), dabartinisBandymas(0) {
        pasirinkZodi();
    }

    void zaisti() {
        while (dabartinisBandymas < maxBandymu && uzmaskuotasZodis != pasirinktasZodis) {
            rodytiKartuves();
            cout << "\nZodis: " << uzmaskuotasZodis << endl;
            cout << "Spetos raides: ";
            for (char c : spejimai) cout << c << ' ';
            cout << "\nLike bandymai: " << maxBandymu - dabartinisBandymas << endl;

            cout << "Ivesk raide: ";
            char spejimas;
            cin >> spejimas;
            spejimas = tolower(spejimas);

            if (!isalpha(spejimas)) {
                cout << "Ivesk tik raide!" << endl;
                continue;
            }

            if (spejimai.count(spejimas)) {
                cout << "Si raide jau buvo speta!" << endl;
                continue;
            }

            spejimai.insert(spejimas);

            if (raidesZemelapis.count(spejimas)) {
                atnaujintiUzmaskuotaZodi(spejimas);
                cout << "Teisingai!" << endl;
            } else {
                dabartinisBandymas++;
                cout << "Neteisingai!" << endl;
            }
        }

        rodytiKartuves();
        if (uzmaskuotasZodis == pasirinktasZodis) {
            cout << "\nSveikinu! Atspejai zodi: " << pasirinktasZodis << endl;
        } else {
            cout << "\nPralaimejai! Teisingas zodis buvo: " << pasirinktasZodis << endl;
        }
    }
};

int main() {
    vector<string> zodziai = {"programa", "kartuves", "kodas", "objektas", "vektorius"};
    Kartuves.zaidimas(zodziai);
    zaidimas.zaisti();
    return 0;
}
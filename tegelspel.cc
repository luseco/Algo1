// Implementatie van klasse TegelSpel

#include "tegelspel.h"
#include "standaard.h"
#include <fstream>   // voor inlezen van spel
#include <iostream>

//*************************************************************************

TegelSpel::TegelSpel () {}  // default constructor

//*************************************************************************

int TegelSpel::getSchalen () {
  return M;
}  // getSchalen

//*************************************************************************

string TegelSpel::getPot () {
  return pot;
}  // getPot

//*************************************************************************

vector< pair <int,int> > TegelSpel::getInhoudSchalen () { 
  vector<pair<int, int>> inhoudSchalen;
  
  for (string& schaal : schalen) {
    int g = 0, b = 0;
    for (char& c : schaal) {
      if (c == 'g') {
        g++;
      }
      else {
        b++;
      }
    }
    inhoudSchalen.push_back(make_pair(g, b));
  }

  return inhoudSchalen;
}  // getInhoudSchalen

//*************************************************************************

vector<pair<int, int>> TegelSpel::getInhoudRijen (int speler) {
  vector<pair<int, int>> inhoudRijen;

  if (speler == 1) {
    return speler1;
  }
  if (speler == 2) {
    return speler2;
  }

  return inhoudRijen;
}  // getInhoudRijen

//*************************************************************************

bool TegelSpel::leesInSpel (const char* invoernaam) {
  ifstream invoer;
  string regel;

  if (!checkFormat(invoernaam)) { //Checkt de format van het bestand
    return false;
  }
  
  invoer.open(invoernaam);
  getline(invoer, regel);
  pot = regel; //Leest de pot in

  for (int i = 0; i < 4; i++) { //Leest de data van het spel in
    invoer >> *pars[i];
  }

  for (int i = 0; i < M; i++) { //Vult de schalen met de inhoud van de pot
    schalen.push_back(pot.substr(0, N)); //!!!doet rare dingen wanneer pot te klein
    pot.erase(0, N);
  }

  getline(invoer, regel);
  for (int i = 0; i < K; i++) { //Leest de velden van speler 1 in
    getline(invoer, regel);
    speler1.push_back(make_pair(regel[0] - '0', regel[2] - '0'));
  }
  for (int i = 0; i < K; i++) { //Leest de velden van speler 2 in
    getline(invoer, regel);
    speler2.push_back(make_pair(regel[0] - '0', regel[2] - '0'));
  }
  invoer >> beurt; //Leest welke speler aan de beurt is in
  beurt++;

  invoer.close();
  return true;
}  // leesInSpel

//*************************************************************************

bool TegelSpel::eindstand () { //joelle
vector< pair <int,int> > inhoudRijen;
int MaxRij = *pars[2];
int speler = 1; 
inhoudRijen = getInhoudRijen(speler);

for (const auto& rij : inhoudRijen) {
    int eerste = rij.first; 
    int tweede = rij.second;
    if ( eerste == MaxRij || tweede == MaxRij){
        return true;
    }//schalen in een array pair ztten want ze moeten genummerd worden van 0 -> m-1
}
return false;
    // Retourneer:
    // * true, als we een eindstand hebben bereikt
    // * false, als we geen eindstand hebben bereikt
} // eindstand

//*************************************************************************

void TegelSpel::drukAf () {
  if (!isspace(pot[0])) {
    cout << "Pot: " << pot << endl;
  }
  else {
    cout << "Pot: Leeg" << endl;
  }

  int i = 1;
  cout << "Schalen:" << endl;
  for (string& schaal : schalen) {
    cout <<i++ << ": " << sortSchaal(schaal) << "  ";
  }

  cout << "\n\n" << "   Speler 1    Speler 2" << endl
                 << "   --------    --------" << endl;
  for (int j = 0; j < K; j++) {
    cout << j + 1 << "| " 
         << string(speler1[j].first, 'g') 
         << string(speler1[j].second, 'b')
         << string(K - speler1[j].first - speler1[j].second, '#')
         << string(MaxPerRij - K + 6, ' ');
    cout << string(speler2[j].first, 'g') 
         << string(speler2[j].second, 'b') 
         << string(K - speler2[j].first - speler2[j].second, '#') << endl;
  }

  cout << endl << "Aan de beurt: Speler " << beurt << endl;
}  // drukAf

//*************************************************************************

vector< pair<int,char> > TegelSpel::bepaalVerschillendeZetten () {
    vector<pair<int, char>> zetten;
    vector<pair<int, int>> inhoudSchalen = {
        make_pair(4, 0),
        make_pair(2, 3),
        make_pair(1, 1)
    };

    bool verschillend = true;
    bool geldig = true;

    for (const auto& s : inhoudSchalen) {
        if ((s.first != s.second) || (s.first != '0' && s.second != '0')) {
            verschillend = true;
        }
    }//verschillend


for (int i = 0; i < 10; i++) {
        pair<int, char> nieuwPaar = make_pair(i, 'g');
        pair<int, char> Paar = make_pair(i, 'b');
        zetten.push_back(nieuwPaar);
        zetten.push_back(Paar);
    }

return zetten;
}  // bepaalVerschillendeZetten

//*************************************************************************

bool TegelSpel::doeZet (int schaal, char kleur) {
  bool geldig = true;
  pair<int, char> zet = make_pair(schaal, kleur);

  if (schaal < 1 || schaal > M) {
    geldig = false;
  }
  else if (schalen[schaal - 1].find(kleur) == -1) {
    geldig = false;
  }
  else {
    for (pair<int, char>& mogelijk : bepaalVerschillendeZetten()) {
      geldig = false;
      if (zet == mogelijk) {
        geldig = true;
        break;
      }
    }
  }
  
  if (geldig) {
    //erase(schalen[schaal - 1], kleur);
  }

  return geldig;
}  // doeZet

//*************************************************************************

bool TegelSpel::unDoeZet () { //ibraheem 
  // TODO: implementeer deze memberfunctie

  return true;

}  // unDoeZet

//*************************************************************************

int TegelSpel::besteScore (pair<int,char> &besteZet,
                             long long &aantalStanden) {
  // TODO: implementeer deze memberfunctie

  return 0;

}  // besteScore

//*************************************************************************

pair<int,char> TegelSpel::bepaalGoedeZet (int nrSimulaties) {
  pair<int,char> goedeZet;

  // TODO: implementeer deze memberfunctie

  return goedeZet;

}  // bepaalGoedeZet

//*************************************************************************

int TegelSpel::bepaalGoedeScore () {
  // TODO: implementeer deze memberfunctie

  return 0;

}  // bepaalGoedeScore

//*************************************************************************

void TegelSpel::doeExperiment () {
  // TODO: implementeer deze memberfunctie

}  // doeExperiment

//*************************************************************************

bool TegelSpel::checkFormat(const char* invoernaam) {//Checkt de format van een bestand
  ifstream invoer;
  string regel;
  int getal;

  invoer.open(invoernaam);
  if (!invoer) { //Checkt of het bestand opent/bestaat
    return false;
  }

  getline(invoer, regel);
  for (char& c : regel) { //Checkt de pot
    if (c != 'g' && c != 'b' && !isspace(c)) {
      return false;
    }
  }

  for (int i = 0; i < 4; i++) { //Checkt of speldata de max. waarden overschreidt
    invoer >> getal;
    if (getal < 1 || getal > maxPars[i]) {
      return false;
    }
  }

  for (int i = 0; i < 0; i++) { //Checkt of data van de spelers klopt
    break;
  }

  //Checkt of het klopt wie aan de beurt is
  //Checkt of het bestand eindigt

  return true;
}

string TegelSpel::sortSchaal(string schaal) {
  string sorted = "";
  int g = 0, b = 0;

  for (char& c : schaal) {
    if (c == 'g') {
      g++;
    }
    else {
      b++;
    }
  }

  sorted.append(g, 'g');
  sorted.append(b, 'b');
  return sorted;
}
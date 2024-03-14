// Implementatie van klasse TegelSpel

#include "tegelspel.h"
#include "standaard.h"
#include <fstream>   // voor inlezen van spel
#include <iostream>

//*************************************************************************

TegelSpel::TegelSpel () {}  // default constructor

//*************************************************************************

int TegelSpel::getSchalen () { //joelle
  return M;
}

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
    int speler = 1;
    vector< pair <int,int> > inhoudRijen = getInhoudRijen(speler);
    vector< pair <int,int> > inhoudSchalen = getInhoudSchalen();
    int MaxRij = *pars[2];

for (pair <int,int> rij : inhoudRijen) {
    if (( rij.first == MaxRij || rij.second == MaxRij) ||
        (rij.first > MaxRij || rij.second > MaxRij))
        return true;
}//for

for  (pair <int,int> schaal :inhoudSchalen) {
    if (schaal.first == '0' && schaal.second == '0'){
        return true;
    }
}//for 

return false;
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

vector< pair<int,char> > TegelSpel::bepaalVerschillendeZetten () { //joelle
    vector<pair<int, char>> zetten;
    int MaxRij = *pars[2];
    int speler = 1;
    vector<pair<int, int>> inhoudSchalen = getInhoudSchalen();
    vector<pair<int, int>> inhoudRijen = getInhoudRijen(speler);
    bool verschillend = false, geldig = true;

    for (pair<int, int>& schaal : inhoudSchalen) {
        if ((schaal.first != schaal.second) || (schaal.first != 0 && schaal.second != 0)) {
            verschillend = true;
        }
    }

    for (pair<int, int> &rij : inhoudRijen) {
        if ((rij.second == '0' && (rij.first > MaxRij)) ||
            (rij.first == '0' && (rij.second > MaxRij))) {
            geldig = false;
            cout << rij.first << " " << rij.second << endl;
        }
    }//alse zet .first + rij.firsr > maxrij

    if (verschillend && geldig) {
        for (const auto& schaal : inhoudSchalen) {
            zetten.push_back(pair<int, char>(schaal.first, 'g'));
            zetten.push_back(pair<int, char>(schaal.first, 'b'));
        }
    }

    return zetten;
}
    

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

// Bepaal met behulp van brute force en recursie de eindscore voor
    // de speler die in de huidige stand (= de stand van de huidige
    // recursieve aanroep) aan de beurt is, wanneer beide spelers vanaf
    // dit punt optimaal verder spelen.
    // De score is gelijk aan het aantal volle rijen van de speler min
    // het aantal volle rijen van de andere speler.
    // Post:
    // * als de huidige stand geen eindstand was, bevat parameter
    //   besteZet een paar (schaal,kleur) dat de huidige speler
    //   in de eerstvolgende zet moet kiezen, om de beste score te bereiken
    // * anders bevat parameter besteZet een passende default waarde
    // * aantalStanden is gelijk aan het aantal standen dat we hebben
    //   bekeken bij het bepalen van de beste eindscore
    // * de stand in het spel is nog onveranderd
  return 0;

}  // besteScore

//*************************************************************************

pair<int,char> TegelSpel::bepaalGoedeZet (int nrSimulaties) {
  pair<int,char> goedeZet;
// Bepaal een `goede zet' voor de speler die in de huidige stand aan
    // aan de beurt is: een zet die ertoe leidt dat hij (na deze ene zet)
    // met nrSimulaties keer random uitspelen een zo hoog mogelijke
    // gemiddelde score haalt.
    // Controleer eerst of de huidige stand geen eindstand is.
    // Retourneer:
    // * de gevonden zet (rij,kolom), als het geen eindstand is
    // * een passende default waarde, als het al wel een eindstand is


  return goedeZet;

}  // bepaalGoedeZet

//*************************************************************************

int TegelSpel::bepaalGoedeScore () {
  

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
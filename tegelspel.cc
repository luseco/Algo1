// Implementatie van klasse TegelSpel

#include "tegelspel.h"
#include "standaard.h"
#include <fstream>   // voor inlezen van spel
#include <iostream>

//*************************************************************************

TegelSpel::TegelSpel () {
  // TODO: implementeer zo nodig deze constructor

}  // default constructor

//*************************************************************************

int TegelSpel::getSchalen () { //joelles
  return *pars[1];
}  // getSchalen

//*************************************************************************

string TegelSpel::getPot () { //joelle
  string retString;
  pot = retString;
  return retString;
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

  for (int i = 0; i < M; i++) {
    schalen.push_back(pot.substr(0, N));
    pot.erase(0, N);
  }

  getline(invoer, regel);
  for (int i = 0; i < K; i++) { //Leest de velden van de spelers in
    getline(invoer, regel);
    speler1.push_back(make_pair(regel[0] - '0', regel[2] - '0'));
  }
  for (int i = 0; i < K; i++) { //Leest de velden van de spelers in
    getline(invoer, regel);
    speler2.push_back(make_pair(regel[0] - '0', regel[2] - '0'));
  }
  invoer >> beurt; //Leest welke speler aan de beurt is in
  
  invoer.close();
  return true;
}  // leesInSpel

//*************************************************************************

bool TegelSpel::eindstand () { //joelle
vector< pair <int,int> > inhoudRijen;
int MaxRij = *pars[2];
int speler = 1; 
inhoudRijen = getInhoudRijen(speler);


} // eindstand

//*************************************************************************

void TegelSpel::drukAf () {
  if (pot != "") {
    cout << "Pot: " << pot << endl;
  }
  int i = 1;
  for (string& schaal : schalen) {
    cout << "Schaal " << i << ": " << sortSchaal(schaal) << endl;
    i++;
  }
}  // drukAf

//*************************************************************************

vector< pair<int,char> > TegelSpel::bepaalVerschillendeZetten () { //joelle
    vector<pair<int, char>> zetten;
    vector<pair<int, int>> inhoudSchalen = {
        make_pair(4, 0),
        make_pair(2, 3),
        make_pair(1, 1)
    };

    bool verschillend = false;
    bool geldig = true;

    for (const auto& s : inhoudSchalen) {
        cout << s.first << " " << s.second << endl;
        if ((s.first != s.second) || (s.first != 0 && s.second != 0)) {
            verschillend = true;
        }
    }//verschillend


     /*
    als zetten ( int char) -> char is niet in retstring 
    zetten ( int char) if if char is g inhoudrij.first +int > N enn 
    if char is binhoudrij.second + int > N
    }
}*/


// Bepaal alle verschillende, geldige zetten (schaal,kleur) in de huidige
    // stand.
    // Een zet met een kleur die niet voorkomt op de schaal is niet geldig.
    // Een zet met een kleur die vaker voorkomt op de schaal dan de speler
    // in een rij kwijt kan, is niet geldig.
    // Retourneer:
    // * Een vector met alle verschillende geldige zetten (schaal,kleur);
    //   de volgorde van de zetten maakt niet uit.
return zetten;

}  // bepaalVerschillendeZetten

//*************************************************************************

bool TegelSpel::doeZet (int schaal, char kleur) { //ibraheem
  // TODO: implementeer deze memberfunctie

  return true;

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
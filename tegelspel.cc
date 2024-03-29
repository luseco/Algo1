// Implementatie van klasse TegelSpel

#include "tegelspel.h"
#include "standaard.h"
#include <fstream>   // voor inlezen van spel
#include <iostream>
#include <set>

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
    schalen[i] = sortSchaal(schalen[i]);
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

for (pair <int,int> rij : inhoudRijen) {
    if (( rij.first == K || rij.second == K) ||
        (rij.first > K|| rij.second > K))
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

  int i = 0;
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
    vector <int> schaal;
    vector<int> temp;
    vector <int> temp2;
    vector<pair<int, char>> zetten;
    vector<pair<int, int>> inhoudSchalen = getInhoudSchalen();
    vector<pair<int, int>> inhoudRijen = getInhoudRijen(beurt);
    int getschalen = getSchalen();
    bool geldig_g =false, geldig_b= false;
    bool verschillend = false;

    for (int i = 0; i < getschalen; ++i) {
        for (int j = i + 1; j < getschalen; ++j) {
            if (inhoudSchalen[i].first == inhoudSchalen[j].first && inhoudSchalen[i].second == inhoudSchalen[j].second) {
                schaal.push_back(i);
                verschillend = true;
            }
        }
    }

    for (int i = 0; i < getschalen; ++i) {
    int found_b = false, found_g = false;
    for (pair<int, int> rij : inhoudRijen) {
        if (((rij.second == 0 && inhoudSchalen[i].first != 0 && rij.first + inhoudSchalen[i].first <= K) || (rij.second == 0 && rij.first == 0)) && !found_g) {
            geldig_g = true, found_g = true;
            if ( !verschillend){
                temp.push_back(i);
            }
        }
        if (((rij.first == 0 && inhoudSchalen[i].second != 0 && rij.second + inhoudSchalen[i].second <= K) || (rij.second == 0 && rij.first == 0)) && !found_b) {
            geldig_b = true, found_b = true;
             if ( !verschillend){
                temp2.push_back(i);
            }
        }
        if (found_b && found_g)
            break;
    }
}

cout<< " "<< endl;
for ( const auto & num : schaal){
cout<< num<<endl;
}

    for (int & i : schaal) {
        if (geldig_g) zetten.push_back(make_pair(i, 'g'));
        if (geldig_b) zetten.push_back(make_pair(i, 'b'));
    }if (geldig_g) {
        for (int & j : temp) zetten.push_back(make_pair(j, 'g'));
    }if (geldig_b ) {
        for (int & k : temp2) zetten.push_back(make_pair(k, 'b'));
    }

    return zetten;

}
//*************************************************************************

bool TegelSpel::doeZet (int schaal, char kleur) {
  bool geldig = true;
  pair<int, char> zet = make_pair(schaal, kleur);

  if (schaal < 0 || schaal >= M) {
    geldig = false;
    cout << endl << "Schaal bestaat niet.";
  }
  else if (schalen[schaal].find(kleur) == string::npos) {
    geldig = false;
    cout << endl << "Geen geldige kleur.";
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
  
  if (!geldig) {
    return geldig;
  }
  int nTegelsZet = 0;
  int offset = 0;

  for (char& tegel : schalen[schaal]) {
    if (tegel == kleur) {
      nTegelsZet++;
    }
  }

  if (kleur == 'b') {
    offset = schalen[schaal].find('b');
  }

  schalen[schaal].erase(offset, nTegelsZet);
  schalen[schaal].append(pot.substr(0, nTegelsZet));
  schalen[schaal] = sortSchaal(schalen[schaal]);
  pot.erase(0, nTegelsZet);

  if (beurt == 1) {
    beurt = 2;
    for (pair<int, int>& rij : speler1) {
      if (kleur == 'g' && nTegelsZet <= K - rij.first && rij.second == 0) {
        rij.first += nTegelsZet;
        break;
      }
      if (kleur == 'b' && nTegelsZet <= K - rij.second && rij.first == 0) {
        rij.second += nTegelsZet;
        break;
      }
    }
  } else {
    beurt = 1;
    for (pair<int, int>& rij : speler2) {
      if (kleur == 'g' && nTegelsZet <= K - rij.first && rij.second == 0) {
        rij.first += nTegelsZet;
        break;
      }
      if (kleur == 'b' && nTegelsZet <= K - rij.second && rij.first == 0) {
        rij.second += nTegelsZet;
        break;
      }
    }
  }

  //moet nog op een stack voor unDoeZet
  return geldig;
}  // doeZet

//*************************************************************************

bool TegelSpel::unDoeZet () { //ibraheem 
  // TODO: implementeer deze memberfunctie

  return true;

}  // unDoeZet

//*************************************************************************

int TegelSpel::besteScore (pair<int,char> &besteZet,
                             long long &aantalStanden) { //ibraheem
  // TODO: implementeer deze memberfunctie

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

pair<int,char> TegelSpel::bepaalGoedeZet (int nrSimulaties) { //joelle
    pair<int,char> goedeZet;
  

  return goedeZet;

}  // bepaalGoedeZet

//*************************************************************************

int TegelSpel::bepaalGoedeScore () { //ibraheem
  // TODO: implementeer deze memberfunctie

  return 0;

}  // bepaalGoedeScore

//*************************************************************************

void TegelSpel::doeExperiment () { //ibraheem
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

#include "tegelspel.h"
#include "standaard.h"
#include <fstream>
#include <iostream>
#include <set>

//*************************************************************************

TegelSpel::TegelSpel () {}

//*************************************************************************

int TegelSpel::getSchalen () {
  return M;
}

//*************************************************************************

string TegelSpel::getPot () {
  return pot;
}

//*************************************************************************

vector< pair <int,int> > TegelSpel::getInhoudSchalen () {
  return schalen;
}

//*************************************************************************

vector<pair<int, int>> TegelSpel::getInhoudRijen (int speler) {
  vector<pair<int, int>> empty;
  
  if (speler == 1) {
    return speler1;
  }
  if (speler == 2) {
    return speler2;
  }
  
  return empty;
}

//*************************************************************************

bool TegelSpel::leesInSpel (const char* invoernaam) {
  ifstream invoer;
  string regel;
  int links, rechts;
  vector<pair<int, int>> *speler;

  if (!checkFormat(invoernaam)) { //Checkt de format van het bestand
    return false;
  }
  
  invoer.open(invoernaam);
  getline(invoer, regel);
  pot = regel; //Leest de pot in

  invoer >> M >> N >> K >> L; //Leest de data van het spel in

  for (int i = 0; i < M; i++) { //Vult de schalen met de inhoud van de pot
    schalen.push_back(make_pair(0, 0));
    vulAan(i); 
  }

  speler = &speler1;
  for (int i = 0; i < 2; i++){
    for (int j = 0; j < K; j++) { //Leest de velden van speler 1 in
      invoer >> links >> rechts;
      (*speler).push_back(make_pair(links, rechts));
    }
    speler = &speler2;
  }

  invoer >> beurt; //Leest welke speler aan de beurt is in
  beurt++; //Corrigeert wie aan de beurt is

  invoer.close();
  return true;
}

//*************************************************************************

bool TegelSpel::eindstand () {
  if (alleZetten().empty()) {
    return true;
  }

  return false;
}

//*************************************************************************

void TegelSpel::drukAf () {
  cout << endl << string(23, '=') << endl;
  cout << "Pot: " << pot << endl;
  int i = 0;
  cout << "Schalen:" << endl;
  for (pair<int, int> schaal : schalen) {
    cout <<i++ << ": " << string(schaal.first, 'g') 
         << string(schaal.second, 'b') << "  ";
  }

  cout << "\n\n" << "   Speler 1    Speler 2" << endl
                 << "   --------    --------" << endl;
  for (int j = 0; j < K; j++) {
    cout << j << "| " 
         << string(speler1[j].first, 'g') 
         << string(speler1[j].second, 'b')
         << string(L - speler1[j].first - speler1[j].second, '#')
         << string(MaxPerRij - L + 6, ' ');
    cout << string(speler2[j].first, 'g') 
         << string(speler2[j].second, 'b') 
         << string(L - speler2[j].first - speler2[j].second, '#') << endl;
  }

  cout << endl << "Aan de beurt: Speler " << beurt << endl;
  cout << string(23, '=') << endl;
}

//*************************************************************************

vector< pair<int,char> > TegelSpel::bepaalVerschillendeZetten () {
  vector<pair<int, char>> zetten, mogelijkeZetten = alleZetten();
  vector<pair<int, char>> tegelsZetten;

  for (pair<int, char>& zet : mogelijkeZetten) {
    int tegels = 0;
    
    if (zet.second == 'g') {
      tegels = schalen[zet.first].first;
    } else if (zet.second == 'b') {
      tegels = schalen[zet.first].second;
    }
    
    tegelsZetten.push_back(make_pair(tegels, zet.second));
  }

  for (int i = 0; i < int(mogelijkeZetten.size()); i++) {
    bool identiek = false;

    for (int j = 0; j < i; j++) {
      if (tegelsZetten[i].first == tegelsZetten[j].first && 
          tegelsZetten[i].second == tegelsZetten[j].second) {
        identiek = true;
        break;
      }
    }

    if (!identiek) {
      zetten.push_back(mogelijkeZetten[i]);
    }
  }

  return zetten;
}
//*************************************************************************

bool TegelSpel::doeZet (int schaal, char kleur) { //6 lines te lang
  bool geldig = false;
  vector<pair<int, int>>* speler;

  for (pair<int, char>& mogelijk : alleZetten()) {
    geldig = false;
    if (make_pair(schaal, kleur) == mogelijk) {
      geldig = true;
      break;
    }
  }
  
  if (!geldig) {
    return false;
  }

  if (beurt == 1) {
    speler = &speler1;
  }
  else {
    speler = &speler2;
  }

  int i = 0;
  for (pair<int, int>& rij : *speler) { //probeer door schalen ints te swappen
    if (kleur == 'g' && schalen[schaal].first <= L - rij.first && rij.second == 0) {
      geschiedenis.push_back({schalen[schaal], schaal, pot, rij, i});
      rij.first += schalen[schaal].first;
      schalen[schaal].first = 0;
      break;
    } else if (kleur == 'b' && schalen[schaal].second <= L - rij.second && rij.first == 0) {
      geschiedenis.push_back({schalen[schaal], schaal, pot, rij, i});
      rij.second += schalen[schaal].second;
      schalen[schaal].second = 0;
      break;
    }
    i++;
  }
  vulAan(schaal);
  beurt = toggleBeurt();

  return true;
}

//*************************************************************************

bool TegelSpel::unDoeZet () {
  if (!geschiedenis.empty()) {
    vector<pair<int, int>>* speler;    

    beurt = toggleBeurt();

    if (beurt == 1) {
      speler = &speler1;
    }
    else {
      speler = &speler2;
    }

    (*speler)[geschiedenis.back().rij] = geschiedenis.back().rijOud;
    schalen[geschiedenis.back().schaal] = geschiedenis.back().schaalOud;
    pot = geschiedenis.back().potOud;

    geschiedenis.pop_back();

    return true;
  } else {
    return false;
  }
}

//*************************************************************************

int TegelSpel::besteScore (pair<int,char> &besteZet, long long &aantalStanden) {
  aantalStanden = 0;
  besteZet = make_pair(-1, ' ');
  
  return berekenBesteScore(besteZet, aantalStanden);
}

//*************************************************************************

pair<int,char> TegelSpel::bepaalGoedeZet (int nrSimulaties) {
  pair<int,char> goedeZet;
  




  return goedeZet;
}

//*************************************************************************

int TegelSpel::bepaalGoedeScore () {
  vector<pair<int, int>> *goedeSpeler, *besteSpeler;

  if (beurt == 1) {
    goedeSpeler = &speler1;
    besteSpeler = &speler2;
  } else if (beurt == 2) {
    goedeSpeler = &speler2;
    besteSpeler = &speler1;
  }

  return 0;
}

//*************************************************************************

void TegelSpel::doeExperiment () {
  while(!eindstand()) {
    pair<int, char> goedeZet = bepaalGoedeZet(NrSimulaties);
    doeZet(goedeZet.first, goedeZet.second);
  }

  while(!geschiedenis.empty()) {
    pair<int,char> besteZet;
    long long aantalStanden;

    unDoeZet();
    besteScore(besteZet, aantalStanden);
  }
}

//*************************************************************************

bool TegelSpel::checkFormat(const char* invoernaam) { //Checkt de format van een bestand //te lang
  ifstream invoer;
  string regel;
  int getal, links, rechts;
  int parameters[4];

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

  invoer >> parameters[0] >> parameters[1] >> parameters[2] >> parameters[3];
  for (int i = 0; i < 4; i++) { //Checkt of speldata de max. waarden overschreidt
    if (parameters[i] < 1 || parameters[i] > maxPars[i]) {
      return false;
    }
  }

  for (int i = 0; i < parameters[2] * 2; i++) { //Checkt of data van de spelers klopt
    invoer >> links >> rechts;
    if ((links != 0 && rechts != 0) || (links < 0 || links > parameters[3]) || 
        (rechts < 0 || rechts > parameters[3])) {
      return false;
    }
  }
  
  invoer >> getal;
  if (getal != 0 && getal != 1) {
    return false;
  }

  invoer.close();
  return true;
}

pair<int, int > TegelSpel::countTegels(string Tegels) {
  int g = 0, b = 0;
  
  for (char& tegel : Tegels) {
    if (tegel == 'g') {
        g++;
    } else if (tegel == 'b') {
        b++;
    }
  }

  return make_pair(g, b);
}
 
void TegelSpel::vulAan(int schaal) {
  int vrij = min(N - schalen[schaal].first - schalen[schaal].second, int(pot.size()));
  pair<int, int> aanvulling = countTegels(pot.substr(0, vrij));
  
  schalen[schaal].first += aanvulling.first;
  schalen[schaal].second += aanvulling.second;

  pot.erase(0, vrij);
}

vector<pair<int, char>> TegelSpel::alleZetten() {
  vector<pair<int, char>> zetten;
  vector<pair<int, int>> speler = getInhoudRijen(beurt);
  int gMax = 0, bMax = 0;

  for (pair<int, int>& rij : speler) {
    int gVrij = 0, bVrij = 0;
    
    if (rij.second == 0) {
      gVrij = L - rij.first;
    }
    if (rij.first == 0) {
      bVrij = L - rij.second;
    }
    
    if (gVrij > gMax) {
      gMax = gVrij;
    }
    if (bVrij > bMax) {
      bMax = bVrij;
    }
  }

  for (int i = 0; i < M; i++) {
    if (schalen[i].first <= gMax && schalen[i].first > 0) {
      zetten.push_back(make_pair(i, 'g'));
    }
    if (schalen[i].second <= bMax && schalen[i].second > 0) {
      zetten.push_back(make_pair(i, 'b'));
    }
  }

  return zetten;
}

int TegelSpel::toggleBeurt() {
  if (beurt == 1) {
    return 2;
  } 
  if (beurt == 2) {
    return 1;
  }
  return 0;
}

int TegelSpel::berekenBesteScore(pair<int,char> &besteZet, long long &aantalStanden) {
  int score = 0;
  vector<pair<int, char>> mogelijkeZetten = alleZetten();
  vector<int> scores;

  if (eindstand()) {
    aantalStanden++;

    for (pair<int, int>& rij : getInhoudRijen(beurt)) {
      if (rij.first == L || rij.second == L) {
        score++;
      }
    }
    for (pair<int, int>& rij : getInhoudRijen(toggleBeurt())) {
      if (rij.first == L || rij.second == L) {
        score--;
      }
    }
  } else {
    for (pair<int, char>& zet : mogelijkeZetten) {
      doeZet(zet.first, zet.second);
      scores.push_back(-1 * berekenBesteScore(besteZet, aantalStanden));
      unDoeZet();
    }

    score = scores[0];
    besteZet = mogelijkeZetten[0];
    for (int i = 1; i < int(scores.size()); i++) {
      if (scores[i] > score) {
        score = scores[i];
        besteZet = mogelijkeZetten[i];
      }
    }
  }

  return score;
}

//Check alle functie lengtes
//Comments
//Test wanneer pot klein wordt

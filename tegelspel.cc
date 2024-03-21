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
  beurt = toggleBeurt(beurt);

  return true;
}

//*************************************************************************

bool TegelSpel::unDoeZet () {
  if (!geschiedenis.empty()) {
    vector<pair<int, int>>* speler;    

    beurt = toggleBeurt(beurt);

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
  pair<int,char> goedeZet = make_pair(-1, ' ');
  vector<pair<int, char>> mogelijkeZetten = alleZetten();
  vector<double> gemScores;
  int goedeSpeler = beurt;
  double highscore = MaxRijen * -1;

  for (pair<int, char>& zet : mogelijkeZetten) {
    int score = 0;
    doeZet(zet.first, zet.second);

    for (int i = 0; i < nrSimulaties; i++) {
      int nSimZetten = 0;

      while (!eindstand()) {
        vector<pair<int, char>> simZetten = alleZetten();
        pair<int, char> randomZet = simZetten[randomGetal(0, simZetten.size() - 1)];
        doeZet(randomZet.first, randomZet.second);
        nSimZetten++;
      }

      score += getScore(goedeSpeler);
      for (int i = 0; i < nSimZetten; i++) {
        unDoeZet();
      }
    }
    unDoeZet();
    gemScores.push_back(double(score) / nrSimulaties);
  }

  
  for (int i = 0; i < int(gemScores.size()); i++) {
    if (gemScores[i] > highscore) {
      highscore = gemScores[i];
      goedeZet = mogelijkeZetten[i];
    }
  }

  return goedeZet;
}

//*************************************************************************

int TegelSpel::bepaalGoedeScore () {
  int nZetten = 0;
  int goedeSpelerBeurt = beurt;
  int score;
  
  while(!eindstand()) {
    if (beurt == goedeSpelerBeurt) {
      pair<int, char> zet = bepaalGoedeZet(NrSimulaties);
      
      doeZet(zet.first, zet.second);
    } else {
      pair<int, char> zet;
      long long aantalStanden;
      
      besteScore(zet, aantalStanden);
      doeZet(zet.first, zet.second);
    }
    nZetten++;
  }

  score = getScore(goedeSpelerBeurt);

  for (int i = 0; i < int(nZetten); i++) {
    unDoeZet();
  }

  return score;
}

//*************************************************************************

void TegelSpel::doeExperiment () {
  clock_t t1, t2;
  int undone = 0;
  
  while(!eindstand()) {
    pair<int, char> goedeZet = bepaalGoedeZet(NrSimulaties);
    doeZet(goedeZet.first, goedeZet.second);
  }

  while(!geschiedenis.empty()) {
    pair<int,char> besteZet;
    long long aantalStanden;

    unDoeZet();
    undone++;

    t1 = clock ();
    besteScore(besteZet, aantalStanden);
    t2 = clock ();

    cout << undone << " undo('s): " << aantalStanden << " Stand(en) in "
         <<  (((double)(t2-t1))/CLOCKS_PER_SEC) << " seconden." << endl;
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

int TegelSpel::toggleBeurt(int curBeurt) {
  if (curBeurt == 1) {
    return 2;
  } 
  if (curBeurt == 2) {
    return 1;
  }
  return 0;
}

int TegelSpel::berekenBesteScore(pair<int,char> &besteZet, long long &aantalStanden) {
  int score = MaxRijen * -1;
  vector<pair<int, char>> mogelijkeZetten = alleZetten();
  vector<int> scores;

  if (eindstand()) {
    aantalStanden++;

    score = getScore(beurt);
  } else {
    for (pair<int, char>& zet : mogelijkeZetten) {
      doeZet(zet.first, zet.second);
      scores.push_back(-1 * berekenBesteScore(besteZet, aantalStanden));
      unDoeZet();
    }

    for (int i = 0; i < int(scores.size()); i++) {
      if (scores[i] > score) {
        score = scores[i];
        besteZet = mogelijkeZetten[i];
      }
    }
  }

  return score;
}

vector<pair<int, int>>* TegelSpel::getSpeler(int speler) {
  if (speler == 1) {
    return &speler1;
  }
  if (speler == 2) {
    return &speler2;
  }

  return nullptr;
}

int TegelSpel::getScore(int speler) {
  int score = 0;
  
  for (pair<int, int>& rij : getInhoudRijen(speler)) {
    if (rij.first == L || rij.second == L) {
      score++;
    }
  }
  for (pair<int, int>& rij : getInhoudRijen(toggleBeurt(speler))) {
    if (rij.first == L || rij.second == L) {
      score--;
    }
  }

  return score;
}

//Check alle functie lengtes
//Comments
//Test wanneer pot klein wordt

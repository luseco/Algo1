#include "tegelspel.h"
#include "standaard.h"
#include <fstream>
#include <iostream>
#include <set>

//*************************************************************************

//De constructor
TegelSpel::TegelSpel () {}

//*************************************************************************

//Returnt aantal schalen
int TegelSpel::getSchalen () {
  return M;
}

//*************************************************************************

//Returnt de pot
string TegelSpel::getPot () {
  return pot;
}

//*************************************************************************

//Returnt de inhoud van de schalen
vector< pair <int,int> > TegelSpel::getInhoudSchalen () {
  return schalen;
}

//*************************************************************************

//Returnt de inhoud van de borden van de spelers
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

//Leest het bestand in en vult membervariabelen
bool TegelSpel::leesInSpel (const char* invoernaam) {
  ifstream invoer;
  string regel;
  int links, rechts;
  vector<pair<int, int>> *speler;

  //Checkt de format van het bestand
  if (!checkFormat(invoernaam)) { 
    return false;
  }
  
  invoer.open(invoernaam);
  //Leest de pot in
  getline(invoer, regel);
  pot = regel; 

  //Leest de data van het spel in
  invoer >> M >> N >> K >> L; 

  //Vult de schalen met de inhoud van de pot
  for (int i = 0; i < M; i++) { 
    schalen.push_back(make_pair(0, 0));
    vulAan(i); 
  }

  //Leest de velden van de spelers in
  speler = &speler1;
  for (int i = 0; i < 2; i++){
    for (int j = 0; j < K; j++) { 
      invoer >> links >> rechts;
      (*speler).push_back(make_pair(links, rechts));
    }
    speler = &speler2;
  }

  //Leest welke speler aan de beurt is in
  invoer >> beurt; 
  //Corrigeert wie aan de beurt is
  beurt++; 

  invoer.close();
  return true;
}

//*************************************************************************

//Checkt voor eindstand
bool TegelSpel::eindstand () {
  //Als er geen legale zetten zijn, is het automatisch een eindstand
  if (alleZetten().empty()) {
    return true;
  }

  return false;
}

//*************************************************************************

//Drukt de borden, schaal en pot af
void TegelSpel::drukAf () {
  cout << endl << string(23, '=') << endl;
  //Print de pot
  cout << "Pot: " << pot << endl;
  int i = 0;
  cout << "Schalen:" << endl;
  for (pair<int, int> schaal : schalen) {
    //Print de schalen
    cout <<i++ << ": " << string(schaal.first, 'g') 
         << string(schaal.second, 'b') << "  ";
  }

  //print de borden van de spelers uit
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
  //Print wie er aan de beurt is uit
  cout << endl << "Aan de beurt: Speler " << beurt << endl;
  cout << string(23, '=') << endl;
}

//*************************************************************************

//Bepaalt welke zetten uniek zijn
vector< pair<int,char> > TegelSpel::bepaalVerschillendeZetten () {
  vector<pair<int, char>> zetten, mogelijkeZetten = alleZetten();
  vector<pair<int, char>> tegelsZetten;

  //Vertaalt de zetten van vorm (schaal, kleur) 
  //naar (hoeveelheid tegels in zet, kleur)
  for (pair<int, char>& zet : mogelijkeZetten) {
    int tegels = 0;
    
    if (zet.second == 'g') {
      tegels = schalen[zet.first].first;
    } else if (zet.second == 'b') {
      tegels = schalen[zet.first].second;
    }
    
    tegelsZetten.push_back(make_pair(tegels, zet.second));
  }

  //Zoekt voor identieke zetten
  for (int i = 0; i < int(mogelijkeZetten.size()); i++) {
    bool identiek = false;

    for (int j = 0; j < i; j++) {
      if (tegelsZetten[i].first == tegelsZetten[j].first && 
          tegelsZetten[i].second == tegelsZetten[j].second) {
        identiek = true;
        break;
      }
    }

    //Stuurt alleen unieke zetten door in de vorm (schaal, kleur)
    if (!identiek) {
      zetten.push_back(mogelijkeZetten[i]);
    }
  }

  return zetten;
}
//*************************************************************************

//Zet een zet
bool TegelSpel::doeZet (int schaal, char kleur) {
  bool geldig = false;
  vector<pair<int, int>>* speler;

  //Checkt of zet wel geldig is
  for (pair<int, char>& mogelijk : alleZetten()) {
    geldig = false;
    if (make_pair(schaal, kleur) == mogelijk) {
      geldig = true;
      break;
    }
  }
  
  //Stopt als het ongeldig is
  if (!geldig) {
    return false;
  }

  speler = getSpeler(beurt);

  //Stopt de zet in geschiedenis, voegt tegels toe aan bord,
  //haalt tegels weg uit schaal en hervult de schaal
  int i = 0;
  for (pair<int, int>& rij : *speler) {
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
  //Verandert wie aan beurt is
  beurt = toggleBeurt(beurt);

  return true;
}

//*************************************************************************

//Zet een zet terug
bool TegelSpel::unDoeZet () {
  if (!geschiedenis.empty()) {
    vector<pair<int, int>>* speler;    

    //verandert wie aan beurt is
    beurt = toggleBeurt(beurt);

    speler = getSpeler(beurt);

    //Zet alle gegevens terug naar wat het voor de zet was
    (*speler)[geschiedenis.back().rij] = geschiedenis.back().rijOud;
    schalen[geschiedenis.back().schaal] = geschiedenis.back().schaalOud;
    pot = geschiedenis.back().potOud;

    //Haalt zet uit geschiedenis
    geschiedenis.pop_back();

    return true;
  } else {
    return false;
  }
}

//*************************************************************************

//Algoritme om de beste score te vinden door te brute forcen
//Dit wordt gebruikt als wrapper-functie
int TegelSpel::besteScore (pair<int,char> &besteZet, long long &aantalStanden) {
  aantalStanden = 0;
  //Default zet
  besteZet = make_pair(-1, ' ');
  
  //De functie waar de berekeningen gedaan worden
  return berekenBesteScore(besteZet, aantalStanden);
}

//*************************************************************************

//Algoritme die de Monte Carlo methode gebruikt om de beste zet te vinden
pair<int,char> TegelSpel::bepaalGoedeZet (int nrSimulaties) {
  //Default zet
  pair<int,char> goedeZet = make_pair(-1, ' ');
  vector<pair<int, char>> mogelijkeZetten = alleZetten();
  //Vector van gemiddelde scores
  vector<double> gemScores;
  int goedeSpeler = beurt;
  //Beginwaarde is de laagste mogelijke waarde voor de score
  double highscore = MaxRijen * -1;

  //Bepaalt voor elke zet de gemiddelde score
  for (pair<int, char>& zet : mogelijkeZetten) {
    int score = 0;
    doeZet(zet.first, zet.second);

    //Runt nrSimulaties aantal simulaties 
    for (int i = 0; i < nrSimulaties; i++) {
      int nSimZetten = 0;

      //Doet random zetten
      while (!eindstand()) {
        vector<pair<int, char>> simZetten = alleZetten();
        pair<int, char> randomZet = simZetten[randomGetal(0, simZetten.size() - 1)];
        doeZet(randomZet.first, randomZet.second);
        nSimZetten++;
      }

      score += getScore(goedeSpeler);
      //Undoet alle zetten naar originele staat
      for (int i = 0; i < nSimZetten; i++) {
        unDoeZet();
      }
    }
    unDoeZet();
    gemScores.push_back(double(score) / nrSimulaties);
  }

  //Vindt goede zet door gemScores te vergelijken
  //De twee vectoren corrileren qua index
  for (int i = 0; i < int(gemScores.size()); i++) {
    if (gemScores[i] > highscore) {
      highscore = gemScores[i];
      goedeZet = mogelijkeZetten[i];
    }
  }

  return goedeZet;
}

//*************************************************************************

//Vergelijkt goedeZet en besteZet door ze tegen elkaar te laten spelen
int TegelSpel::bepaalGoedeScore () {
  int nZetten = 0;
  int goedeSpelerBeurt = beurt;
  int score;
  
  while(!eindstand()) {
    //Doet goedeZet voor de speler wiens beurt het was 
    //toen de functie begon
    if (beurt == goedeSpelerBeurt) {
      pair<int, char> zet = bepaalGoedeZet(NrSimulaties);
      
      doeZet(zet.first, zet.second);
      
      //Doet besteZet voor de andere speler
    } else {
      pair<int, char> zet;
      long long aantalStanden;
      
      besteScore(zet, aantalStanden);
      doeZet(zet.first, zet.second);
    }
    nZetten++;
  }

  //Eindstand
  score = getScore(goedeSpelerBeurt);

  //Undoet alle zetten terug naar originele staat
  for (int i = 0; i < int(nZetten); i++) {
    unDoeZet();
  }

  return score;
}

//*************************************************************************

//Experiment om besteZet te benchmarken
void TegelSpel::doeExperiment () {
  //Om tijd te meten
  clock_t t1, t2;
  int undone = 0;
  
  //Gaat naar een eindstand
  while(!eindstand()) {
    pair<int, char> goedeZet = bepaalGoedeZet(NrSimulaties);
    doeZet(goedeZet.first, goedeZet.second);
  }

  while(!geschiedenis.empty()) {
    pair<int,char> besteZet;
    long long aantalStanden;

    unDoeZet();

    t1 = clock ();
    besteScore(besteZet, aantalStanden);
    t2 = clock ();

    cout << undone++ << " undo('s): " << aantalStanden << " Stand(en) in "
         <<  (((double)(t2-t1))/CLOCKS_PER_SEC) << " seconden." << endl;
  }
}

//*************************************************************************

//Checkt de format van een bestand //te lang
bool TegelSpel::checkFormat(const char* invoernaam) { 
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

//Comments afmaken
//Namen en studentennummers bovenaan .cc en .h
//spel2.txt maken 1 miljard
// Ibraheem Ahmed (s4147936) & Joelle Tiao(s3939855)
// 21/03/2024

#ifndef TegelSpelHVar  // voorkom dat dit bestand meerdere keren
#define TegelSpelHVar  // ge-include wordt

#include <vector>
#include <string>
#include "constantes.h"
using namespace std;

class TegelSpel
{ public:
    TegelSpel ();
    int getSchalen ();
    string getPot ();
    vector< pair <int,int> > getInhoudSchalen ();
    vector< pair <int,int> > getInhoudRijen (int speler);
    bool leesInSpel (const char* invoernaam);
    bool eindstand ();
    void drukAf ();
    vector< pair<int,char> > bepaalVerschillendeZetten ();
    bool doeZet (int schaal, char kleur);
    bool unDoeZet ();
    int besteScore (pair<int,char> &besteZet, long long &aantalStanden);
    pair<int,char> bepaalGoedeZet (int nrSimulaties);
    int bepaalGoedeScore ();
    void doeExperiment ();

  private:
//*************************************************************************
    //Eigen membervariabelen

    //De pot
    string pot;
    //Speldata: n Schalen, n per Schaal, n rijen, n per rij
    int M, N, K, L; 
    //Welke speler aan de beurt is; 1 OF 2
    int beurt;

    //Array van Max. waarden
    const int maxPars[4] = {MaxSchalen, MaxPerSchaal, MaxRijen, MaxPerRij}; 

    //De borden van de spelers; pair<n gele tegels, n blauwe tegels>
    vector<pair<int, int>> speler1, speler2;
    //Vector van de schalen; pair<n gele tegels, n blauwe tegels>
    vector<pair<int, int>> schalen; 
    
    //Struct voor alle gedane zetten
    struct zet {
      pair<int, int> schaalOud;
      int schaal;
      string potOud;
      pair<int, int> rijOud;
      int rij;
    };
    //Vector van alle zetten die zijn gedaan
    vector<zet> geschiedenis; 

//*************************************************************************
    //Eigen memberfuncties
    
    //Checkt format van bestand, returnt true als format klopt
    bool checkFormat(const char* invoernaam);

    //Telt aantal tegels in string, 
    //returnt pair<n gele tegels, n blauwe tegels>
    pair<int, int> countTegels(string Tegels);

    //Returnt alle mogelijke legale zetten
    vector<pair<int, char>> alleZetten();

    //Vult schaal aan uit de pot
    void vulAan(int schaal);

    //Togglet wie er aan de beurt is, returnt 1 OF 2
    int toggleBeurt(int curBeurt);

    //Recursieve functie die beste score en zet berekent d.m.v. brute force
    int berekenBesteScore(pair<int,char> &besteZet, 
                          long long &aantalStanden);

    //Returnt pointer naar speler
    //Neemt 1 (-> speler1) OF 2 (-> speler2) als input
    vector<pair<int, int>>* getSpeler(int speler);

    //Berekent score van het bord, met als input welk perspectief
    int getScore(int speler);
};

#endif
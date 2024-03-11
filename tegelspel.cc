// Implementatie van klasse TegelSpel

#include "tegelspel.h"
#include "standaard.h"
#include <fstream>   // voor inlezen van spel
#include <iostream>

//*************************************************************************

TegelSpel::TegelSpel ()
{
  // TODO: implementeer zo nodig deze constructor

}  // default constructor

//*************************************************************************

int TegelSpel::getSchalen ()
{
  // TODO: implementeer deze memberfunctie
  return 0;

}  // getSchalen

//*************************************************************************

string TegelSpel::getPot ()
{ string retString;

  // TODO: implementeer deze memberfunctie
  return retString;

}  // getPot

//*************************************************************************

vector< pair <int,int> > TegelSpel::getInhoudSchalen ()
{ vector< pair <int,int> > inhoudSchalen;

  // TODO: implementeer deze memberfunctie

  return inhoudSchalen;

}  // getInhoudSchalen

//*************************************************************************

vector< pair <int,int> > TegelSpel::getInhoudRijen (int speler)
{ vector< pair <int,int> > inhoudRijen;

  // TODO: implementeer deze memberfunctie

  return inhoudRijen;

}  // getInhoudRijen

//*************************************************************************

bool TegelSpel::leesInSpel (const char* invoernaam)
{
  string regel;
  int M, N, K, L;
  int parameters[4];
  ifstream invoer;
  vector<pair<char, int>> speler1, speler2;

  invoer.open(invoernaam);

  if (!invoer) {
    return false;
  }
  getline(invoer, regel);

  for (char &c : regel) {
    if (c != 'g' && c != 'b') {
      return false;
    }
  }
  for (int i = 0; i < 4; i++) {
    invoer >> parameters[i];
  }
  M = parameters[0];
  N = parameters[1];
  K = parameters[2];
  L = parameters[3];

  getline(invoer, regel);
  for (int j = 0; j < 2; j++) {
    vector<pair<char, int>> *speler = &speler1;
    for (int i = 0; i < K; i++) {
      getline(invoer, regel);
      cout << regel;
      if (regel[0] != '0' && regel[2] != '0') {
        return false;
      }
      if (regel[0] == '0' && regel[2] == '0') {
        speler->push_back(make_pair(' ', 0));
      } else if (regel[0] >= '1' && regel[0] <= L) {
        speler->push_back(make_pair('g', regel[0]));
      } else if (regel[0] >= '1' && regel[0] <= L) {
        speler->push_back(make_pair('b', regel[2]));
      }
    }
    speler = &speler2;
  }

  for (pair<char, int> i : speler1) {
    cout << i.first << " " << i.second << endl;
  }
  cout << endl;
  for (pair<char, int> i : speler2) {
    cout << i.first << " " << i.second << endl;
  }

  invoer.close();
  return true;

}  // leesInSpel

//*************************************************************************

bool TegelSpel::eindstand ()
{
  // TODO: implementeer deze memberfunctie

  return false;

} // eindstand

//*************************************************************************

void TegelSpel::drukAf ()
{
  // TODO: implementeer deze memberfunctie

}  // drukAf

//*************************************************************************

vector< pair<int,char> > TegelSpel::bepaalVerschillendeZetten ()
{ vector< pair<int,char> > zetten;

  // TODO: implementeer deze memberfunctie

  return zetten;

}  // bepaalVerschillendeZetten

//*************************************************************************

bool TegelSpel::doeZet (int schaal, char kleur)
{
  // TODO: implementeer deze memberfunctie

  return true;

}  // doeZet

//*************************************************************************

bool TegelSpel::unDoeZet ()
{
  // TODO: implementeer deze memberfunctie

  return true;

}  // unDoeZet

//*************************************************************************

int TegelSpel::besteScore (pair<int,char> &besteZet,
                             long long &aantalStanden)
{
  // TODO: implementeer deze memberfunctie

  return 0;

}  // besteScore

//*************************************************************************

pair<int,char> TegelSpel::bepaalGoedeZet (int nrSimulaties)
{ pair<int,char> goedeZet;

  // TODO: implementeer deze memberfunctie

  return goedeZet;

}  // bepaalGoedeZet

//*************************************************************************

int TegelSpel::bepaalGoedeScore ()
{
  // TODO: implementeer deze memberfunctie

  return 0;

}  // bepaalGoedeScore

//*************************************************************************

void TegelSpel::doeExperiment ()
{
  // TODO: implementeer deze memberfunctie

}  // doeExperiment


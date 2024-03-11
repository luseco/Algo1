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

int TegelSpel::getSchalen () //joelle
{
  // TODO: implementeer deze memberfunctie
  return 0;

}  // getSchalen

//*************************************************************************

string TegelSpel::getPot () //joelle
{ string retString;

  // TODO: implementeer deze memberfunctie
  return retString;

}  // getPot

//*************************************************************************

vector< pair <int,int> > TegelSpel::getInhoudSchalen () //ibraheem
{ vector< pair <int,int> > inhoudSchalen;

  // TODO: implementeer deze memberfunctie

  return inhoudSchalen;

}  // getInhoudSchalen

//*************************************************************************

vector< pair <int,int> > TegelSpel::getInhoudRijen (int speler) //ibraheem
{ vector< pair <int,int> > inhoudRijen;

  // TODO: implementeer deze memberfunctie

  return inhoudRijen;

}  // getInhoudRijen

//*************************************************************************

bool TegelSpel::leesInSpel (const char* invoernaam)
{ ifstream invoer;
  string regel;

  invoer.open(invoernaam);
  if (!invoer) {return false;}
  getline(invoer, regel);

  for (char &c : regel) {
    if (c != 'g' && c != 'b') {
      return false;
    }
  }
  pot = regel;

  for (int i = 0; i < 4; i++) {
    invoer >> *pars[i];
    if(*pars[i] < 1 || *pars[i] > maxPars[i]) {
      return false;
    }
  }

  getline(invoer, regel);
  for (int j = 0; j < 2; j++) {
      vector<pair<char, int>> *speler;
      if (j == 0) {
          speler = &speler1;
      } else {
          speler = &speler2;
      }

      for (int i = 0; i < K; i++) {
          getline(invoer, regel);
          if (regel[0] != '0' && regel[2] != '0') {
              return false;
          } if (regel[0] == '0' && regel[2] == '0') {
              speler->push_back(make_pair(' ', 0));
          } else if (regel[0] - '0' >= 1 && regel[0] - '0' <= L) {
              speler->push_back(make_pair('g', regel[0] - '0'));
          } else if (regel[2] - '0' >= 1 && regel[2] - '0' <= L) {
              speler->push_back(make_pair('b', regel[2] - '0'));
          }
      }
  }
  invoer >> beurt;

  invoer.close();
  return true;
}  // leesInSpel

//*************************************************************************

bool TegelSpel::eindstand () //joelle
{
  // TODO: implementeer deze memberfunctie

  return false;

} // eindstand

//*************************************************************************

void TegelSpel::drukAf () //ibraheem
{
  // TODO: implementeer deze memberfunctie

}  // drukAf

//*************************************************************************

vector< pair<int,char> > TegelSpel::bepaalVerschillendeZetten () //joelle
{ vector< pair<int,char> > zetten;

  // TODO: implementeer deze memberfunctie

  return zetten;

}  // bepaalVerschillendeZetten

//*************************************************************************

bool TegelSpel::doeZet (int schaal, char kleur) //ibraheem
{
  // TODO: implementeer deze memberfunctie

  return true;

}  // doeZet

//*************************************************************************

bool TegelSpel::unDoeZet () //ibraheem 
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


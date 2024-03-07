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

  // TODO: implementeer deze memberfunctie

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


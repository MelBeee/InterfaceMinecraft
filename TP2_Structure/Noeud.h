// Déclaration d'un noeud. En l'occurence, le
// noeud ne contient qu'une string comme élément
// d'information
//
// par Pierre Prud'homme, octobre 2014
//-------------------------------------------------
#ifndef _NOEUD_H_
#define _NOEUD_H_
#include <string>
#include <vector>
using namespace std;


enum Section
{
   TerrasseNonFumeur, TerrasseFumeur, SalleManger
};

class ClientsEnAttente
{
   struct Client
   {
      string nomReservation;
      int nombreDePersonnes;
      vector<Section> sectionChoisis;
   };

   Client clientsTable; 
   ClientsEnAttente * pPrécédent_;  // Chaque noeud retient l'adresse de celui qui le précède
   ClientsEnAttente * pSuivant_;    // et de celui qui le suit

public:
   //--- Constructeurs
   ClientsEnAttente();
   ClientsEnAttente(string nom);

   void SetPrécédent(ClientsEnAttente * p);
   void SetSuivant(ClientsEnAttente *p);
   void SetClient(Client c);

   ClientsEnAttente * GetPrécédent() const;
   ClientsEnAttente * GetSuivant() const;
   Client GetClient(); 
};

#endif

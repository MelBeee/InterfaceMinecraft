#include "FonctionsGenerales.h"


int main()
{
   setlocale(LC_ALL, "");
   FileAttente laFile; 
   bool quitter = true;
   string nom;
   int nbre;
   int sections;

   while (quitter)
   {
      switch (MenuFaireChoix())
      {
      case 1:
         cout << " Ajout d'un client " << endl;
		 DemanderInfoClient(nom, nbre, sections);
		 laFile.Ajouter(nom, nbre, sections); 
         break;
      case 2:
         cout << " Assignation d'une table " << endl;
         AssignerTable();
         break;
      case 3:
         cout << " Retrait d'un client qui quitte " << endl;
         break;
      case 4:
         cout << " Affichage d'un client en attente " << endl;
         break;
      case 5:
         cout << " Affichage de la file d'attente " << endl;
         break;
      case 6:
         cout << " Quitter " << endl;
         quitter = QuitterLeProgramme();
         if (!quitter)
         {
            AffichageFinale();
         }
         break;
      }
   }
}


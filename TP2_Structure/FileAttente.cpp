////////////////////////////////////////////////////////////////////////////////
//								FileAttente.cpp													//
//				  Fait par Mélissa Boucher et Xavier Brosseau							//
//							Créé le 29 octobre 2014												//
//						Derniere modif 16 novembre 2014										//
//																										//
//			Définition de la classe FileAttente qui stock le 1er et dernier		//
//			clients en attente. Les méthodes utilisés sont fait pour modififer	//
//			la file et afficher la file.														//
////////////////////////////////////////////////////////////////////////////////
#include "FileAttente.h"

////////////////////////////////////////////////////////////////////////////////
//											SetDernier()							            //
////////////////////////////////////////////////////////////////////////////////
void FileAttente::SetDernier(ClientsEnAttente * p)
{
	pDernier_ = p;
}
////////////////////////////////////////////////////////////////////////////////
//											GetDernier()							            //
////////////////////////////////////////////////////////////////////////////////
ClientsEnAttente* FileAttente::GetDernier() const
{
	return pDernier_;
}
////////////////////////////////////////////////////////////////////////////////
//											SetNbGroupes()							            //
////////////////////////////////////////////////////////////////////////////////
void FileAttente::SetNbGroupes(int nb)
{
	nbGroupes_ = nb;
}
////////////////////////////////////////////////////////////////////////////////
//										SetNbPersonnes()							            //
////////////////////////////////////////////////////////////////////////////////
void FileAttente::SetNbPersonnes(int nb)
{
	nbPersonne_ = nb;
}
////////////////////////////////////////////////////////////////////////////////
//										SetNbGroupesTotal()						            //
////////////////////////////////////////////////////////////////////////////////
void FileAttente::SetNbGroupesTotal(int nb)
{
	nbGroupesTotal_ = nb;
}
////////////////////////////////////////////////////////////////////////////////
//										SetNbPersonnesTotal()					            //
////////////////////////////////////////////////////////////////////////////////
void FileAttente::SetNbPersonnesTotal(int nb)
{
	nbPersonnesTotal_ = nb;
}
////////////////////////////////////////////////////////////////////////////////
//											SetPremier()							            //
////////////////////////////////////////////////////////////////////////////////
void FileAttente::SetPremier(ClientsEnAttente * p)
{
	pPremier_ = p;
}
////////////////////////////////////////////////////////////////////////////////
//											GetPremier()							            //
////////////////////////////////////////////////////////////////////////////////
ClientsEnAttente* FileAttente::GetPremier() const
{
	return pPremier_;
}
////////////////////////////////////////////////////////////////////////////////
//											FileAttente()							            //
////////////////////////////////////////////////////////////////////////////////
FileAttente::FileAttente()
{
	SetNbGroupes(0);  // il n'y a pas d'éléments dans la liste
	SetNbPersonnes(0);
	SetNbGroupesTotal(0);
	SetNbPersonnesTotal(0);
	SetPremier(nullptr);     // on pointe sur rien
	SetDernier(nullptr);
}
////////////////////////////////////////////////////////////////////////////////
//										ObtenirNbGroupes()						            //
////////////////////////////////////////////////////////////////////////////////
int FileAttente::ObtenirNbGroupes() const
{
	return nbGroupes_;
}
////////////////////////////////////////////////////////////////////////////////
//										ObtenirNbPersonnes()						            //
////////////////////////////////////////////////////////////////////////////////
int FileAttente::ObtenirNbPersonnes() const
{
	return nbPersonne_;
}
////////////////////////////////////////////////////////////////////////////////
//									ObtenirNbPersonnesTotal()					            //
////////////////////////////////////////////////////////////////////////////////
int FileAttente::ObtenirNbPersonnesTotal() const
{
	return nbPersonnesTotal_;
}
////////////////////////////////////////////////////////////////////////////////
//											SetDernier()							            //
////////////////////////////////////////////////////////////////////////////////
int FileAttente::ObtenirNbGroupesTotal() const
{
	return nbGroupesTotal_;
}
////////////////////////////////////////////////////////////////////////////////
//												Afficher()							            //
////////////////////////////////////////////////////////////////////////////////
void FileAttente::Afficher(ostream & out) const
{
	ClientsEnAttente * pTemporaire = GetPremier();
	int indice = 1;

	if (pTemporaire == nullptr)
		throw exception(" La file d'attente est vide ");

	while (pTemporaire != 0)
	{
		cout << GetClient(indice) << endl;
		indice++;
		pTemporaire = pTemporaire->GetSuivant();
	}

}
////////////////////////////////////////////////////////////////////////////////
//												Ajouter()							            //
////////////////////////////////////////////////////////////////////////////////
void FileAttente::Ajouter(ClientsEnAttente::Client clientAMettreEnFile)
{
	ClientsEnAttente * pNouveau = new ClientsEnAttente(clientAMettreEnFile.nomReservation,
		clientAMettreEnFile.nombreDePersonnes,
		clientAMettreEnFile.sectionChoisis);

	if (EstVide())
	{
		SetPremier(pNouveau);
		SetDernier(pNouveau);  // ajouté quand on a un pointe
	}
	else
	{
		pNouveau->SetPrécédent(GetDernier());
		GetDernier()->SetSuivant(pNouveau);
		SetDernier(pNouveau);
	}

	SetNbGroupes(ObtenirNbGroupes() + 1);
	SetNbPersonnes(ObtenirNbPersonnes() + clientAMettreEnFile.nombreDePersonnes);
}
////////////////////////////////////////////////////////////////////////////////
//												Retirer()							            //
////////////////////////////////////////////////////////////////////////////////
bool FileAttente::Retirer(string nomClient, int nbPersonnes)
{
	ClientsEnAttente * pTemporaire = GetPremier();
	bool existe = false;

	if (pTemporaire == nullptr)
	{
		throw exception("La liste est vide");
	}
	if (VérifierSiPrésent(nomClient, nbPersonnes))
	{
		while (pTemporaire != nullptr && !existe)
		{
			if (pTemporaire != nullptr && EstLeMemeNom(pTemporaire, nomClient, nbPersonnes))
				existe = true;

			else
				pTemporaire = pTemporaire->GetSuivant();
		}
		if (existe)
		{
			if (pTemporaire->GetPrécédent() != nullptr) //si le pTempo n'est pas le 1er
			{
				if (pTemporaire->GetSuivant() != nullptr) //si le pTempo n'est pas le dernier
				{
					pTemporaire->GetSuivant()->SetPrécédent(pTemporaire->GetPrécédent());
					pTemporaire->GetPrécédent()->SetSuivant(pTemporaire->GetSuivant());
				}
				else //si le pTempo est le dernier
				{
					SetDernier(pTemporaire->GetPrécédent());
					pTemporaire->GetPrécédent()->SetSuivant(0);
				}
			}
			else //si le pTempo est le premier de la file	
			{
				if (pTemporaire->GetSuivant() != nullptr) // premier mais pas dernier
				{
					SetPremier(pTemporaire->GetSuivant());
					pTemporaire->GetSuivant()->SetPrécédent(nullptr);
				}
				else // si le premier et dernier
				{
					SetPremier(nullptr);
					SetDernier(nullptr);
				}
			}
			SetNbPersonnes(ObtenirNbPersonnes() - pTemporaire->GetNombrePersonne());
			SetNbGroupes(ObtenirNbGroupes() - 1);
			delete pTemporaire;
		}
	}
	return existe;
}
////////////////////////////////////////////////////////////////////////////////
//												GetClient()							            //
////////////////////////////////////////////////////////////////////////////////
string FileAttente::GetClient(int indice) const
{
	ClientsEnAttente * pBalayage = GetPremier();
	int compteur = 1;
	while (compteur != indice)
	{
		pBalayage = pBalayage->GetSuivant();
		compteur++;
	}

	string nom = " Nom de la réservation : " + pBalayage->GetNom();
	string nombre = " Nombre de personne : " + to_string(pBalayage->GetNombrePersonne());
	string section = " Sections possibles : |";
	for (unsigned int i = 0; i < pBalayage->GetClientSection().size(); i++)
	{
		section += AfficherSection(pBalayage->GetClientSection()[i]) + "|";
	}
	return (nom + "\n" + nombre + "\n" + section + "\n");
}
////////////////////////////////////////////////////////////////////////////////
//										AfficherSection()							            //
////////////////////////////////////////////////////////////////////////////////
string FileAttente::AfficherSection(int i) const
{
	string section;
	switch (i)
	{
	case TerrasseNonFumeur: section = "Terrasse NonFumeur"; break;
	case TerrasseFumeur: section = "Terrasse Fumeur"; break;
	case SalleManger: section = "Salle A Manger"; break;
	}
	return section;
}
////////////////////////////////////////////////////////////////////////////////
//												EstVide()							            //
////////////////////////////////////////////////////////////////////////////////
bool FileAttente::EstVide() const
{
	return GetPremier() == 0;
}
////////////////////////////////////////////////////////////////////////////////
//										VérifierSiPrésent()						            //
////////////////////////////////////////////////////////////////////////////////
bool FileAttente::VérifierSiPrésent(string nom, int nbPersonnes) const
{
	ClientsEnAttente * pBalayage = GetPremier();

	while (pBalayage != nullptr && !EstVide() && !EstLeMemeNom(pBalayage, nom, nbPersonnes))
	{
		pBalayage = pBalayage->GetSuivant();
	}

	return pBalayage != nullptr;
}
////////////////////////////////////////////////////////////////////////////////
//											EstLeMemeNom()							            //
////////////////////////////////////////////////////////////////////////////////
bool FileAttente::EstLeMemeNom(ClientsEnAttente * p, string nom, int nbPersonnes) const
{
	return (MettreEnMajuscules(p->GetNom()) == MettreEnMajuscules(nom) && p->GetNombrePersonne() == nbPersonnes);
}
////////////////////////////////////////////////////////////////////////////////
//									MettreEnMajuscules()							            //
////////////////////////////////////////////////////////////////////////////////
string FileAttente::MettreEnMajuscules(string nom) const
{
	for (unsigned int i = 0; i < nom.size(); ++i)
	{
		nom[i] = toupper(nom[i]);
	}
	return nom;
}
////////////////////////////////////////////////////////////////////////////////
//											Retirer()								            //
////////////////////////////////////////////////////////////////////////////////
ClientsEnAttente::Client FileAttente::Retirer(int nbPlacesDeLaTable, Section sectionDeLaTable)
{
	ClientsEnAttente * pTemporaire = GetPremier();
	ClientsEnAttente * meilleursChoix = nullptr;
	bool trouver = false;
	ClientsEnAttente::Client c;

	for (int i = nbPlacesDeLaTable; i > 0 && !trouver; i--)
	{
		pTemporaire = GetPremier();
		while (pTemporaire != nullptr && !trouver)
		{
			ReduireBoucle(pTemporaire, trouver, meilleursChoix, i, sectionDeLaTable);
			pTemporaire = pTemporaire->GetSuivant();
		}
	}

	if (!trouver)
		throw exception("Pas de groupe correspondant aux demandes");

	cout << " Bonne appetit " << meilleursChoix->GetNom() << endl;
	c.nombreDePersonnes = meilleursChoix->GetNombrePersonne();
	c.nomReservation = meilleursChoix->GetNom();
	c.sectionChoisis = meilleursChoix->GetClientSection();

	Retirer(meilleursChoix->GetNom(), meilleursChoix->GetNombrePersonne());

	SetNbGroupesTotal(ObtenirNbGroupesTotal() + 1);
	SetNbPersonnesTotal(ObtenirNbPersonnesTotal() + c.nombreDePersonnes);
	return c;
}
////////////////////////////////////////////////////////////////////////////////
//										ReduireBoucle()							            //
////////////////////////////////////////////////////////////////////////////////
void FileAttente::ReduireBoucle(ClientsEnAttente * & pTemporaire, bool & trouver, ClientsEnAttente * & meilleursChoix, int & i, Section & sectionDeLaTable)
{
	if (pTemporaire->GetNombrePersonne() == i)
	{
		for (unsigned int j = 0; j < pTemporaire->GetClientSection().size() && !trouver; j++)
		{
			trouver = (AfficherSection(pTemporaire->GetClientSection().at(j)) == AfficherSection(sectionDeLaTable));
			if (trouver)
				meilleursChoix = pTemporaire;
		}
	}
}

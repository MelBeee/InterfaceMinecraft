// Implantation d'une liste de noeuds
//
// par Pierre Prud'homme, octobre 2014
//-------------------------------------------------
#include "FileAttente.h"

void FileAttente::SetDernier(ClientsEnAttente * p)
{
	pDernier_ = p;
}

ClientsEnAttente* FileAttente::GetDernier() const
{
	return pDernier_;
}

void FileAttente::SetNbGroupes(int nb)
{
	nbGroupes_ = nb;
}

void FileAttente::SetNbPersonnes(int nb)
{
	nbPersonne_ = nb;
}

void FileAttente::SetPremier(ClientsEnAttente * p)
{
	pPremier_ = p;
}

ClientsEnAttente* FileAttente::GetPremier() const
{
	return pPremier_;
}

FileAttente::FileAttente()
{
	SetNbGroupes(0);  // il n'y a pas d'�l�ments dans la liste
	SetNbPersonnes(0);
	SetPremier(0);     // on pointe sur rien
	SetDernier(0);
}

FileAttente::~FileAttente()
{
	pPremier_ = 0;
	pDernier_ = 0;
	delete pPremier_;
	delete pDernier_;
}
// retourne le nombre d'�l�ments de la liste
int FileAttente::ObtenirNbGroupes() const
{
	return nbGroupes_;
}

int FileAttente::ObtenirNbPersonnes() const
{
	return nbPersonne_;
}

void FileAttente::Afficher(ostream & out) const
{
	ClientsEnAttente * pTemporaire = GetPremier();

	while (pTemporaire != 0) // pourquoi != 0 ? 
	{
		vector<Section> tempo = pTemporaire->GetClientSection();

		out << "R�servation : " << pTemporaire->GetNom() 
			<< "Nb de personnes : " << pTemporaire->GetNombrePersonne() 
			<< "Sections d�sir�es : ";
		for (int i = 0; i < tempo.size(); i++)
		{
			cout << tempo[i] << ", ";
		}
		cout << endl << endl; 
		pTemporaire = pTemporaire->GetSuivant();
	}
	out << "Il y a " << ObtenirNbGroupes() << " elements dans la liste" << endl
		<< "Il y a " << ObtenirNbPersonnes() << " en file " << endl; 
}
void FileAttente::Ajouter(Client clientAMettreEnFile)
{

	ClientsEnAttente * pNouveau = new ClientsEnAttente(clientAMettreEnFile.nomReservation,
													   clientAMettreEnFile.nombreDePersonnes, 
													   clientAMettreEnFile.sectionChoisis);

	if (EstVide())
	{
		SetPremier(pNouveau);
		SetDernier(pNouveau);  // ajout� quand on a un pointe
	}
	else
	{
		pNouveau->SetPr�c�dent(GetDernier());
		GetDernier()->SetSuivant(pNouveau);
		SetDernier(pNouveau);
	}
	SetNbGroupes(ObtenirNbGroupes() + 1);
	SetNbPersonnes(ObtenirNbPersonnes() + nbPersonne_);
}

Client Retirer(int nbPlacesDeLaTable, Section sectionDeLaTable)
{

}
bool FileAttente::Retirer(string nomClient, int nbPersonnes)
{
	bool existe = false; 

	if (V�rifierSiPr�sent(nomClient, nbPersonnes))
	{

		existe = true; 
	}

	return existe; 
}

string FileAttente::GetClient(int indice)
{

}

bool FileAttente::EstVide() const
{
	return GetPremier() == 0;
}

bool FileAttente::V�rifierSiPr�sent(string nom, int nbPersonnes) const
{
	ClientsEnAttente * pBalayage = GetPremier();

	while (pBalayage != nullptr && !EstLeMemeNom(pBalayage, nom, nbPersonnes))
	{
		pBalayage = pBalayage->GetSuivant();
	}

	return pBalayage != nullptr;
}

bool FileAttente::EstLeMemeNom(ClientsEnAttente * p, string nom, int nbPersonnes) const
{
	return (MettreEnMajuscules(p->GetNom()) == MettreEnMajuscules(nom) && p->GetNombrePersonne() == nbPersonnes);
}

string FileAttente::MettreEnMajuscules(string nom) const
{
	for (int i = 0; i < nom.size(); ++i)
	{
		nom[i] = toupper(nom[i]);
	}
	return nom;
}

int FileAttente::DonnerLeRang(string nom, int nbPersonnes) const
{
	ClientsEnAttente * pBalayage = GetPremier();
	//int rang = 1; 
	int rang = 0; 

	while (pBalayage != nullptr && !EstLeMemeNom(pBalayage, nom))
	{
		pBalayage = pBalayage->GetSuivant();
		rang++;
	}

	//if (pBalayage == nullptr)
	//{
	//	rang = 0;
	//}

	return rang;
}
void FileAttente::PasserDevantToutLeMonde()
{
	if (ObtenirNbGroupes() > 1)
	{
		ClientsEnAttente * pTricheur = GetDernier();
		// modifier la file pour 'enlever' le dernier
		SetDernier(GetDernier()->GetPr�c�dent());
		GetDernier()->SetSuivant(nullptr);

		GetPremier()->SetPr�c�dent(pTricheur);
		pTricheur->SetSuivant(GetPremier());
		pTricheur->SetPr�c�dent(nullptr);
		SetPremier(pTricheur);
	}
}
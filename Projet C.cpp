#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <string.h>
#include <stdio.h>
#define taille 100
int position = 0;
struct client{
	//nom, prenom, fonction, mdp...
	char nom[25];
	char prenom[25];
	int fonction; // 1 : etudiant ; 2 : cuisinier; 3 : administration;
	int mdp;
	int solde;
};

struct menus{
	//menus ou sandwichs, description, prix...
};
void affich_tab(struct client tab[], int position)
{
	for(int k=0; k<position; k++)
		printf("%s", tab[position].prenom);
	printf("");
}
void creation(struct client tab[], int position)//creation d'un nouveau compte
{
	char fonction[25];
	bool fonction_valide;
	fflush(stdin);
	fseek(stdin, 0, SEEK_END);
	printf("Entrez le nom : \n");//saisie des infos du compte
	fgets(tab[position].nom, 25, stdin);
	fflush(stdin);
	printf("Entrez le prenom : \n");
	fgets(tab[position].prenom, 25, stdin);
	fflush(stdin);
	printf("Entrer votre code secret : \n");
	scanf_s("%d", &tab[position].mdp);
	do {
		fflush(stdin);
		fseek(stdin, 0, SEEK_END);
		printf("Entrez la fonction (etudiant/cuisinier/administration) : ");
		fgets(fonction, 25, stdin);
		fonction_valide = strcmp(fonction, "etudiant\n") == 0 ||
			strcmp(fonction, "administration\n") == 0 ||
			strcmp(fonction, "cuisinier\n") == 0;

		if (!fonction_valide)
			printf("Entree invalide\n");
		
	} while (!fonction_valide);
	//attribution d'un nb a une fonction
		if (strcmp(fonction, "etudiant") == 0)
			tab[position].fonction = 1;
		else if (strcmp(fonction, "cuisinier") == 0)
			tab[position].fonction = 2;
		else if (strcmp(fonction, "administration") == 0)
			tab[position].fonction = 3;
}
int connexion(struct client tab[], int indice) //connexion
{
	char prenom[25], nom[25];
	int mdp, trouve = 0, i=0;
	fseek(stdin, 0, SEEK_END);
	printf("Prenom: ");
	fgets(prenom, 25, stdin);
	printf("\nNom :");
	fgets(nom, 25, stdin);
	printf("\nmot de passe : ");
	scanf_s("%d", &mdp);
	//recherche du compte correspondant dans le tab
	do {
		
		if (strcmp(prenom, tab[i].prenom) == 0)
		{
			if (strcmp(nom, tab[i].nom) == 0)
			{
				if (mdp == tab[i].mdp)
					trouve = 1;
			}
		}
		else {
			i++;
		}
		position = i;
	} while (trouve == 0 && i < indice);
		int num_fonction = tab[indice].fonction;
		return num_fonction;
}
void affich_menus()//affichage des menus rentr??s par le cuisinier 
{

}
void enregistrer(struct client tab[], int position)//enregistrement du tableau dans le fichier comptes.dat
{
	FILE *fichier;
	fichier = fopen("comptes.dat", "w");
	for (int i = 0; i < position; i++)
		fwrite(&tab[i], sizeof(struct client), 1, fichier);
	fclose(fichier);
}
int lire(struct client tab[])//lecture du fichier
{
	int i = 0;
	FILE *fichier = fopen("comptes.dat", "r");
	while (fread(&tab[i], sizeof(struct client), 1, fichier) && !feof(fichier))
			i++;
	return i;
}
int main()
{
	struct client tableau[taille];
	int replay = 0, choix, position = 0, fonction;
	position = lire(tableau);
	do {
		printf("-------------------\nCreer un compte...1\n");
		printf("Se connecter......2\n");
		printf("Plats proposes....3\n");
		printf("Statistiques......4\n-------------------");
		fflush(stdin);
		scanf_s("%d", &choix);
		switch (choix)
		{
		case 1: //creer un compte->ajout dans un struct
			creation(tableau, position);
			affich_tab(tableau, position);
			position++;
			break;
		case 2:	//connexion a un compte
			fonction = connexion(tableau, position);
			if (fonction == 1) //etudiant
			{
				printf("Ajouter de l'argent.......1\n");
				printf("Afficher menus............2");
				printf("");
				scanf_s("%d", &choix);
				switch (choix)
				{
				case 1 :
					printf("\nQuelle somme d'argent voulez-vous ajouter ?\n");				
					scanf_s("%d", &tableau[position].solde);
					printf("%d euros ajoute sur le compte de %s\n", tableau[position].solde, tableau[position].prenom);
					break;
				case 2 :
					
					break;
				case 3:
					printf("Fin du programme, enregistrement dans le fichier");
					enregistrer(tableau, position);
					break;
				}
			}
			else if (fonction == 2) //cuisinier
			{
				
			}
			else if (fonction == 3) //admin
			{

			}
			break;
		case 3:	//plats propos??s
			
			break;
		}
	
	}while (replay == 0); //boucle de rejouer
}

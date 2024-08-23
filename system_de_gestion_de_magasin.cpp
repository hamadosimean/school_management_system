#include<iostream>
#include<fstream>
#include<string.h>
#include<conio.h>
#include <ctime>

using namespace std;

ifstream fin;
ofstream fout;
fstream fio;
 
// Gestionnaire implementation
class Gestionnaire {
	public:
		void menuGest();
	    void ajouterCaissiere();
		void ajouterProduit();
		void visualiserCaissiere();
		void visualiserProduit();
		void connexion(); 
		void visualiserProduitDetails();
		void supprimerProduit();
		void ajouterQuantite();
}g;



// personne implementation

class Personne{
	public:
		char nom[40];
		char prenom[40];
		char addresse[40];
		char contact[40];
}ps;
//


//Caisiere implementation
class Caissiere: public Personne{
	public:
		void menuCais();
		void connexion();
		void vendreProduit();
}c;

// Produit class
class Produit{
	public:
		char nom[100];
		double prix;
		int quantite;
		char desc[200];
}pd;
class Client: public Personne{
}cl;



//Temps et date
string temps(){
	time_t temp_ac;
	temp_ac = time(0);
    char * dt = ctime(&temp_ac);
	return dt;
}

// Menu du gestionnaire

void Gestionnaire::menuGest(){
			char res;
			do{
				cout<<"----------------------------"<<endl;
				cout<<"| (1)   Ajouter  Caissiere |"<<endl;
				cout<<"| (2)   Ajouter produit    |"<<endl;
				cout<<"| (3)   Afficher produits  |"<<endl;
				cout<<"| (4)   Chercher produit   |"<<endl;
				cout<<"| (5)   Afficher caissieres|"<<endl;
				cout<<"| (6)   Supprimer produit  |"<<endl;
				cout<<"| (7)   Ajouter quantite   |"<<endl;
				cout<<"| (0)   Quitter            |"<<endl;
				cout<<"----------------------------"<<endl;
				cout<<"Choississez une option:";
				cin>>res;
				switch (res){
					case '1': ajouterCaissiere(); break;
					case '2': ajouterProduit(); break;
					case '3': visualiserProduit(); break;
					case '4': visualiserProduitDetails();break;
					case '5': visualiserCaissiere(); break;
					case '6': supprimerProduit(); break;
					case '7': ajouterQuantite(); break;
					case '0':cout<<"Merci d'utiliser mon programme...\n\n";
					 	exit(-1);	
					default:
						system("cls");
						cout <<"\n\nChoix invalide.ressayer... !!"<<endl;
						break; 
						menuGest();
				}
			}
			while(res == '1' || 
			      res == '2' || 
				  res == '3' || 
				  res == '4' || 
				  res == '5' || 
				  res == '6' ||
				  res == '7' || 
				  res =='0'   );
	}


// Ajouter caissiere
void Gestionnaire::ajouterCaissiere(){
	fio.open("caissiere.dat",ios::binary|ios::app|ios::in|ios::out);
	if (!fio.is_open()){
		cout<<"Erreur lors de l'ouverture du fichier caissiere.txt";
		return ;
	}
	cout<<"Entrer le nom du caissiere: ";
	cin>>c.nom;
	cout<<"Entrer le prenom du caissiere: ";
	cin>>c.prenom;
	cout<<"Entrer l'adresse du caissiere: ";
	cin>>c.addresse;
	cout<<"Entrer le contact du caissiere: ";
	cin>>c.contact;
	cout<<"Souhaitez-vous enregistrer la caissiere(o/O)"<<c.prenom<<"?: ";
	char confirm;
	cin>>confirm;
	if (confirm == 'o'|| confirm == 'O'){
		fio.write((char*)&c,sizeof(c));
		system("cls");
		cout<<"Caissiere ajoute avec success! "<<endl;
	}
	
	
}

//Voir caissiere
void Gestionnaire::visualiserCaissiere(){
	int i;
	i = 0;
	fio.open("caissiere.dat",ios::binary|ios::out|ios::in);
	if(!fio.is_open()){
		cout<<"Erreur lors de l'ouverture du fichier caissiere.txt"<<endl;
		return ;
	}    
		cout<<"Caissiere disponible "<<endl;
		cout<<"No"<<"      "<<"Nom"<<"        "<<"Prenom"<<"       "<<"Addresse"<<"       "<<"Contact"<<endl;
		while(fio.read((char*)&c,sizeof(c))){
			i++;
		cout<<i<<"       "<<c.nom<<"     "<<c.prenom<<"     "<<c.addresse<<"     "<<c.contact<<endl;
		}
		if(i==0){
			cout<<"Auncune caissiere ajoute!\n"<<endl;
		}
	fio.close();
	
}

void Gestionnaire::connexion(){
	string email;
	string pass;
	
	do{
		cout<<"Veuillez vous connecter\n\n"<<endl;
		cout<<"Entrer votre email: ";
		cin>>email;
		
		cout<<"Veuillez entrer votre mot de passe! ";
		cin>>pass;
		if(email!="gestionnaire@gmail.com" || pass!="gestionnairepass"){
			cout<<"Votre mot de pass ou votre email est incorect ressayer !"<<endl;
		}else{
			system("cls");
			cout<<"Vous vous etes connecter en tant que gestionnaire!\n "<<endl;
			g.menuGest();
		}
	}while(email=="gestionnaire@gmail.com" && pass=="gestionnairepass");
	
}



/// Produits
// Ajouter produit

void Gestionnaire::ajouterProduit(){
	char confirm;
	Produit pr;
	int i;
	i = 0;
	fio.open("produits.dat",ios::binary|ios::out|ios::in|ios::app);
	if (!fio.is_open()){
		cout<<"Erreur lors de l'ouverture du fichier produit.dat"<<endl;
		return ;
	}
	cout<<"Entrer le nom du produit: ";
	cin>>pd.nom;
	cout<<"Entrer le prix de "<<pd.nom<<": ";
	cin>>pd.prix;
	cout<<"Entrer la quantite de "<<pd.nom<<":" ;
	cin>>pd.quantite;
	cout<<"Entrer la description de "<<pd.nom<<":" ;
	cin.ignore();
	cin.getline(pd.desc,200);
	
	cout<<"Souhaitez-vous enregistrer le produit (o/O) "<<pd.nom<<"? :";
	cin>>confirm;
	if (confirm == 'o'|| confirm == 'O'){
		fio.write((char*)&pd,sizeof(pd));
		system("cls");
		cout<<"Poduit ajoute avec success! "<<endl;
	}
	fio.close();
}

// Afficher produits
void Gestionnaire::visualiserProduit(){
	char res;
	int i;
	i = 0;
	fio.open("produits.dat",ios::binary|ios::out|ios::in);
	if(!fio.is_open()){
		system("cls");
		cout<<"Erreur lors de l'ouverture du fichier produits.dat"<<endl;
		return ;
	}
	else{
		cout<<"Produits disponible "<<endl;
		cout<<"No"<<"         "<<"Nom"<<"        "<<"Prix"<<"       "<<"Quantite"<<endl;
		while(fio.read((char*)&pd,sizeof(pd))){
			i++;
			cout<<i<<"        "<<pd.nom<<"       "<<pd.prix<<"         "<<pd.quantite<<endl;
		}
		if(i==0){
			cout<<"Le stock est vide!\n"<<endl;
		}
	}
	fio.close();
	cout<<"Souhaitez-vous voir les details d'un produit (o/O) ?: ";
	cin>>res;
	system("cls");
	if(tolower(res)=='o'){
		g.visualiserProduitDetails();
		
	}
	return;
	
	
}

//Afficher produit avec plus de details


void Gestionnaire::visualiserProduitDetails(){
	char nom_pr[100];
	bool trouve = false;
	fio.open("produits.dat",ios::binary|ios::out|ios::in);
	if(!fio.is_open()){
		system("cls");
		cout<<"Erreur lors de l'ouverture du fichier produits.dat";
		return ;
	}
	else{   
	cout<<"Saississez le nom du produit :";
	cin>>nom_pr;
	while(fio.read((char*)&pd,sizeof(pd))){
		if(strcmp(pd.nom,nom_pr)==0){
			cout<<"-----------------------------\n";
			cout<<"Details du produit "<<endl;
			cout<<"Nom:        "<<pd.nom<<endl;
			cout<<"Pix:        "<<pd.prix<<endl;
			cout<<"Quantite    "<<pd.quantite<<endl;
			cout<<"Description:"<<pd.desc<<endl;
			cout<<"-----------------------------\n";
			trouve =true;
			break;
		}
   	 }
   	 if(!trouve){
			system("cls");
			cout<<"Ce produit n'est pas enregistrer\n"<<endl;
		}
	}
	fio.close();
}



//supprimer produit
void Gestionnaire::supprimerProduit(){
	
	char nom_pr[100];
	bool trouve = false;
	cout<<"Saississez le nom du produit a supprimer :";
	cin>>nom_pr;
	fout.open("temp.dat",ios::binary);
	fin.open("produits.dat",ios::binary);
	while(!fin.eof()){
		fin.read((char*)&pd,sizeof(pd));
		if(!fin.eof()){
			if(strcmp(nom_pr,pd.nom)==0){
					cout<<"Details du produit "<<endl;
					cout<<"Nom:        "<<pd.nom<<endl;
					cout<<"Pix:        "<<pd.prix<<endl;
					cout<<"Quantite    "<<pd.quantite<<endl;
					cout<<"Description:"<<pd.desc<<endl;
					trouve =true;
				    cout<<"Voulez-vous supprimer ce produit (O/N) ?:";
				    char sup;
				 	cin>>sup;
				if(tolower(sup)=='o'){
					system("cls");
					cout<<"Produit supprimer!"<<endl;
								
			    }
		    }
		    else{
			fout.write((char*)&pd,sizeof(pd));
		}
		
		}
				 	 
	}
			
   	 	if(!trouve)
			cout<<"Ce produit n'est pas enregistrer"<<endl;
		
		fin.close();
		fout.close();
		remove("produits.dat");
		rename("temp.dat","produits.dat");
		
}

// mise a jour
void Gestionnaire::ajouterQuantite( ){
	bool trouve = false;
	int qt;
	char nom_pr[100];
	fio.open("produits.dat",ios::binary|ios::out|ios::in);
	if(!fio.is_open()){
		cout<<"Erreur lors de l'ouverture du fichier produits.dat";
		return ;
	}
	else{ 
	cout<<"Enter le nom du produit !: " ;
	cin>>nom_pr;
	while(fio.read((char*)&pd,sizeof(pd))){
		if(strcmp(pd.nom,nom_pr)==0){
			cout<<"-----------------------------\n";
			cout<<"Quantite actuelle: "<<pd.quantite<<endl;
			cout<<"-----------------------------\n";
			trouve =true;
			cout<<"Entrer la nouvelle quantite du produit de "<<pd.nom<<"!:";
			cin>>qt;
			if(qt>0){
				pd.quantite += qt;
				fio.seekp(fio.tellg() - static_cast<streamoff>(sizeof(pd)));
	            fio.write((char*)&pd, sizeof(pd));
	            system("cls");
	            cout<<"Quantite ajouter avec success !!\n\n";
			}else{
				system("cls");
				cout<<"Desole, la quantite doit etre >0\n\n";
			}
		}
		if(!trouve){
			cout<<"Ce produit n'est pas enregistrer\n\n"<<endl;
		}
   	 }
   	 fio.close();
	}
}


//aisiere
// Connection caissiere
void Caissiere::menuCais(){
	char res;
	do{
		cout<<"----------------------------"<<endl;
		cout<<"| (1)  Effectuer une vente |"<<endl;
		cout<<"| (0)   Quitter            |"<<endl;
		cout<<"----------------------------"<<endl;
		cout<<"Faites une option!: ";
		cin>>res;
		switch(res){
			case '1': c.vendreProduit();break;
			case '0': cout<<"\n\nMerci d'utiliser mon programme...\n\n";
					  exit(-1);
			 break;
			default :
				cout<<"Choix invalide. Ressayer..."<<endl;
				menuCais();
				 break;
		}
	}while(res=='1'|| res=='0');
}
void Caissiere::connexion(){
	string nom;
	string contact;
	Caissiere cai;
	string no, co;
	bool trouve = false;
	fio.open("caissiere.dat",ios::binary|ios::in|ios::out);
	if(!fio.is_open()){
	cout<<"Erreur lors de l'ouverture du fichier caissiere.dat";
	return ;
	}
	do{
		cout<<"\n\nVeuillez vous connecter\n\n"<<endl;
		cout<<"Entrer votre nom: ";
		cin>>nom;
		
		cout<<"Veuillez entrer votre numero de tel: ";
		cin>>contact;
		while(fio.read((char*)&c,sizeof(c))){
		if(strcmp(c.nom,nom.c_str())==0 && strcmp(c.contact,contact.c_str())==0){
			system("cls");
			cout<<"Bienvenue "<<c.nom<<"\n\n";
			cai.menuCais();
			no = c.nom;
			co  = c.contact;
			trouve = true;
			break;
		}	
	  }
	  if(!trouve){
			cout<<"Votre mot de pass ou votre numero de contact est incorect ressayer !\n"<<endl;
		}
	  fio.clear(); 
	  fio.seekg(0, ios::beg);
		
		
	}while(nom==no || contact==co);
	fio.close();	
}

//Vente
//void 
// Menu:

void menu_principal(){
	char option;
	do{
	
			cout<<"----------------------------"<<endl;
			cout<<"| (1)  Gestionnaire        |"<<endl;
			cout<<"| (2)  Caissirere          |"<<endl;
			cout<<"----------------------------"<<endl;
			cout<<"Chossissez une option :";
			cin>>option;
			
			switch(option){
				case '1': g.connexion(); break;
				case '2': c.connexion(); break;
				default:
					cout<<"Choix invalide!!: "<<endl;
			}
			
  }while(option=='1'|| option=='2');
}


void afficherProduit2(char nom_pr[100]){
	bool trouve = false;
	fio.open("produits.dat",ios::binary|ios::out|ios::in);
	if(!fio.is_open()){
		system("cls");
		cout<<"Erreur lors de l'ouverture du fichier produits.dat";
		return ;
	}
	else{   
	while(fio.read((char*)&pd,sizeof(pd))){
		if(strcmp(pd.nom,nom_pr)==0){
			cout<<"-----------------------------\n";
			cout<<"Details du produit "<<endl;
			cout<<"Nom:        "<<pd.nom<<endl;
			cout<<"Pix:        "<<pd.prix<<endl;
			cout<<"Quantite    "<<pd.quantite<<endl;
			cout<<"Description:"<<pd.desc<<endl;
			cout<<"-----------------------------\n";
			trouve =true;
			break;
		}
   	 }
   	 if(!trouve){
			system("cls");
			cout<<"Ce produit n'est pas enregistrer\n"<<endl;
		}
	}
	fio.close();	
}

//Venddre produit

void Caissiere::vendreProduit(){
	bool trouve = false;
	char nom_pr[200];
	int qt;
	
	fio.open("produits.dat",ios::binary|ios::out|ios::in);
	if(!fio.is_open()){
		system("cls");
		cout<<"Erreur lors de l'ouverture du fichier produits.dat";
		return ;
	}
	else{ 
	cout<<"Entrer le nom du produit : ";
	cin>>nom_pr;  
	while(fio.read((char*)&pd,sizeof(pd))){
		if(strcmp(pd.nom,nom_pr)==0){
			cout<<"-----------------------------\n";
			cout<<"Details du produit "<<endl;
			cout<<"Nom:        "<<pd.nom<<endl;
			cout<<"Pix:        "<<pd.prix<<endl;
			cout<<"Quantite    "<<pd.quantite<<endl;
			cout<<"Description:"<<pd.desc<<endl;
			cout<<"-----------------------------\n";
			trouve =true;
			
			do{
				cout<<"Enter la quatite a achete :";
		    	cin>>qt;
		    	if(pd.quantite<qt || qt < 0 )
				cout<<"Quantite invalide "<<endl;
			
			}while(pd.quantite<qt || qt < 0 );
		    	
				
			cout<<"Entrer le nom du client :";
			cin>>cl.nom;
			cout<<"Entrer le prenom du client :";
			cin>>cl.prenom;
			cout<<"Enter l'adresse du client :";
			cin>>cl.addresse;
			cout<<"Entrer le numero de contact du client :";
			cin>>cl.contact;
			
			cout<<"\n\n\n";
			cout<<"--------------------------------Facture----------------------------\n"; 
			cout<<"Nom              : "<<cl.nom<<"          "<<"prenom  : "<<cl.prenom<<endl;
			cout<<"Adresse          : "<<cl.addresse<<"     "<<"Contact : "<<cl.contact<<endl;
			cout<<"Nom du produit   : "<<pd.nom<<endl;
			cout<<"Prix unitaire    : "<<pd.prix<<endl;
			cout<<"Description      : "<<pd.desc<<endl;
			cout<<"Quantite achete  : "<<qt<<endl;
			cout<<"Prix total       : "<<pd.prix * qt<<endl;
			cout<<"Date et heure    : "<<temps()<<endl;
			cout<<"--------------------------------------------------------------------\n";
			
		}
   	 }
   	 if(!trouve){
			system("cls");
			cout<<"Ce produit n'est pas enregistrer\n"<<endl;
		}
	}
	fio.close();
	
	
}


// Main
int main(){

cout<<temps()<<endl;
menu_principal();
return 0;
}

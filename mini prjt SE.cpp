#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct fichier {

char name_Fi[50],id_Utl[50],emp_Fi[50];
int etat;
struct fichier* suiv;
// le champ "etat" est designée pour l'etat de partage du fichier (valeur '0' pour public et '1' pour prive)
// le champ "name_Fi" est designée pour le nom du fichier
// le champ "id_Utl" est designée pour l'identifiant du propriétaire du fichier
// le champ "emp_Fi" est designée pour l'emplacement physique du fichier
// le champ "suiv" est designée pour l'adresse du fichier suivant dans le catalogue
} fichier;

typedef struct fichier* catalogue;

//Ajout d'un fichier dans le catalogue
catalogue AddFile (catalogue f,char name[50],char id[50],char emp[50], int et)
{
	catalogue f1 = (fichier*)malloc(sizeof(fichier));
	strcpy(f1->name_Fi,name);
	strcpy(f1->id_Utl,id);
	strcpy(f1->emp_Fi,emp);
	f1->etat=et;
	
	
	if(f==NULL)
	f1->suiv=NULL;

	else
	f1->suiv=f;
	
	
		return f1;
}

//recherche d'un fichier dans le catalogue
catalogue  SearchFile (catalogue f,char name[],char id[50],int* i)
{
	catalogue f1=f;

	(*i)=1;	
	
	if (f==NULL)
	{   (*i)=2;
	   return NULL;
		}	
	
	else
	{
		while(f1!=NULL)
		{
			if(strcmp(f1->name_Fi,name)==0)
			{
				if(strcmp(f1->id_Utl,id)==0)
				{  (*i)=3;
				   return f1;
				}
				
				else
				(*i)=0;
				
				

			}
			
			f1=f1->suiv;
		}
		
	}
	if((*i)!=0 )
	(*i)=1;
	
	return NULL;
	

}

//creation adresse
void adrs(char* n,char* n1)
{
	int i;
	char c;
	
	for (i=0;i<strlen(n);i++)
	n1[i+1]=n[i];
	
	n1[i+1]='\0';
	
	n1[0]='@';
	
	
}
//Changement du nom d'un fichier
catalogue  RenameFile (catalogue f,char name[50],char id[50],char name2[50],int* i)
{
	catalogue f1=f;

	if (f==NULL)
	{
		(*i)=0;
		return NULL;
	}
	
	else
	{(*i)=3;
		while(f1!=NULL)
		{
			if(strcmp(f1->name_Fi,name)==0)
			{
			  (*i)=1;
			  
				if(strcmp(f1->id_Utl,id)==0)
				{
				  strcpy(f1->name_Fi,name2);
				  adrs(name2,f1->emp_Fi);
				  (*i)=2;
				}

			}
			
			f1=f1->suiv;
		}
		
		
		return f;
		
		
	}
	
}
	
//suppresion d'un fichier du catalogue
catalogue  DeleteFile (catalogue f,char name[50],char id[50],int *i)
{
	catalogue f1=f,f2;
	
		
	if (f==NULL)
	return NULL;
	
	
		if ((strcmp(f->name_Fi,name)==0) && strcmp(f->id_Utl,id)==0)
		{
			f2=f;
			f=f->suiv;
			free(f2);
			(*i)=0;
			return f;
		}
		
		else if ((strcmp(f->name_Fi,name)!=0) && strcmp(f->id_Utl,id)!=0)
		{
		 (*i)=1;
		 return f;
		}
	
	
	else
	{ (*i)=2;

	
		while (f1->suiv!=NULL)
		{
			if(strcmp(f1->suiv->name_Fi,name)==0)
			{ (*i)=1;
			
				if(strcmp(f1->suiv->id_Utl,id)==0)
				{
					f2 = f1->suiv;
					f1->suiv = f2->suiv;
					free(f2);
					(*i)=0;
					return f;
				}
				
				
				
			}
			
			f1=f1->suiv;
		}
	}
	
	
	return f;
	

}

//Partage d'un fichier
catalogue  ShareFile (catalogue f,char name[50],char id[50],int* i)
{
	catalogue f1;
	int b;
	
	f1 =  SearchFile (f,name,id,&b);
	
	if (b==3)
	{
		f1->etat= 0;
		return f1;

	}
	
	else
	(*i)=0;
	return NULL;
}

//Retrait de partage
void  EndshareFile (catalogue f,char name[50],char id[50])
{
	catalogue f1;
	int b;
	
	f1 =  SearchFile (f,name,id,&b);
	
	if (b==3)
	f1->etat = 1;

	
}

//Affichage de la liste des fichier d'un utilisateur donne
void PrintFiles (catalogue f,char id[50])
{
	int i=0;
	
	if(f!=NULL)
	{ printf("\t\t la liste des fichier d'utilisateur %s \n\n",id);
	
		while(f!=NULL)
		{
			
			if ( strcmp(f->id_Utl,id)== 0)
			{i=1;
			    printf(" - Nom du fichier : %s \n - Emplacement du fichier : %s \n",f->name_Fi,f->emp_Fi);
			    
			    if(f->etat==0)
			    printf(" - Etat du fichier : Public \n");
			    
			    else
			    printf(" - Etat du fichier : Prive \n");
			    
				}
				
				f=f->suiv;
	}}
	
	else
	printf("l'utilisateur n'a aucun fichier \n");
	
	if(i==0)
	printf("--------- Vide -----------\n\n");
}


main()
{
	catalogue f=NULL;
	
	catalogue f1;
	int v;
	
	char name[50],id[50],emp[50],name2[50];
	int etat,ch,r;

do{
    r=1;
    printf("\nWELCOME \n");
    printf("\t\t\t\t ************************* \t\t\t\t\n");
    printf("\t\t\t\t *                       * \t\t\t\t\n");
    printf("\t\t\t\t *          MENU         * \t\t\t\t\n");
    printf("\t\t\t\t *                       * \t\t\t\t\n");
    printf("\t\t\t\t ************************* \t\t\t\t\n");
    
    
    
    printf("1-Ajouter un fichier \n");
    printf("2-Cherhcer un fichier\n");
    printf("3-Renommer un fichier \n");
    printf("4-Supprimer un fichier \n");
    printf("5-Partager un fichier \n");
    printf("6-Arreter le partage d'un fichier \n");
    printf("7-Afficher la liste des fichier \n");
    printf("6-LOGOUT \n");
    
    printf("entrer votre choix: ");
    scanf("%d",&ch);
    
    switch(ch)
    {
    	case 1 : {
    		do{r=1;
    		        printf("\t\t\t*********** ADD **********************\n\n");
    				printf("entrer l'id du utilisateur  \n");
	                fflush(stdin);
                  	gets(id);	
	                printf("entrer le nom du fichier \n");
	                fflush(stdin);
	                gets(name);
	                printf("entrer l'etat du fichier  (taper 0 pour public et 1 pour prive )\n");
                    scanf("%d",&etat);
                    adrs(name,emp);
    			    f= AddFile (f,name,id,emp,etat);
    			    printf("\t\t\t\t\t\t\t\t ------------SUCCES \n");
    			    
    			    printf("\n Voulez vous ajouter un autre fichier (taper 0 pour 'Oui' et 1 pour 'Non' )\n ");
    			    scanf("%d",&r);
			}while(r==0);
			break;
		}
		
    	case 2 : {
    		do{r=1;
    		        printf("\t\t\t*********** SEARCH **********************\n\n");
    				printf("entrer l'id du utilisateur  \n");
	                fflush(stdin);
                  	gets(id);	
	                printf("entrer le nom du fichier (Attention!! Si le nom du fichier ne correspand pas au utilisateur saisi, Vous ne serez pas authorise a l'acceder!!) \n");
	                fflush(stdin);
	                gets(name);
	                f1=SearchFile (f,name,id,&v);
	                
	                switch(v)
            	{
            		case 0: printf("Vos n'avez pas la permission d'acceder ce fichier \n"); break;
            		
            		case 1: printf("le fichier introuvable \n");break;
            		
		            case 2 : printf("la liste est vide \n");break;
		            
		            case 3:  printf(" \n\n le fichier a recherche du utilisateur %s \n - Nom du fichier : %s \n - Emplacement du fichier : %s \n \t\t\t\t\t\t\t\t ------------SUCCES \n",f1->id_Utl,f1->name_Fi,f1->emp_Fi);break;

	           }


    			    printf("\n Voulez vous chercher un autre fichier (taper 0 pour 'Oui' et 1 pour 'Non' )\n ");
    			    scanf("%d",&r);
			}while(r==0);
			break;
		}
		
    	case 3 : {
    		do{r=1;
    		        printf("\t\t\t*********** RENAME **********************\n\n");
    				printf("entrer l'id du utilisateur  \n");
	                fflush(stdin);
                  	gets(id);	
	                printf("entrer le nom du fichier (Attention!! Si le nom du fichier ne correspand pas au utilisateur saisi, Vous ne serez pas authorise a l'acceder!!) \n");
	                fflush(stdin);
	                gets(name);
	                printf("entrer le nouveau nom du fichier \n");
	                fflush(stdin);
	                gets(name2);
	                
                    f = RenameFile (f,name,id,name2,&v);

                	switch(v)
            	{
		            case 0 : printf("la liste est vide \n");break;
		
		            case 1: printf("Vos n'avez pas la permission d'acceder ce fichier \n"); break;
		
		            case 2 : printf("Fichier renomme avec succes \n");break;
		            
		            case 3 : printf("le fichier introuvable \n");break;
		
               }
    			    printf("\n Voulez vous renommer un autre fichier (taper 0 pour 'Oui' et 1 pour 'Non' )\n ");
    			    scanf("%d",&r);
			}while(r==0);
			break;
		}
		
    	case 4 : {
    		do{r=1;
    		        printf("\t\t\t*********** DELETE **********************\n\n");
    				printf("entrer l'id du utilisateur  \n");
	                fflush(stdin);
                  	gets(id);	
	                printf("entrer le nom du fichier (Attention!! Si le nom du fichier ne correspand pas au utilisateur saisi, Vous ne serez pas authorise a l'acceder!!) \n");
	                fflush(stdin);
	                gets(name);

	                
                    f = DeleteFile (f,name,id,&v);

                	switch(v)
	           {
	               	case 0 : printf("Fichier suprrime avec succes \n");break;
		
		            case 1: printf("Vos n'avez pas la permission d'acceder ce fichier \n"); break;
		
		            case 2 : printf("le fichier introuvable \n");break;
		
               }
    			    printf("\n Voulez vous supprimer un autre fichier (taper 0 pour 'Oui' et 1 pour 'Non' )\n ");
    			    scanf("%d",&r);
			}while(r==0);
			break;
		}
		
    	case 5 : {
    		do{r=1;
    		        printf("\t\t\t*********** SHARE **********************\n\n");
    				printf("entrer l'id du utilisateur  \n");
	                fflush(stdin);
                  	gets(id);	
	                printf("entrer le nom du fichier (Attention!! Si le nom du fichier ne correspand pas au utilisateur saisi, Vous ne serez pas authorise a l'acceder!!) \n");
	                fflush(stdin);
	                gets(name);

	                
                    f1 = ShareFile (f,name,id,&v);

                    if(v !=0 )
                printf("le fichier est partage avec succes \n");

                    else
                    {
					
	                f1=SearchFile (f,name,id,&v);
	                
	                switch(v)
            	{
            		case 0: printf("Vos n'avez pas la permission d'acceder ce fichier \n"); break;
            		
            		case 1: printf("le fichier introuvable \n");break;
            		
		            case 2 : printf("la liste est vide \n");break;
		            
	           }

            }
                
    			    printf("\n Voulez vous partager un autre fichier (taper 0 pour 'Oui' et 1 pour 'Non' )\n ");
    			    scanf("%d",&r);
			}while(r==0);
			break;
		}
		
    	case 6 : {
    		do{r=1;
    		        printf("\t\t\t*********** END SHARE **********************\n\n");
    				printf("entrer l'id du utilisateur  \n");
	                fflush(stdin);
                  	gets(id);	
	                printf("entrer le nom du fichier (Attention!! Si le nom du fichier ne correspand pas au utilisateur saisi, Vous ne serez pas authorise a l'acceder!!) \n");
	                fflush(stdin);
	                gets(name);
                    EndshareFile (f,name,id); 
                    printf("le partage de fichier est arrete avec succes \n");
    			    printf("\n Voulez vous arreter le partage d'un autre fichier (taper 0 pour 'Oui' et 1 pour 'Non' )\n ");
    			    scanf("%d",&r);
			}while(r==0);
			break;
		}
		
    	case 7 : {
    		do{r=1;
    		        printf("\t\t\t*********** PRINT **********************\n\n");
    				printf("entrer l'id du utilisateur  \n");
	                fflush(stdin);
                  	gets(id);	
	                PrintFiles (f,id);
    			    printf("\n Voulez vous afficher la liste des fichiers d'un autre utilisateur (taper 0 pour 'Oui' et 1 pour 'Non' )\n ");
    			    scanf("%d",&r);
			}while(r==0);
			break;
		}
		
	}
	
		printf("\n Voulez vous faire un autre traitement (taper 0 pour 'Oui' et 1 pour 'Non' )\n ");
    	scanf("%d",&r);

}while(r==0);

printf("\t\t ----AUREVOIR---\n");
}

// convertir Txt2Bin.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
struct Dict {
	char palIngles [50];
	char palEspanol [50];
};

typedef struct Dict TipoDict;

struct Nodo {
	TipoDict info;
	struct Nodo *siguiente; 
};
typedef struct Nodo TipoNodo;
//TipoNodo *lista=NULL;

void convertirtxtBin(char *nombreTxt, char * nombreBin){
	FILE *mnjTxt, *mnjBin;
	char *tmpIngles, *tmpEspanol, linea[200];
	TipoDict tmpDict;
	mnjTxt= fopen (nombreTxt, "r");
	mnjBin=fopen (nombreBin, "wb");
	while (fgets (linea,200,mnjTxt)!=NULL){
		//char *fgets (apunBuffer, numBytes, archivo)	
		tmpIngles= strtok (linea,":");
		tmpEspanol=strtok(NULL, "\n");
		if( strlen(tmpIngles)<50 && strlen(tmpEspanol)<50){
			strcpy (tmpDict.palEspanol,tmpIngles);
			strcpy (tmpDict.palIngles,tmpEspanol);
			fwrite(&tmpDict,sizeof(tmpDict),1,mnjBin);
		//int fwrite (apunBuffer,tamañoBloque,nVeces, ,mnjArchivo)
		}
	}
	fclose (mnjTxt); 
	fclose (mnjBin);
}

void imprimirBin (char *nombreBin){
	FILE *mnjBin = fopen (nombreBin,"rb");
	TipoDict *tmpDict= ((TipoDict*)malloc(sizeof(TipoDict)));
	//int fread(apunBuffer,tamañoBytes,nVeces,mnjArchivos);
	while (fread(tmpDict,sizeof(TipoDict),1,mnjBin)==1){
		//printf("<%s> <%s> \n",tmpDict->palIngles, tmpDict ->palEspanol);
	}
	fclose(mnjBin);
}

char *Search (char *palabra,TipoNodo* lista){
	system("clear");
	TipoNodo*tmp=lista;
	while(tmp!=NULL){
		if(strcmp(tmp->info.palIngles,palabra)==0){
			return tmp->info.palEspanol;
		}
		tmp=tmp->siguiente;	
	}
	return ("La Palabra no existe");
}
TipoNodo * crearNodo (TipoDict elemento){
	TipoNodo *nodito;
	nodito=(TipoNodo *)malloc (sizeof(TipoNodo));
	strcpy (nodito ->info.palIngles, elemento.palIngles);
	strcpy(nodito->info.palEspanol,elemento.palEspanol);
	nodito ->siguiente=NULL;
	return nodito;
}
TipoNodo * adicionarLista (TipoDict elemento, TipoNodo *lst){
	TipoNodo *tmpNodo= crearNodo (elemento); 
	TipoNodo *p;
	if (lst==NULL){
		lst=tmpNodo;
	}
	else {
		p=lst;
		// CAMBIO
		while (p->siguiente !=NULL){
			p=p->siguiente;
		}
		p->siguiente=tmpNodo;
	}
	return lst;	
}
TipoNodo* cargarDictaLista(char *nombreArch,TipoNodo *lst){
	FILE *mnjArch=fopen (nombreArch, "r");
	TipoDict registro;
	TipoNodo *lista;
	// CAMBIO
	//lista=(TipoNodo *)malloc (sizeof(TipoNodo));
	while (fread(&registro,sizeof(TipoDict),1,mnjArch)==1){
		//printf ("<%s>:<%s>\n",registro.palIngles, registro.palEspanol);
		lst=adicionarLista (registro,lst);
	}
	fclose (mnjArch);
	return (lst);
}

void imprimirLista (TipoNodo *lst){
	TipoNodo *p=lst;

	while (p !=NULL){
		printf("%s : %s \n", p->info.palIngles, p->info.palEspanol);
		p=p->siguiente;
	}
	printf("\n");
}

TipoNodo * InsertarLista (TipoNodo *lst, int pos, TipoDict elemento){
	TipoNodo *p=lst;
	TipoNodo *q= crearNodo (elemento);
	int cont=1;
	if (pos==1){
		q->siguiente=p;
		lst=q;
	}
	else {

		while (cont<pos-1){
			p=p->siguiente;
			cont ++;
		}
		q->siguiente=p->siguiente;
		p->siguiente=q;
	}
	return lst;
}

int buscarPos (char *palabra, TipoNodo *lst){
	int cont=0;
	char palIngles [50];
	TipoNodo *p=lst;
	if (lst== NULL){
		return 1;
	}
	else {
		do{
			if (p->siguiente==	NULL){
				return cont+1;
			}
			strcpy (palIngles,p->info.palIngles);
			cont ++;
			p=p->siguiente;
		} while (strcmp(palabra,palIngles)>0);
	}
	return cont;
}

TipoNodo *Adicionar(char*Palabra,char*Traduccion,TipoNodo* lista){
	system("clear");
	printf("Palabra Añadida\n\n");
	TipoNodo* tmp=lista;
	TipoDict New;
	strcpy(New.palEspanol,Traduccion);
	strcpy(New.palIngles,Palabra);
	TipoNodo* NewNodo=crearNodo(New);
	int pos=buscarPos(Palabra,lista);
	int cont=1;
	if(pos==1){
		NewNodo->siguiente=tmp;
		lista=NewNodo;
	}
	else{
		while (cont<pos-1){
			tmp=tmp->siguiente;
			cont++;
		}
		NewNodo->siguiente=tmp->siguiente;
		tmp->siguiente=NewNodo;
	}
	return lista;
}
TipoNodo* Eliminar(char*Palabra,TipoNodo*lista){
	system("clear");
	printf("Palabra Eliminada\n\n");
	int pos=buscarPos(Palabra,lista);
	TipoNodo* tmp=lista;
	for (int i=1;i<pos-1;i++){
		tmp=tmp->siguiente;
	}
	tmp->siguiente=tmp->siguiente->siguiente;
	return lista;
}
TipoNodo* Modificar(char*Palabra,char*Palabra2,TipoNodo* lista){
	system("clear");
	printf("Palabra Modificada\n\n");
	int pos=buscarPos(Palabra,lista);
	TipoNodo* tmp=lista;
	for(int i=1;i<pos;i++){
		tmp=tmp->siguiente;
	}
	strcpy(tmp->info.palEspanol,Palabra2);
	return lista;
}
int Levi(char*Palabra,char*Palabra2){
	unsigned int x, y, Palabralen, Palabra2len;
    Palabralen = strlen(Palabra);
    Palabra2len = strlen(Palabra2);
    unsigned int matrix[Palabra2len+1][Palabralen+1];
    matrix[0][0] = 0;
    for (x = 1; x <= Palabra2len; x++)
        matrix[x][0] = matrix[x-1][0] + 1;
    for (y = 1; y <= Palabralen; y++)
        matrix[0][y] = matrix[0][y-1] + 1;
    for (x = 1; x <= Palabra2len; x++)
        for (y = 1; y <= Palabralen; y++)
            matrix[x][y] = MIN3(matrix[x-1][y] + 1, matrix[x][y-1] + 1, matrix[x-1][y-1] + (Palabra[y-1] == Palabra2[x-1] ? 0 : 1));

    return(matrix[Palabra2len][Palabralen]);
}
void Inteligente(char*Palabra,TipoNodo*lista){
	system("clear");
	TipoNodo*tmp=lista;
		while(tmp!=NULL){
			if(Levi(Palabra,tmp->info.palIngles)<=1){
				printf("%s\n",tmp->info.palIngles);
			}
			tmp=tmp->siguiente;
		}
}

void Save(TipoNodo *lst,char *nombrearch){
	FILE* mnjbin=fopen(nombrearch,"wb");
	FILE *mnjtxt=fopen("Prueba.txt","w");
	TipoNodo *p=lst;
	TipoDict *tmpinfo;
	char cadena[150];
	while (p != NULL){
		tmpinfo= &(p->info);
		sprintf(cadena,"< %s > : < %s >\n",tmpinfo->palIngles,tmpinfo->palEspanol);
		fputs(cadena,mnjtxt);
		fwrite(tmpinfo,sizeof(TipoDict),1,mnjbin);
		p = p->siguiente;
	}
	fclose(mnjbin);
	fclose(mnjtxt);
}
TipoNodo* menu(TipoNodo* lista,char* NombreTxt){
	int cont=0;
	char a;
	do{
		if(cont%2==0){
			printf("\n-------------------------------------Menu-------------------------------------\n\n");
			printf("Opciones:\n");
			printf("s: Salir:\n");
			printf("Termina el Programa\n");
			printf("b: Busqueda exacta:\n");
			printf("Busca una palabra exactamente como aparece en el diccionario\n");
			printf("a: Adicionar:\n");
			printf("Adiciona una nueva palabra al diccionario\n");
			printf("e: Eliminar:\n");
			printf("Elimina la palabra del diccionario\n");
			printf("m: Modificar:\n");
			printf("Cambia la traducción de una palabra\n");
			printf("i: Búsqueda inteligente:\n");
			printf("Busca palabras similares a la ingresada\n");			
			printf("Ingrese la Opción: ");
		}
		scanf("%c",&a);
		if (a=='s'){
			break;
		}
		else if(a=='b'){
			char Palabra[50];
			printf("Ingrese la palabra: ");
			scanf("%s",Palabra);
			printf("Traduccion: %s\n\n",Search(Palabra,lista));
		}
		else if(a=='a'){
			char Palabra[50];
			char Traduccion[50];
			printf("Ingrese la palabra en ingles: ");
			scanf("%s",Palabra);
			printf("Ingrese la traduccion: ");	
			scanf("%s",Traduccion);
			lista=Adicionar(Palabra,Traduccion,lista);		
		}
		else if(a=='e'){
			char Palabra[50];
			printf("Ingrese la palabra: ");
			scanf("%s",Palabra);
			lista=Eliminar(Palabra,lista);		
		}
		else if(a=='m'){
			char Palabra[50];
			char Palabra2[50];
			printf("Ingrese la palabra: ");
			scanf("%s",Palabra);
			printf("Ingrese corrección: ");
			scanf("%s",Palabra2);
			lista=Modificar(Palabra,Palabra2,lista);		
		}
		else if(a=='i'){
			char Palabra[50];
			printf("Ingrese la palabra aproximada: ");
			scanf("%s",Palabra);
			printf("Algunas sugerencias son:");
			Inteligente(Palabra,lista);	
			printf("\n\n");	
		}
		cont++;
	}while(1);
	return lista;
}
int main (int argc, char * argv[]){
	system("clear");
	TipoNodo *lista=NULL;
	//convertirtxtBin("palabras.txt","palabras.bin");
	lista=cargarDictaLista ("palabras.bin",lista);
	char *palabra=argv[1];
	if (palabra==NULL){
		lista=menu(lista,"palabras.bin");
		Save(lista,"palabras.bin");
	}
	else{
		printf("%s\n",Search(palabra,lista));
	}
	return 0;
}

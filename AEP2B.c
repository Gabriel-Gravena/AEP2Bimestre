#include<stdio.h>
#include<conio.c>
#include<windows.h>
#include<locale.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

FILE *arquivo;

void janelaLinha(int ci, int li, int cf, int lf, int corL, int corF, char msg[]);
void janelaFundo(int cI, int lI, int cF, int lF, int corF);
void menu();
void limpaAviso();
void cadastro(char us[50], char senh[50]);
void criptografar(char str[]); 
void descriptografarSTR(char str[]);
void descriptografarTXT();
void mostrarTXT();
void mostrarTXTexclusao();
bool excluirUsuario(char us[50]);
bool senhaForte(char s[50]);
bool validaUsuario(char us[50]);
void selectionSort(char usuario[][50], char senha[][50], int n);
void alterarTxt();

//========================================================================================

int main() {
	char usuario[50],senha1[50],senhaConf[50], usExcluido[50];
	int tecla, opc, i, l, lE;
	l = 1;
	bool sair = false;
	janelaLinha(10,7,24,19,0,7,"Bem vindo!"); 
	janelaFundo(11, 8, 24, 19, 7);	
	
	do{
		opc=115;

		menu();	
		textbackground(8);
		textcolor(15);
		switch(l){
			case 1:
				gotoxy(12,9); printf("%c", 175);
				gotoxy(13,9); printf("Inserir"); 
				break;
			case 2:
				gotoxy(12,11); printf("%c", 175);
				gotoxy(13,11); printf("Alterar"); 
				break;
			case 3:
				gotoxy(12,13); printf("%c", 175);
				gotoxy(13,13); printf("Excluir"); 
				break;
			case 4:
				gotoxy(12,15); printf("%c", 175);
				gotoxy(13,15); printf("Ler    "); 
				break;
			case 5:
				textbackground(8);
				textcolor(15);
				gotoxy(12,17); printf("%c", 175);
				gotoxy(13,17); printf("Sair   "); 
			break;
		}
		textbackground(0);
		
		tecla = _getch();
    	
		if(tecla < 0 || tecla == 0 || tecla == 244){
    		tecla = _getch();
		}
		
		switch(tecla){
			case 72:l--; break;
			case 80:l++; break;
		}
		if (l==0) l=5;
    	if (l==6) l=1;
    	
    	if(tecla==13)switch(l){
				case 1: 
				while(opc!=27){
					janelaLinha(27,6,80,20,14,0,"Inserir=Dados");
					textcolor(7);
					gotoxy(29,8); printf("informe o usuario: "); 
					gotoxy(48, 8); printf("                                ");
					gotoxy(29,9); printf("digite a senha: ");
					gotoxy(45, 9); printf("                                   ");
					gotoxy(29,10); printf("confirme a senha: ");
					gotoxy(47, 10); printf("                                ");
                    limpaAviso(28, 80, 11, 20);
					do{
                    	gotoxy(48, 8); fgets(usuario, 100, stdin);
                    	usuario[strcspn(usuario, "\n")] = 0; 
                    	criptografar(usuario);
                    	if(strlen(usuario)<3 || strlen(usuario)>16){
                    		limpaAviso(28, 80, 11, 20);
							textcolor(RED);
                    		gotoxy(38, 12); printf("Minimo 3 caracteres e maximo 16!");
                    		gotoxy(48, 8); printf("                                ");
							textcolor(7);
						}else if(validaUsuario(usuario)){
							limpaAviso(28, 80, 11, 20);
							textcolor(RED);
                    		gotoxy(42, 12); printf("Este usuario ja existe!");
                    		gotoxy(48, 8); printf("                                ");
							textcolor(7);
						}
						else{
							descriptografarSTR(usuario);
							textbackground(GREEN);
							gotoxy(48, 8); printf("%s", usuario);
							textbackground(0);	
						}
                	}while(validaUsuario(usuario));
					
					limpaAviso(28, 80, 11, 20);
					do{
                    	gotoxy(45, 9); fgets(senha1, 50, stdin);
                    	senha1[strcspn(senha1, "\n")] = 0; 
                    	if (!senhaForte(senha1)) {
                    		textcolor(RED);
                        	gotoxy(29, 12); printf("ERRO!! a senha deve conter pelo menos:");
                        	gotoxy(29, 13); printf("1 numero, 1 caracter especial e 1 letra maiuscula");
                        	gotoxy(45, 9); printf("                                   ");
                        	textcolor(7);
                    	}else{
                    		textbackground(GREEN);
							for(i=0;i<strlen(senha1);i++){
								gotoxy(45+i, 9); printf("*");	
							}
							textbackground(0);	
						}
					}while(!senhaForte(senha1));
					
					limpaAviso(28, 80, 11, 20);
					do{
                    	gotoxy(47, 10); fgets(senhaConf, 50, stdin);
                    	senhaConf[strcspn(senhaConf, "\n")] = 0; 
                    	if (strcmp(senha1, senhaConf)) {
                    		textcolor(RED);
                        	gotoxy(37, 12); printf("Erro: as senhas nao coincidem!");
                        	gotoxy(47, 10); printf("                                ");
                        	textcolor(7);
                    	}else{
                    		textbackground(GREEN);
							for(i=0;i<strlen(senhaConf);i++){
								gotoxy(47+i, 10); printf("*");	
							}
							textbackground(0);	
						}	
						
					}while(strcmp(senha1, senhaConf));
                    
                    criptografar(usuario);
                    criptografar(senha1);
					cadastro(usuario,senha1);
                    limpaAviso(28, 80, 11, 20);
                    textcolor(GREEN);
					gotoxy(38, 13); printf("Usuario cadastrado com sucesso!");
					textcolor(15);
					Sleep(100);
					gotoxy(29,16);
					printf("Pressione ESC para voltar ao menu..");
					gotoxy(29,17);
					printf("ENTER para um novo cadastro");
					opc=_getch();
					if(opc < 0 || opc == 0 || opc == 244){
    					opc = _getch();
    					}
    				while(opc!=27 && opc!=13){
    					opc = _getch();
						if(opc < 0 || opc == 0 || opc == 244){
    						opc = _getch();
    						}
						}
    				}
                    clrscr(); 
					janelaLinha(10,7,24,19,0,7,"Bem vindo!"); 
					janelaFundo(11, 8, 24, 19, 7);
					break;
				case 2:
					alterarTxt();
					clrscr(); janelaLinha(10,7,24,19,0,7,"Bem vindo!"); janelaFundo(11, 8, 24, 19, 7); break;
				case 3:
					do{
						limpaAviso(27, 80, 2, 25);
						descriptografarTXT("Excluir=Usuario");
						gotoxy(34,18); printf("Qual usuario deseja excluir?");
						gotoxy(34,19);
						fgets(usExcluido, 50, stdin);
						usExcluido[strcspn(usExcluido, "\n")] = 0;
					if(excluirUsuario(usExcluido)){
						textcolor(GREEN);
						gotoxy(34,21); printf("Usuario excluido com sucesso!");
						textcolor(15);
					}else if(excluirUsuario(usExcluido)==false){
						textcolor(RED);
						gotoxy(29,21);
						printf("Erro ao abrir o arquivo ou o usuario nao existe!");
						textcolor(15);
					}
						Sleep(500);
						limpaAviso(27, 80, 18, 25);
						gotoxy(30,23);
						printf("ESC para sair");
						gotoxy(30,24);
						printf("ENTER para nova exclusao..");
						opc = _getch();
					if(opc < 0 || opc == 0 || opc == 244){
    					opc = _getch();
    				}
    				}while(opc != 27);
    				clrscr(); 
					janelaLinha(10,7,24,19,0,7,"Bem vindo!"); 
					janelaFundo(11, 8, 24, 19, 7); 
					break;
				case 4:
					janelaLinha(53,2,53,24,14,0,"");
                    mostrarTXT();
					clrscr(); 
					janelaLinha(10,7,24,19,0,7,"Bem vindo!"); 
					janelaFundo(11, 8, 24, 19, 7);
					break;
				case 5: sair=true; 
				gotoxy(8,23);
				system("pause");
				clrscr(); break;
			}
	}while(tecla!=27 && sair!=true);
		
	
	
	
	
	textcolor(15);
	textbackground(0);
    return 0;
}

//===========================================================================================
void janelaLinha(int colInicial, int lnhInicial, int cFinal, int lFinal, int corLinha, int corFundo, char msg[]){
	
	int i;    
    
	textcolor(corLinha);
    textbackground(corFundo);
    for (i=colInicial;i<=cFinal;i++){ //desenha linhas horizontais
    	gotoxy(i,lnhInicial); 
    	printf("%c",205);
        gotoxy(i,lFinal); 
 		printf("%c",205);
    }
    for (i=lnhInicial;i<=lFinal;i++){ //desenha linhas verticais
        gotoxy(colInicial,i); printf("%c",186);
        gotoxy(cFinal,i); printf("%c",186);
    }   
    
    gotoxy(colInicial,lnhInicial);  printf("%c",201);
    gotoxy(cFinal,lnhInicial);  printf("%c",187);
    gotoxy(colInicial,lFinal);  printf("%c",200);
    gotoxy(cFinal,lFinal);  printf("%c",188);
    
    gotoxy(colInicial+2,lnhInicial);
    printf("%s",msg); 
    
    textbackground(0);
    textcolor(15);
}

//========================================================================================

void janelaFundo(int cI, int lI, int cF, int lF, int corF){
	int i,j;
	for(i=cI;i<cF;i++){
		for(j=lI;j<lF;j++){
			textbackground(corF);
			gotoxy(i,j); printf(" ");
		}
	}
}

//========================================================================================

void menu(){
	textbackground(7);
    textcolor(0);
	gotoxy(12,9); printf(" Inserir");
	gotoxy(12,11); printf(" Alterar");
	gotoxy(12,13); printf(" Excluir");
	gotoxy(12,15); printf(" Ler    ");
	gotoxy(12,17); printf(" Sair   ");
}

//=========================================================================================
void selectionSort(char usuario[][50], char senha[][50], int n) {
    char tempUser[50], tempSenha[50];
    int i, j, min_idx;
    
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        
        for (j = i + 1; j < n; j++) {
            if (strcmp(usuario[j], usuario[min_idx]) < 0) {
                min_idx = j;
            }
        }
        
        if (min_idx != i) {
            strcpy(tempUser, usuario[i]);
            strcpy(usuario[i], usuario[min_idx]);
            strcpy(usuario[min_idx], tempUser);

            strcpy(tempSenha, senha[i]);
            strcpy(senha[i], senha[min_idx]);
            strcpy(senha[min_idx], tempSenha);
        }
    }
}
//=========================================================================================

bool senhaForte(char s[50]){
	bool ch = false, num = false, maiusc = false, minusc = false;
	int i;

    for (i = 0; i < strlen(s); i++) {
        if ((s[i] >= 33 && s[i] <= 47) || (s[i] >= 58 && s[i] <= 64) || 
            (s[i] >= 91 && s[i] <= 96) || (s[i] >= 123 && s[i] <= 126)) {
            ch = true;  // Caracteres especiais
        } else if (s[i] >= 48 && s[i] <= 57) {
            num = true;  // Números
        } else if (s[i] >= 65 && s[i] <= 90) {
            maiusc = true;  // Letras maiúsculas
        } else if (s[i] >= 97 && s[i] <= 122) {
            minusc = true;  // Letras minúsculas
        }
    }

    if (ch && num && maiusc && minusc) {
        return true;
    } else {
        return false;
    }
}

//===================================================================================

bool validaUsuario(char us[50]){ //funcao para ver se o usuario ja existe
	FILE *arquivo;
	arquivo = fopen("senhacptfds.txt", "r");
	
	char usuario1 [50];
	bool us2, tamanho;
	
	if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return false;
    }
    
	if (strlen(us) < 3 || strlen(us) > 16) {
		fclose(arquivo);
		return true;
	}
	while(fscanf(arquivo, "%s %*s", usuario1) != EOF){
		if(strcmp(usuario1, us) == 0){
			fclose(arquivo);
			return true;
		}	
	}
	
	fclose(arquivo); 
	return false;
}

//===================================================================================
//28-80  11-20
void limpaAviso(int colI, int colF, int lI, int lF){
	int i, j;
	
	for(i=colI;i<colF;i++){
		for(j=lI;j<lF;j++){
			gotoxy(i,j); printf(" ");
		}
	}
	
}

//===================================================================================

void cadastro(char us[50], char senh[50]){
	FILE *arquivo;
	arquivo = fopen("senhacptfds.txt", "a");
	char usuariotxt[50][50], senhatxt[50][50];
	int tot, i;
	
	if(arquivo == NULL){
		printf("Erro ao abrir arquivo!\n");
	}else{
		fprintf(arquivo, "%s %s\n", us, senh);  // Salva o usuário e a senha no arquivo
		fclose(arquivo);
	}
	
	arquivo = fopen("senhacptfds.txt", "r");
	while(fscanf(arquivo, "%s %s", usuariotxt[tot], senhatxt[tot])!= EOF){
		tot++;
	}
	fclose(arquivo);
	
	arquivo = fopen("senhacptfds.txt", "w");
	selectionSort(usuariotxt, senhatxt, tot);
	for(i=0;i<tot;i++){
		fprintf(arquivo, "%s %s\n", usuariotxt[i], senhatxt[i]);
	}
	fclose(arquivo);
}

//===================================================================================

void criptografar(char str[]) {
	int i;
    for (i = 0; str[i] != '\0'; i++) {
        str[i] = str[i] + i + 4;  
    }
}

//===================================================================================

void descriptografarSTR(char str[]){
	int i;
    for (i = 0; str[i] != '\0'; i++) {
        str[i] = str[i]  - i - 4;  
    }	
}

//===================================================================================

void descriptografarTXT(char mesg[]){
	FILE *arquivo;
    char usuariotxt[50][50], senhatxt[50][50];
    int x=29, x1=57, y=3, tot=0, i;
	
	janelaLinha(26, 1, 80, 25, 14, 0, mesg);

    arquivo = fopen("senhacptfds.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
    }

    while (fscanf(arquivo, "%s %s", usuariotxt[tot], senhatxt[tot]) != EOF) {
        descriptografarSTR(usuariotxt[tot]);
        descriptografarSTR(senhatxt[tot]);
        tot++;
    }
    
	for(i=0;i<tot;i++){
        gotoxy(x,y);
        textcolor(RED);
        printf("usuario:%s", usuariotxt[i]);
		gotoxy(x1,y);
        printf("senha:%s", senhatxt[i]);
        y++;
        textcolor(15);
	}
    fclose(arquivo);
}

//==================================================================================

void mostrarTXT(){
	int x, z, x1, y, opc, tot, o=1;
	char usuario[50][50], senha[50][50];
	
	do{
		x=29;
		x1 = 57;
		y = 3;
		switch(o){
			case 1: 
				janelaLinha(26, 1, 80, 25, 14, 0, "Listar=Usuarios");
    			
    			arquivo = fopen("senhacptfds.txt", "r");
   			 	if (arquivo == NULL) {
        		printf("Erro ao abrir o arquivo!\n");
        		return;
   				}

   				tot=0;
    			while (fscanf(arquivo, "%s %s", usuario[tot], senha[tot]) != EOF) {
    		    tot++;
    			}
				
				for(z=0;z<tot;z++){
    		    gotoxy(x,y);
				textcolor(GREEN);
    		    printf("usuario:%s", usuario[z]);
				gotoxy(x1,y);
    		    printf("senha:%s", senha[z]);
    		    textcolor(15);
    		    y++;
				}
    			
    			fclose(arquivo);
    			break;
			case 2: descriptografarTXT("Listar=Usuarios"); break; 
		}
		
		gotoxy(27, 25);
		textcolor(14);
        printf("Pressione=ENTER==para=descriptografar..");
		textcolor(0);
		opc=_getch();
		if(opc < 0 || opc == 0 || opc == 244){
    		opc = _getch();
		}
		switch(opc){
			case 13: o++; break;
		}
		if (o==3) o=1;
    	
	}while(opc!=27);
}

//=====================================================================================

bool excluirUsuario(char us[]) {
	    FILE *arquivo;
	    char usuario[50][50], senha[50][50];
	    bool usEncontrado = false;
	    int tot = 0, i, j;
	
	    arquivo = fopen("senhacptfds.txt", "r");
	    if (arquivo == NULL) {
	        return false;
	    }

    while (fscanf(arquivo, "%s %s", usuario[tot], senha[tot]) != EOF) {
        descriptografarSTR(usuario[tot]);
        tot++;
    }
    fclose(arquivo);

    while(i<tot && usEncontrado == false) {
        if (strcmp(us, usuario[i]) == 0) {
            usEncontrado = true;
            for (j = i; j < tot - 1; j++) {
                strcpy(usuario[j], usuario[j + 1]);
                strcpy(senha[j], senha[j + 1]);
            }
            tot--;
        }
        i++;
    }

    if (usEncontrado) {
        arquivo = fopen("senhacptfds.txt", "w");
        if (arquivo == NULL) {
            return false;
        }

        for (i = 0; i < tot; i++) {
            criptografar(usuario[i]); 
            fprintf(arquivo, "%s %s\n", usuario[i], senha[i]);
        }
        fclose(arquivo);
        return true;
    }

	if(!usEncontrado){
		fclose(arquivo);
		return false;
	}
}
//======================================================================================
void alterarTxt(){
	descriptografarTXT("Alterar");
	FILE *arquivo;
    char us1[2][50], usuario[50][50], senha[50][50];
    bool usEncontrado = false;
    int tot = 0, i, j;
	
	gotoxy(35,19);
	printf("Qual usuario deseja alterar?");
	gotoxy(35,20);
	fgets(us1[0], 50, stdin);
	us1[0][strcspn(us1[0], "\n")] = 0;
	limpaAviso(30,78,19,21);
	gotoxy(35,19);
	printf("Informe o novo usuario:");
	gotoxy(35,20);
	fgets(us1[1], 50, stdin);
	us1[1][strcspn(us1[1], "\n")] = 0;
	
    arquivo = fopen("senhacptfds.txt", "r");
    if (arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo!");
    }	
    
    while (fscanf(arquivo, "%s %s", usuario[tot], senha[tot]) != EOF) {
        descriptografarSTR(usuario[tot]); 
        if(strcmp(usuario[tot], us1[0]) == 0){
        	strcpy(usuario[tot], us1[1]);
        	usEncontrado=true;
		}
        tot++;
    }
    fclose(arquivo);
    if(usEncontrado){
    	selectionSort(usuario, senha, tot);
    	arquivo = fopen("senhacptfds.txt", "w");
    	for(i=0;i<tot;i++){
    		criptografar(usuario[i]);
    		fprintf(arquivo,"%s %s\n", usuario[i], senha[i]);
		}
		fclose(arquivo);
		textcolor(GREEN);
		gotoxy(35,22);
		printf("Usuario alterado com sucesso!");
		textcolor(15);
	}else{
		textcolor(RED);
		gotoxy(35,22);
		printf("Usuario nao encontrado!");
		textcolor(15);
	}
	gotoxy(30,24);
	printf("Pressione qualquer tecla para sair..");
	_getch();
}
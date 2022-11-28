#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

void menu(); 
void deposito();
void saque();
void extrato();
void gpn();
void sair();
void tipoGasto();
void getData();
void attSaldo();
double saldo=0, movimento=0, urgente=0, recorrente=0, desnecessario=0;
int opc, u=0, r=0, d=0, nv;// u = Gasto Urgente-Nao Recorrente; r = Gasto recorrente; d = Gasto Desnecessario; nv = Nivel do gasto(opc switch)
char motivo[100], nvs[30];
FILE *arq;
FILE *arqSaldo;

int main(){
	   
    printf("\n-------------------------------------------------------------\n"
    "| Ola, Bem vindo ao FinApp, seu ajudante financeiro pessoal |"
    "\n-------------------------------------------------------------\n");
    _sleep(3000);

	menu();
    
    
    return 0;
}

void attSaldo(){
    arqSaldo = fopen("Saldo.txt","w+");
    fprintf(arqSaldo,"%.2lf %d %d %d %.2lf %.2lf %.2lf",saldo, u, r, d, urgente, recorrente, desnecessario);
    fclose(arqSaldo);
}

void getData(){
    struct tm *d;  
    time_t s;
    time(&s);
    d = localtime(&s);
    fprintf(arq,"%d/%d/%d - %d:%d", d->tm_mday,d->tm_mon+1,d->tm_year+1900,d->tm_hour,d->tm_min);
}

void tipoGasto(){
printf("\nEste Gasto e:\n"
        "\n-------------------------------\n"
        "| 1 - Urgente-nao Recorrente  |\n"
        "| 2 - Recorrente              |\n"
        "| 3 - Desnecessario           |\n"
        "-------------------------------\n");
        scanf("%d", &nv);
                switch (nv)
                {
                case 1:
                    u++;
                    urgente = urgente + movimento;
                    fprintf(arq, "\nGasto: Urgente\n");
                break;
                case 2:
                    r++;
                    recorrente = recorrente + movimento;
                    fprintf(arq, "\nGasto: Recorrente\n");
                break;
                case 3:
                    d++;
                    desnecessario = desnecessario + movimento;
                    fprintf(arq, "\nGasto: Desnecessario\n");
                break;
        
                default:
                    printf("\nDigite um numero de 1 a 3\n");
                    tipoGasto();
                 break;
                }
}

void menu(){
	
	system("cls");
    arq = fopen("Contas.txt", "a");
    arqSaldo = fopen("Saldo.txt","r");
    rewind(arqSaldo);
    fscanf(arqSaldo,"%lf %d %d %d %lf %lf %lf", &saldo, &u, &r, &d, &urgente, &recorrente, &desnecessario);
    fclose(arqSaldo);
    
     printf("\n--------------------------------------------------------\n"
    "saldo = %.2lf R$ "
    "\n--------------------------------------------------------\n", saldo);

    printf("\n\nEscolha uma opcao abaixo digitando o numero correspondente:\n\n"
    "\n------------------------------\n"
    "| 1 - Deposito               |\n"
    "| 2 - Saque                  |\n"
    "| 3 - Extrato                |\n"  
    "| 4 - Gastos por necessidade |\n" 
    "| 5 - Sair                   |\n"
    "------------------------------\n");
    scanf("%d",&opc);
    
	switch (opc)
    {
    case 1:
        deposito();       
        break;
    case 2:
        saque();
        break;
    case 3:
        fclose(arq);
     	extrato();
    	break;

    case 4:
    	gpn();
    	break;
    
    case 5:
	    sair();
        break;
        
    default:
    	printf("Por favor Digite um numero entre 1 e 5");
    	menu();
   		break;
    }
}

void deposito(){
	    system("cls");
        printf("Digite o valor do deposito:\n");
        scanf("%lf",&movimento);
        saldo = saldo + movimento;
        printf("Digite a origem do deposito:\n");
        fflush(stdin); gets(motivo);
        getData();
        printf("Deposito de %.2lf R$ realizado.",movimento);
        fprintf(arq, "\nValor: + %.2lf R$\n"
        "Origem: %s\n\n", movimento, motivo);
        fclose(arq);
        attSaldo();
        _sleep(2000);
        menu();
}

void saque(){
	    system("cls");
        printf("Digite o valor do saque:\n");
        scanf("%lf",&movimento);
        getData();
        tipoGasto();
        saldo = saldo - movimento;
        printf("Digite o motivo:\n");
        fflush(stdin); gets(motivo); 
        fprintf(arq, "Valor: - %.2lf R$ \n"
        "Motivo: %s\n\n", movimento,motivo);
        printf("Saque de %.2lf R$ realizado.\n"
        "Motivo: %s \n\n",movimento, motivo);
        fclose(arq);
        attSaldo();
        _sleep(2000);
        menu();
}

void extrato(){   
    system("cls");
    system("Contas.txt");
    printf("digite qualquer tecla para constinuar\n");
    system("pause");
    fclose(arq);
    menu();
}

void gpn(){
	system("cls");
    printf("Voce realizou:\n"
    "%d gastos Urgentes - nao recorrentes totalizando em um valor de %.2lf R$\n"
    "%d gastos recorrentes totalizando em um valor de %.2lf R$\n"
    "%d gastos desnecessarios totalizando em um valor de %.2lf R$\n", u, urgente, r, recorrente, d, desnecessario);
    printf("\n Digite 1 para voltar ou qualquer outro numero para sair");
    scanf("%d", &opc);
    
    if(opc == 1){
        menu();
    }
    else{
        sair();
    }
}

void sair(){
	system("cls");
        printf("Obrigado por usar o FinApp :)");
        fclose(arq);
        _sleep(1500);
        return 0;
}
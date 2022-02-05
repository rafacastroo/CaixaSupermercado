#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//ESTRUTURA DE LISTA
struct List{
    char ItemNome[20];
    double ItemPreco;
    int quantidade;
};

//ESTRUTURA DE CARTÃO
struct Card{
    char NumeroCartao[25];
    long double SaldoCartao;
    int AnoDeExpiracao;
    char Bandeira[15];
    int PIN;
};

//DECLARAÇÕES GERAIS
int n,i;
char escolha;
struct List list[50];
FILE *bill;
struct Card Customer;
double s;

//FUNÇÃO DE DESCONTO BLOQUEADA
double Desconto(double sum){
    double Des;
    
    if(sum>=1000 && sum<2000){Des = 0.10;}
    else if(sum>=2000 && sum<4000){Des = 0.20;}
    else if(sum>=4000 && sum<7000){Des = 0.30;}
    else if(sum>=7000){Des = 0.40;}
    else{Des = 0;}
    
    return Des;
}
double desconto;

//FUNÇÃO DO DISPLAY
void PrintItems()
{
    for(i=1;i<n;i++){
        //Print items
        printf("\tItem %d: \n", i);
        printf("\tItem Nome: %s\n", list[i].ItemNome);
        printf("\tItem Preco: %.2lf RS\n", list[i].ItemPreco);
        printf("\tQuantidade : %d\n", list[i].quantidade);
        printf("\n");
    }
}

//FUNÇÃO PARA IMPRIMIR RECIBO
void printRecibo()
{
    FILE *recibo;
    recibo = fopen("Recibo.txt", "w");
    fprintf(recibo, "===============================RESUMO DA CONTA================================\n\n");
    fprintf(recibo, "\n");
    fprintf(recibo, "\n");
    fprintf(recibo, "Item:\t\t\t\t\t\t\tPreco:\n");
    for(i=1; i<n; i++)
    {
        fprintf(recibo, "%s x %d", list[i].ItemNome, list[i].quantidade);
        fprintf(recibo, "\t\t\t\t\t\t\t");
        fprintf(recibo, "%.2lf RS", list[i].ItemPreco);
        fprintf(recibo, "\n");
    }
    fprintf(recibo, "\n\n");
    fprintf(recibo, "Total Montante: ");
    fprintf(recibo, "%.2lf RS\n", s);
    fprintf(recibo, "%.0lf%c DESCONTO OFERECIDO \n", (desconto*100), '%');
    fprintf(recibo, "Valor a pagar apos o desconto: %.2lf RS\n", s - desconto*s );
    fprintf(recibo, "\n\n");
    fprintf(recibo, "===========================================================================\n\n");
    fprintf(recibo, "Tenha um bom dia! Venha nos visitar novamente!\nEndereco: *casa*\nContato: 012345678901\n");
    fclose(recibo);
    printf("Recibo feito\n\n");
}

//FUNÇÃO PRINCIPAL
int main()
{
    printf("\n<<<CONTADOR DE CAIXA>>>\n\nDesconto continuo!!!!! Obtenha um desconto de ate 40 por cento !!!!!!!\n\n\n");
    n=50;
    s=0;
    //ENTRAR COM OS ITENS AQUI
    for(i=1;i<n;i++){
        printf("Add item? S/N\nEnter: ");
        fflush(stdin);
        scanf("%c", &escolha);
        fflush(stdout);
        if(escolha=='n' || escolha=='N'){
            n = i;
            break;
        }
        else if(escolha=='s' || escolha=='S'){
            printf("Enter Item Nome: ");
            fflush(stdin);
            gets(list[i].ItemNome);
            fflush(stdout);
            reEnterPreco:
            printf("Enter Item Preco: ");
            scanf("%lf", &list[i].ItemPreco);
            if(list[i].ItemPreco<=0)
            {
                printf("Valor do Preco Invalido!\nRe-");
                goto reEnterPreco;
            }
            reEnterQuantidade:
            printf("Enter quantidade: ");
            scanf("%d", &list[i].quantidade);
            if(list[i].quantidade<=0)
            {
                printf("Valor de Quantidade Invalido!\nRe-");
                goto reEnterQuantidade;
            }
            printf("\n");
            continue;
        }
        else{
            printf("\nEntrada invalida. Entre novamente!\n");
            i--;
            continue;
        }
    }
    printf("\n");
//CALCULAR SOMA
    for(i=1; i<n;i++){
        s = s + (list[i].ItemPreco*list[i].quantidade);
    }
    PrintItems();
    printf("Resultado Total: %.0lf RS\n", s);//Resultado w/o desconto
    desconto = Desconto(s);    
    printf("Desconto surpresa oferecido: %.0lf%c\n", (desconto*100), '%' );
    printf("Quantia a pagar: %.2lf RS\n", s - desconto*s );
    


//CASO O COMPRADOR ESQUECER ALGUM ITENS

    ItemDelete:
    printf("\nDelete,Add item ou continuar a compra(D/A/C)\n");
    fflush(stdin);
    scanf("%c", &escolha);
    fflush(stdout);
    if(escolha=='D' || escolha=='d')
    {
        Novamente:
        printf("Entrar com numero do item: ");
        int pos;//ENTRAR NUMERO DO ITEM PARA REMOVER
        scanf("%d", &pos);

        //CALCULAR NOVO PRECO
        s = s - (list[pos].ItemPreco*list[pos].quantidade);

        if(pos>n || pos<0)
        {
            printf("Item nao encontrado! Tente novamente\n");
            goto Novamente;
        }
        else
        {
            //MOVER TODOS ELEMENTOS PARA -1
            for(i=pos; i<n-1; i++)
            {
                strcpy(list[i].ItemNome, list[i+1].ItemNome);
                list[i].ItemPreco = list[i+1].ItemPreco;
                list[i].quantidade = list[i+1].quantidade;
            }

        }

        //DIMINUIR TAMANHO DA VARIAVEL
        n--;
        
    }
    else if (escolha=='A' || escolha=='a')
    {
        //MOVER TODOS OS ELEMENTO PARA  +1
        for(i=n+1;i>=1;i--)
        {
            strcpy(list[i+1].ItemNome, list[i].ItemNome);
            list[i+1].ItemPreco=list[i].ItemPreco;
            list[i+1].quantidade = list[i].quantidade;
        }

        //ENTRAR COM NOVO ELEMENTO QUE SERÁ SUBSTITUIDO PELO PRIMEIRO
        printf("Entar Nome do Item: ");
        fflush(stdin);
        gets(list[i+1].ItemNome);
        fflush(stdout);
        printf("Enter Item Preco: ");
        scanf("%lf", &list[i+1].ItemPreco);
        printf("Enter quantidade: ");
        scanf("%d", &list[i+1].quantidade);
        //CALCULAR NOVO PREÇO
        s = s + (list[i+1].ItemPreco*list[i+1].quantidade);

        //AUMENTAR TAMANHO VARIAVEL
        n++;

    }
    else if( escolha=='C' || escolha=='c' ){}//NO COND. SO LOOP EXIT
    else
    {
        printf("Entrada incorreta! Trente novamente!\n");
        goto ItemDelete;//GOES BACK TO START     
    }
    PrintItems();
    printf("TOTAL : %.2lf BR\n", s);

//DESCONTO
    desconto = Desconto(s);
    printf("Surpresa desconto concedido: %.0lf%c\n", (desconto*100), '%' );
    printf("Quantia a pagar: %.2lf BR\n", s - desconto*s );

//AFERIÇÃO FINAL
    finalCheck:
    printf("\n>>Algo mais?\nS-Sim\nN-Nao \nEnter: ");
    fflush(stdin);
    scanf("%c", &escolha);
    fflush(stdout);
    if(escolha=='N' || escolha=='n'){}
    else if (escolha=='S' || escolha=='s')
    {
        goto ItemDelete;
    }
    else
    {
        printf(">>Nao entendi, entrada invalida!\n");
        goto finalCheck;

    }

//IMPRIMIR RECIBO
    printRecibo();

//OPÇÃO DE PAGAMENTO    
    opcaoPagamento:
    printf(">>Dinheiro ou Cartao?\n(1)Dinheiro\t(2)Cartao\nEnter: ");
    int ch;
    scanf("%d", &ch);
    switch(ch){
        //SE PAGAR COM DINHEIRO
        case 1:
        {
            printf(">>Pagar dinheiro(NOTE: ENTRAR VALOR): ");
            double carteira;
            scanf("%lf", &carteira);
            double mudanca;
            if(carteira<( s - (s*desconto))){
                printf(">>Desculpe, dinheiro insuficiente!\nMudar Forma de Pagamento\n\n");
                goto opcaoPagamento;
            }
            else if (carteira > ( s - (s*desconto)) ){
                mudanca = carteira - ( s - (s*desconto) );
                printf("%.2lf RS diferenca devolvida!Obrigado pela compra\n", mudanca);
            }
            else if ( carteira == ( s - (s*desconto)) ){
                printf("Obrigado pela compra!\n");
            }
            break;
        }
        //SE PAGAR COM CARTÃO
        case 2:
        {
            bill = fopen("CreditBill.txt", "w");
            Customer.SaldoCartao=100000;
            Bandeira:
            printf("Nome do Cartao: ");
            fflush(stdin);
            gets(Customer.Bandeira);
            fflush(stdout);
            int k=0, marca=1;
            while( Customer.Bandeira[k] != '\0' )
            {
                if( (Customer.Bandeira[k]>='a' && Customer.Bandeira[k]<='z') || (Customer.Bandeira[k]>='A' && Customer.Bandeira[k]<='Z') || Customer.Bandeira[k]==' ' || Customer.Bandeira[k]=='-'  )
                {
                    marca = 1;
                }
                else
                {
                    marca= 0;
                }
                if(marca==0)
                {
                    break;
                }
                k++;
            }
            switch(marca)
            {
                case 1:
                {
                    break;
                }
                case 0:
                {
                    printf("Cartao nao aceito! Re-");
                    goto Bandeira;
                }
            }
            CNum:
            printf("Numero cartao: ");
            fflush(stdin);
            gets(Customer.NumeroCartao);
            fflush(stdout);
            int m=0, flag=1;
            while(Customer.NumeroCartao[m] != '\0')
            {
                if( Customer.NumeroCartao[m] >= '0' && Customer.NumeroCartao[m] <= '9' )
                {
                    marca = 1;
                }
                else
                {
                    marca = 0;
                }
                if(marca==0)
                {
                    break;
                }
                m++;
            }

            switch (marca)
            {
                case 1:
                {
                    break;
                }
                case 0:
                {
                    printf("Erro! Tente novamente ");
                    goto CNum;
                }
            }
            
            if(strlen(Customer.NumeroCartao) == 16){}
            else
            {
                printf("Numero do Cartao Invalido. Tente novamente ");
                goto CNum;
            }
            AnoDeExpiracao:
            printf("Ano de Expiracao: ");
            scanf("%d", &Customer.AnoDeExpiracao);
            if( Customer.AnoDeExpiracao<=2019 || Customer.AnoDeExpiracao>=2030 )
            {
                printf("Ano invalido");
                goto AnoDeExpiracao;
            }
            pin:
            printf("Enter PIN: ");
            scanf("%d", &Customer.PIN);
            if( Customer.PIN<=0 || Customer.PIN>=10000 )
            {
                printf("Invalid PIN. Re-");
                goto pin;
            }
            if( Customer.SaldoCartao>= (s - (desconto*s) ) )
            {
                fprintf(bill, "\t RECIBO DE DINHEIRO\n=========================\n");
                fprintf(bill, "Endereco:\t\t*endereco*\n");
                fprintf(bill, "Tel:\t\t012345678901\n");
                fprintf(bill, "=====DETALHES DE FATURAMENTO=====\n");
                fprintf(bill, "NUMERO CARTAO. : %s\n", Customer.NumeroCartao);
                fprintf(bill, "BANDEIRA CARTAO : %s\n", Customer.Bandeira);
                fprintf(bill, "ANO DE EXPIRACAO : %d\n", Customer.AnoDeExpiracao);
                fprintf(bill, "FUNCAO : Credit Card\n");
                fprintf(bill, "TOTAL COMPRA : %.2lf RS\n", (s - (s*desconto)) );
                fprintf(bill, "=========================\n\n\n");
                fprintf(bill, "ASSINAR:____________________\n");
                fprintf(bill, "Volte Sempre!\n");
            }
            else
            {
                printf(">>SALDO INSUFICIENTE!\n");
                        goto opcaoPagamento;
            }
                    
            fclose(bill);
            break;
        }
        default:
        {
            printf(">>Opcao nao especificada\nRetry\n");
            goto opcaoPagamento;
        }
    }
    printf("\n\n>>CLIENTE ATENDIDO COM SUCESSO\n\n\n");

//FECHAR SISTEMA
    close:
    printf("(1)Fechar Cliente\t(2)Proximo Cliente\nEscolha: ");
    int num;
    char tecla;
    scanf("%d", &num);
    if(num==1){
        printf(">>PRESSIONE A TECLA ENTER PARA FECHAR O CONTADOR\n");
        getchar();
        scanf("%c", &tecla);
        return 0;
    }else if(num==2){
        printf("\n\n----------------------------------------------------------------------------------------------PROXIMO CLIENTE--------------------------------------------------------------------------------------------------------\n\n");
        main();
    }else{
        printf(">>ESCOLHA INVALIDA\n");
        goto close;
    }


}

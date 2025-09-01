#include <stdio.h>
#include <stdlib.h>

struct Caractere{

    char valor;
    struct Caractere *proximo;
};

struct Email{

    int tamanho;
    struct Caractere *inicio;
    struct Caractere *fim;
};

struct Email *iniciar(){

    struct Email *email = malloc(sizeof(struct Email));
    email->fim = NULL;
    email->inicio = NULL;
    email->tamanho = 0;

    return email;
}

void adicionar_caractere(struct Email *email, char letra){  

    struct Caractere *caractere = malloc(sizeof(struct Caractere)); 
    caractere->valor = letra;              
    caractere->proximo = NULL; 

    if(email->tamanho == 0){                     
        email->fim = caractere;                              
        email->inicio = caractere;

    }else{
        email->fim->proximo = caractere;                      
        email->fim = caractere;                                                 

    }   

    email->tamanho++;         
}

int q5(struct Email *email){

    char sufixo[22];
    const char *sufixo1, *sufixo2, *sufixoUsuario1, *sufixoUsuario2;
    sufixo1 = "estudante.ifms.edu.br";
    sufixo2 = "ifms.edu.br";

    email->inicio = email->inicio->proximo; 

    int i = 0;
    while((email->inicio != NULL) && (i < 22)){

        sufixo[i] = email->inicio->valor;
        email->inicio = email->inicio->proximo;  
        i++;      
    }
    sufixo[i] = '\0';
    sufixoUsuario1 = sufixo;
    sufixoUsuario2 = sufixo;

    while((*sufixoUsuario1 && *sufixo1)){

        if((*sufixoUsuario1++ != *sufixo1++)){
            
            while((*sufixoUsuario2 && *sufixo2)){

                if((*sufixoUsuario2++ != *sufixo2++)){
                    return 0;
                }
            }
        }
    }

    return 1;
}

int q4(struct Email *email){

    while((email->inicio != NULL) && (email->inicio->valor >= '0' && email->inicio->valor <= '9') || (email->inicio->valor == '@')){

        if(email->inicio->valor == '@'){
            return q5(email);
        }

        email->inicio = email->inicio->proximo;
    }

    return 0;
}

int q3(struct Email *email){

    while((email->inicio != NULL) && ((email->inicio->valor >= 'a' && email->inicio->valor <= 'z') || (email->inicio->valor >= '0' && email->inicio->valor <= '9') || (email->inicio->valor == '@'))){

        if(email->inicio != NULL && email->inicio->valor >= '0' && email->inicio->valor <= '9'){
            return q4(email);
        }

        if(email->inicio != NULL && email->inicio->valor == '@'){
            return q5(email);
        }

        email->inicio = email->inicio->proximo;
    }

    return 0;
}

int q2(struct Email *email){

    email->inicio = email->inicio->proximo;

    if(email->inicio != NULL && email->inicio->valor >= 'a' && email->inicio->valor <= 'z'){    

        email->inicio = email->inicio->proximo;
        return q3(email);
    }

    return 0;
}

int q1(struct Email *email){

    while((email->inicio != NULL) && (email->inicio->valor >= 'a' && email->inicio->valor <= 'z') || (email->inicio->valor == '.')){

        if(email->inicio->valor == '.'){
            return q2(email);
        }

        email->inicio = email->inicio->proximo;
    }

    return 0;
}

int q0(struct Email *email){

    if((email->inicio != NULL) && (email->inicio->valor >= 'a' && email->inicio->valor <= 'z')){  

        email->inicio = email->inicio->proximo;
        return q1(email);
    }
    
    return 0;
}

void imprimir_saida(struct Email *email, int status, FILE *arq_saida){

    struct Caractere *c = email->inicio;

    while(c != NULL){
        fputc(c->valor, arq_saida);
        c = c->proximo; 
    }

    if(status){
        fputs(", sim\n", arq_saida);
    }else{
        fputs(", nao\n", arq_saida);
    }
}

void limpar_lista(struct Email *email){

    struct Caractere *atual = email->inicio;
    struct Caractere *prox;

    while (atual != NULL) {
        prox = atual->proximo;  
        free(atual);             
        atual = prox;            
    }

    email->inicio = NULL;
    email->tamanho = 0;
}

void ler_entrada(struct Email *email){

    int status;
    char letra;
    FILE *arq_entrada = fopen("t2_b1_interdisciplinar_afd_email.entrada", "r");
    FILE *arq_saida = fopen("leonardo_armelin_t2_b1_interdisciplinar_afd_email.saida", "w");

    while((letra = fgetc(arq_entrada)) != EOF){
        
        if(letra != '\n'){
            adicionar_caractere(email, letra);

        }else{
            struct Caractere *inicio_original = email->inicio;

            status = q0(email);
            email->inicio = inicio_original;

            imprimir_saida(email, status, arq_saida);
            limpar_lista(email);
        }
    }

    if(email->tamanho > 0){

        struct Caractere *inicio_original = email->inicio;

        status = q0(email);
        email->inicio = inicio_original;

        imprimir_saida(email, status, arq_saida);
        limpar_lista(email);
    }


    fclose(arq_entrada);
    fclose(arq_saida); 
}

int main(){

    struct Email *email = iniciar();
    ler_entrada(email);

    return 0;
}
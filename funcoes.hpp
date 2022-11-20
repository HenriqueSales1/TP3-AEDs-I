#include <iostream>

#ifndef FUNCOES_H
#define FUNCOES_H

using namespace std;

typedef struct
{
    string nome;
    string endereco;
    string idade;
    string sexo;

    char triagem[18];
    int prioridade;
} Paciente;

typedef struct
{
    string nome;
    string espec;
    string crm;

    Paciente paciente;

    time_t tempo;
    bool livre = true;
} Medico;

typedef struct Elemento *Apontador;

typedef struct Elemento
{
    Medico medicos[5];
    Paciente pacientes;
    Apontador prox;
};

typedef struct Fila
{
    Apontador primeiro, ultimo;
    int tamanho;
};

typedef struct
{
    int atendimentos;
    Medico medicos[5];
    Fila fila;
} Upa;

void CriaFilaVazia(Fila *fila);
bool FilaVazia(Fila *fila);
void EnfileraPaciente(Fila *fila, Paciente item);
void EnfileiraPrioridade(Fila *fila, Paciente item);
Paciente DesenfileiraPaciente(Fila *fila);
void DesenfileiraTudo(Fila *fila);

void MedicoLivre(Upa *upa);
void Perguntas(int i);
void Cadastro(Upa *upa);
void TriagemLivre(Upa *upa);
void Atendimentos(Upa *upa);
void RemoveMedico(Upa *upa, string nome);
void ListaMedicos(Upa upa);
void CadastroMedicos(Upa *upa);


#endif
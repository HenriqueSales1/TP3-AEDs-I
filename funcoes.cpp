#include <iostream>
#include <time.h>
#include "funcoes.hpp"

using namespace std;

string perguntas[18] = {"Comprometimento da via aérea", "Respiração ineficaz", "Choque", "Não responde a estímulos", "Em convulsão",
                        "Dor Severa", "Grande hemorragia incontrolável", "Alteração do estado de consciência", "Temperatura maior ou igual a 39°C", "Trauma craniano severo",
                        "Dor moderada", "Pequena hemorragia incontrolável", "Vômito persistente", "Temperatura entre 38°C e 39°C",
                        "Idoso ou grávida", "Dor leve", "Náuseas", "Temperatura entre 37°C e 38°C"};

void CriaFilaVazia(Fila *fila)
{
    fila->primeiro = NULL;
    fila->ultimo = NULL;
    fila->tamanho = 0;
}

bool FilaVazia(Fila *fila)
{
    if (fila->primeiro == NULL || fila->tamanho == 0)
    {
        return true;
    }
    return false;
}

void EnfileraPaciente(Fila *fila, Paciente item)
{
    Apontador aux = new Elemento;
    aux->pacientes = item;
    aux->prox = NULL;

    if (FilaVazia(fila))
    {
        fila->primeiro = aux;
        fila->ultimo = fila->primeiro;
        fila->tamanho++;
    }
    else
    {
        aux->prox = fila->primeiro;
        fila->tamanho++;
    }
}

void EnfileiraPrioridade(Fila *fila, Paciente item)
{
    Apontador aux = fila->primeiro, atual = new Elemento, anterior;
    bool i = 1;
    int cont = 0;
    if (FilaVazia(fila))
    {
        EnfileraPaciente(fila, item);
        return;
    }
    while (i)
    {
        if (aux == NULL)
        {
            break;
        }
        if (aux->pacientes.prioridade <= item.prioridade)
        {
            anterior = aux;
            aux = aux->prox;
            cont++;
        }
        else
        {
            i = 0;
        }
    }
    if (cont > 0)
    {
        atual->pacientes = item;
        atual->prox = anterior->prox;
        anterior->prox = atual;
        fila->tamanho++;
    }
    else
    {
        atual->pacientes = item;
        atual->prox = aux;
        fila->primeiro = atual;
        fila->tamanho++;
    }
}

Paciente DesenfileiraPaciente(Fila *fila)
{
    Apontador deletado;
    Paciente retorno;
    if (!FilaVazia(fila))
    {
        deletado = fila->primeiro;
        retorno = deletado->pacientes;
        fila->primeiro = fila->primeiro->prox;
        fila->tamanho--;
        delete deletado;
        return retorno;
    }
    else
    {
    }
}

void DesenfileiraTudo(Fila *fila)
{
    Apontador aux = fila->primeiro;
    while (aux != NULL)
    {
        Apontador deletado = aux;
        aux = aux->prox;
        delete deletado;
    }
    CriaFilaVazia(fila);
}

// void ImprimeFila(Fila *fila)
// {
//     if (FilaVazia(fila))
//     {
//         return;
//     }
//     Apontador aux = fila->primeiro;
//     while (aux != NULL)
//     {
//         aux = aux->prox;
//     }
// }

//------------------------------------------------------------------------
//                      TAD REFERENTE À UPA A SEGUIR
//------------------------------------------------------------------------

void MedicoLivre(Upa *upa)
{
    for (int i = 0; i < 5; i++)
    {
        if (upa->medicos[i].livre)
        {
            continue;
        }
        else if (upa->medicos[i].paciente.prioridade == 0)
        {
            if (((clock() - upa->medicos[i].tempo) / CLOCKS_PER_SEC) / 60 >= 60)
            {
                upa->medicos[i].livre = true;
            }
        }
        else if (upa->medicos[i].paciente.prioridade == 1)
        {
            if (((clock() - upa->medicos[i].tempo) / CLOCKS_PER_SEC) / 60 >= 25)
            {
                upa->medicos[i].livre = true;
            }
        }
        else if (upa->medicos[i].paciente.prioridade == 2)
        {
            if (((clock() - upa->medicos[i].tempo) / CLOCKS_PER_SEC) / 60 >= 20)
            {
                upa->medicos[i].livre = true;
            }
        }
        else if (upa->medicos[i].paciente.prioridade == 3)
        {
            if (((clock() - upa->medicos[i].tempo) / CLOCKS_PER_SEC) / 60 >= 12)
            {
                upa->medicos[i].livre = true;
            }
        }
        else if (upa->medicos[i].paciente.prioridade == 4)
        {
            if (((clock() - upa->medicos[i].tempo) / CLOCKS_PER_SEC) / 60 >= 8)
            {
                upa->medicos[i].livre = true;
            }
        }
    }
}

void Perguntas(int i)
{
    cout << perguntas[i] << "?" << endl;
}

void Cadastro(Upa *upa)
{
    MedicoLivre(upa);
    char opcao = 's';
    do
    {
        Paciente paciente;
        system("cls");
        cout << "Insira o nome: " << endl;
        cin >> paciente.nome;

        cout << "Insira sua idade: " << endl;
        cin >> paciente.idade;

        cout << "Insira seu sexo: " << endl;
        cin >> paciente.sexo;

        cout << "Insira seu endereço: " << endl;
        cin >> paciente.endereco;
        system("cls");
        int j = 18;
        for (int i = 0; i < 18; i++)
        {
            cout << "O paciente possui ";
            Perguntas(i);
            cin >> paciente.triagem[i];
            system("cls");
            if (paciente.triagem[i] == 's' && i < j)
            {
                j = i;
            }
            if (paciente.triagem[i] == 's' && i < 5)
            {
                break;
            }
        }
        if (j < 5)
        {
            paciente.prioridade = 0;
        }
        else if (j < 10)
        {
            paciente.prioridade = 1;
        }
        else if (j < 15)
        {
            paciente.prioridade = 2;
        }
        else if (j < 18)
        {
            paciente.prioridade = 3;
        }
        else
        {
            paciente.prioridade = 4;
        }
        EnfileiraPrioridade(&upa->fila, paciente);
        cout << "Deseja realizar nova triagem?" << endl;
        cin >> opcao;
    } while (opcao != 'n');
    int tamanhoincio = upa->fila.tamanho;
    for (int i = 0; i < 5; i++)
    {

        if (!upa->medicos[i].livre)
        {
            continue;
        }

        if (FilaVazia(&upa->fila))
        {
            break;
        }
        else
        {
            upa->medicos[i].paciente = DesenfileiraPaciente(&upa->fila);
            upa->medicos[i].livre = false;
            upa->medicos[i].tempo = clock();
            upa->atendimentos++;
        }
    }
    if (tamanhoincio == upa->fila.tamanho)
    {
        cout << "Sem vagas disponíveis. Favor aguardar.\n\n";
        return;
    }
    else
    {
        cout << "Pacientes encaminhados." << endl;
        if (FilaVazia(&upa->fila))
            return;
        cout << "Pacientes em espera: " << upa->fila.tamanho;
        return;
    }
}

void TriagemLivre(Upa *upa)
{
    if (FilaVazia(&upa->fila))
    {
        cout << "Fila de espera vazia.";
        return;
    }
    MedicoLivre(upa);
    int tamanhoincio = upa->fila.tamanho;
    for (int i = 0; i < 5; i++)
    {
        if (!upa->medicos[i].livre)
        {
            continue;
        }
        if (FilaVazia(&upa->fila))
        {
            break;
        }
        upa->medicos[i].paciente = DesenfileiraPaciente(&upa->fila);
        upa->medicos[i].livre = false;
        upa->medicos[i].tempo = clock();
        upa->atendimentos++;
    }
    if (tamanhoincio == upa->fila.tamanho)
    {
        cout << "Sem vagas disponíveis. Favor aguardar.";
        return;
    }
    else
    {
        cout << "Pacientes encaminhados.";
        if (FilaVazia(&upa->fila))
            return;
        cout << "Pacientes em espera: " << upa->fila.tamanho;
        return;
    }
}


void Atendimentos(Upa *upa)
{
    MedicoLivre(upa);
    int cont = 0;
    cout << "Atendimentos ocorrendo no momento: \n";
    for (int i = 0; i < 5; i++)
    {
        if (upa->medicos[i].livre)
        {
            continue;
        }
        cout << "Médico: " << upa->medicos[i].nome << endl;
        cout << "Paciente: " << upa->medicos[i].paciente.nome << endl;
        cout << "Nuâncias: ";
        int cont2 = 0;
        for (int j = 0; j < 18; j++)
        {
            if (upa->medicos[i].paciente.triagem[j] == 's')
            {
                cout << perguntas[j] << endl;
                cont2++;
            }
        }
        if (cont2 == 0)
        {
            cout << "Nenhuma.";
        }
        cont++;
        cout << endl
             << endl;
    }
    if (cont == 0)
    {
        cout << "Nenhum.";
    }
    system("pause");
}

void RemoveMedico(Upa *upa, string nome)
{
    for (int i = 0; i < 5; i++)
    {
        if (upa->medicos[i].nome == nome)
        {
            upa->medicos[i].livre = true;
            system("cls");
            cout << "Médico liberado.";
            return;
        }
    }
    cout << "Médico não registrado.";
}

void ListaMedicos(Upa upa)
{
    system("cls");
    for (int i = 0; i < 5; i++)
    {
        cout << "Nome: " << upa.medicos[i].nome << endl;
        cout << "Especialização: " << upa.medicos[i].espec << endl;
        cout << "CRM: " << upa.medicos[i].crm << endl
             << endl;
        if (upa.medicos[i].livre)
        {
            cout << "Médico disponível p/ atendimento." << endl
                 << endl;
            cout << "---------------------------------------------\n";
        }
        else
        {
            cout << "Médico ocupado." << endl;
            cout << "Paciente: " << upa.medicos[i].paciente.nome << endl;
            cout << "Tempo de consulta: " << ((clock() - upa.medicos[i].tempo) / CLOCKS_PER_SEC) / 60 << "min." << endl
                 << endl;
            cout << "---------------------------------------------\n";
        }
    }
    system("pause");
}
void CadastroMedicos(Upa *upa)
{
    upa->atendimentos = 0;
    FilaVazia(&upa->fila);
    upa->medicos[0].nome = "Henrique";
    upa->medicos[1].nome = "Lucas";
    upa->medicos[2].nome = "Tiago";
    upa->medicos[3].nome = "Igor";
    upa->medicos[4].nome = "Thales";
    upa->medicos[0].espec = "Oncologista";
    upa->medicos[1].espec = "Pediatra";
    upa->medicos[2].espec = "Oftalmologista";
    upa->medicos[3].espec = "Neurologista";
    upa->medicos[4].espec = "Cardiologista";
    upa->medicos[0].crm = "1532324";
    upa->medicos[1].crm = "3274541";
    upa->medicos[2].crm = "5456869";
    upa->medicos[3].crm = "4637342";
    upa->medicos[4].crm = "7809562";
}

#include <iostream>
#include <windows.h>
#include "funcoes.cpp"

using namespace std;


void Menu();

int main()
{
    UINT CPAGE_UTF8 = 65001;
    SetConsoleOutputCP(CPAGE_UTF8);

    Upa upa;
    CadastroMedicos(&upa);
    int escolha;
    char decisao;

    while (escolha != 7)
    {
        Menu();
        cout << "Digite a opção desejada: ";
        cin >> escolha;
        string nome;
        switch (escolha)
        {
        case 1:
            ListaMedicos(upa);
            system("cls");
            break;
        case 2:
            Cadastro(&upa);
            break;
        case 3:
            TriagemLivre(&upa);
        case 4:
            cout << "Digite o nome do médico a ser liberado: ";
            cin >> nome;
            RemoveMedico(&upa, nome);
            break;
        case 5:
            Atendimentos(&upa);
        case 6:
            MedicoLivre(&upa);
        default:
            cout << "Deseja sair do programa?\n(S ou s para sim, N ou n para não)\n\nEscolha: ";
            cin >> decisao;
            if (decisao == 's' || decisao == 'S')
            {
                escolha = 7;
            }
            else
            {
                escolha = 8;
            }
            break;
        }
    }
    system("cls");
    cout << "Atendimentos realizados hoje: " << upa.atendimentos;
    return 0;
}

void Menu()
{
    cout << "---------------------------------------------------\n";
    cout << "\t\tMENU DO HOSPITAL\n";
    cout << "---------------------------------------------------\n\n";
    cout << "1. Listar médicos\n";
    cout << "2. Cadastrar paciente\n";
    cout << "3. Esvaziar lista de espera\n";
    cout << "4. Liberar médico\n";
    cout << "5. Imprimir atendimentos em ocorrência\n";
    cout << "6. Verificar término de consultas em andamento\n";
    cout << "7. Sair do programa\n";
    cout << "---------------------------------------------------\n\n";
}
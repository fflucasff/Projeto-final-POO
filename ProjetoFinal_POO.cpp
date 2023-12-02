#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
using namespace std;

//A classe Contato armazena o nome e o telefone de um contato.
class Contato
{
private:
	string nome;
	string telefone;

public:
	Contato(string _nome, string _telefone) : nome(_nome), telefone(_telefone) {}

	string getNome() const
	{
		return nome;
	}
	string getTelefone() const
	{
		return telefone;
	}

	void mostrarContato() const
	{
		cout << "Nome: " << nome << ", Telefone: " << telefone << endl;
	}

	string salvarFormatado() const
	{
		return nome + ";" + telefone;
	}
};

//Escreve os contatos em um arquivo de texto chamado "contatos.txt".
void salvarContatos(const vector<Contato>& contatos)
{
	ofstream arquivo("contatos.txt");
	if (arquivo.is_open())
	{
		for (size_t i = 0; i < contatos.size(); ++i)
		{
			arquivo << contatos[i].salvarFormatado() << endl;
		}
		arquivo.close();
		cout << "Contatos salvos no arquivo 'contatos.txt'.\n";
	}
	else
	{
		cout << "Erro ao abrir o arquivo.\n";
	}
}

//Lê os contatos do arquivo "contatos.txt" e os carrega para um vetor.
vector<Contato> carregarContatos()
{
	vector<Contato> contatos;
	ifstream arquivo("contatos.txt");
	if (arquivo.is_open())
	{
		string linha;
		while (getline(arquivo, linha))
		{
			size_t pos = linha.find(';');
			if (pos != string::npos)
			{
				string nome = linha.substr(0, pos);
				string telefone = linha.substr(pos + 1);
				contatos.push_back(Contato(nome, telefone));
			}
		}
		arquivo.close();
	}
	return contatos;
}

//Declara um vetor de contatos e carrega os contatos existentes do arquivo.
int main()
{
	vector<Contato> contatos = carregarContatos();
	int opcao;
	bool continuar = true;

	while (continuar)
	{
		cout << "\nEscolha uma opcao:\n";
		cout << "1. Adicionar Contato\n";
		cout << "2. Visualizar Contatos\n";
		cout << "3. Deletar Contato\n";
		cout << "4. Sair\n";
		cout << "Opcao: ";

		if (!(cin >> opcao))
		{
			cout << "Entrada invalida. Por favor, insira um numero.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}

		cin.ignore(numeric_limits<streamsize>::max(), '\n');

		//Solicita ao usuário o nome e o telefone do novo contato.
		//Adiciona o novo contato ao vetor e salva os contatos atualizados no arquivo.
		switch (opcao)
		{
		case 1:
		{
			string nome, telefone;
			cout << "Digite o nome do contato: ";
			getline(cin, nome);
			cout << "Digite o telefone do contato: ";
			getline(cin, telefone);
			contatos.push_back(Contato(nome, telefone));
			salvarContatos(contatos);
			cout << "Contato adicionado com sucesso!\n";
			break;
		}

		//Mostra a lista de contatos armazenados no vetor.
		case 2:
		{
			if (contatos.empty())
			{
				cout << "Nenhum contato cadastrado.\n";
			}
			else
			{
				cout << "Lista de Contatos:\n";
				for (size_t i = 0; i < contatos.size(); ++i)
				{
					contatos[i].mostrarContato();
				}
			}
			break;
		}

		//Mostra a lista de contatos com números correspondentes.
		//Permite que o usuário digite os números dos contatos a serem excluídos separados por espaço.
		//Remove os contatos escolhidos do vetor e salva os contatos atualizados no arquivo.
		case 3:
		{
			if (contatos.empty())
			{
				cout << "Nenhum contato cadastrado para excluir.\n";
			}
			else
			{
				cout << "Lista de Contatos:\n";
				for (size_t i = 0; i < contatos.size(); ++i)
				{
					cout << i + 1 << ". ";
					contatos[i].mostrarContato();
				}

				cout << "Digite o numero do contato que deseja excluir: ";
				int indiceExclusao;
				if (!(cin >> indiceExclusao) || indiceExclusao < 1 || indiceExclusao > static_cast<int>(contatos.size()))
				{
					cout << "Opcao invalida.\n";
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					break;
				}

				cin.ignore(numeric_limits<streamsize>::max(), '\n');

				contatos.erase(contatos.begin() + indiceExclusao - 1);
				salvarContatos(contatos);
				cout << "Contato excluido com sucesso!\n";
			}
			break;
		}

		//Encerra o programa
		case 4:
			cout << "Saindo do programa...\n";
			continuar = false;
			break;

		default:
			cout << "Opcao invalida. Escolha novamente.\n";
		}
	}

	return 0;
}

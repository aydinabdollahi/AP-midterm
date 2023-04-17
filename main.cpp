#include <vector>
#include <algorithm>
#include <iostream>
#include "classes.h"
using namespace std;

// Lists

vector<Genome> genomes;
vector<Cell> cells;
vector<Genome> chromosomes;

// Menu of the program

int main()
{
	while (true)
	{
		system("cls");
		int choice;
		int n;
		string rna, dna1, dna2;
		string a1, a2;
		int index;
		char c1, c2;
		string type;
		Cell *c;
		Genome *g;
		int m;
		cout << "[1] Create a genome" << endl;
		cout << "[2] Print a genome" << endl;
		cout << "[3] Create DNA from RNA" << endl;
		cout << "[4] Small mutation on a genome" << endl;
		cout << "[5] Large mutation on a genome" << endl;
		cout << "[6] Reverse mutation on genome" << endl;
		cout << "[7] Create a cell" << endl;
		cout << "[8] Print a cell" << endl;
		cout << "[9] Cell Death" << endl;
		cout << "[10] Large mutation on cell" << endl;
		cout << "[11] small mutation on cell" << endl;
		cout << "[12] reverse mutation on cell" << endl;
		cout << "[13] Print all palindromes" << endl;
		cout << "[14] Exit the program" << endl;
		cout << "Please select one of options: " << endl;

		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "Enter the RNA:";
			cin >> rna;
			cout << "Enter DNA:";
			cin >> dna1 >> dna2;
			g = new Genome();
			g->setDNA(dna1, dna2);
			g->setRNA(rna);
			genomes.push_back(*g);
			break;
		case 2:
			cout << "Enter the index of genome:";
			cin >> index;
			a1 = genomes[index].getDNA1();
			a2 = genomes[index].getDNA2();
			cout << a1 << endl
				 << a2 << endl;
			break;
		case 3:
			cout << "Enter the index of genome:";
			cin >> index;
			cout << complement(genomes[index].getRNA());
			break;
		case 4:
			cout << "dna / rna? ";
			cin >> type;
			cout << "Enter the index of genome: ";
			cin >> index;
			cout << "Enter number of mutation: ";
			cin >> n;
			cout << "Enter the characters (from / to): ";
			cin >> c1 >> c2;
			if (type == "dna")
			{
				genomes[index].SMutationDNA(c1, c2, n);
				a1 = genomes[index].getDNA1();
				a2 = genomes[index].getDNA2();
				cout << a1 << endl
					 << a2 << endl;
			}
			else if (type == "rna")
			{
				genomes[index].SMutationRNA(c1, c2, n);
				cout << genomes[index].getRNA() << endl;
			}
			break;
		case 5:
			cout << "dna / rna? ";
			cin >> type;
			cout << "Enter the index of genome:";
			cin >> index;
			cout << "Enter s1:";
			cin >> a1;
			cout << "Enter s2:";
			cin >> a2;
			if (type == "dna")
			{
				genomes[index].LMutationDNA(a1, a2);
				a1 = genomes[index].getDNA1();
				a2 = genomes[index].getDNA2();
				cout << a1 << endl
					 << a2 << endl;
			}
			else if (type == "rna")
			{
				genomes[index].LMutationRNA(a1, a2);
				cout << genomes[index].getRNA() << endl;
			}
			break;
		case 6:
			cout << "dna / rna? ";
			cin >> type;
			cout << "Enter the substring: ";
			cin >> a1;
			cout << "Enter the index of genome:";
			cin >> index;
			if (type == "dna")
			{
				genomes[index].reverseMutationDNA(a1);
				a1 = genomes[index].getDNA1();
				a2 = genomes[index].getDNA2();
				cout << a1 << endl
					 << a2 << endl;
			}
			else if (type == "rna")
			{
				genomes[index].reverseMutationRNA(a1);
				cout << genomes[index].getRNA() << endl;
			}
			break;
		case 7:
			cout << "Number of chromosomes: ";
			cin >> index;
			c = new Cell(index);
			cells.push_back(*c);
			for (int i = 0; i < index; i++)
			{
				cout << "DNA of chromosome " << i + 1 << ": " << endl;
				cin >> a1 >> a2;
				cells.at(i).addChromosome(a1, a2);
			}
			break;
		case 8:
			cout << "The index of chromosome: ";
			cin >> index;
			chromosomes = cells.at(index).chromosome;
			for (auto &&i : chromosomes)
			{
				cout << i.getRNA() << endl
					 << i.getDNA1() << endl
					 << i.getDNA2() << endl;
			}
			break;
		case 9:
			cout << "Enter the index of cell: ";
			cin >> index;
			cells[index].cellDeath();
			cells.erase(cells.begin() + index);
			break;
		case 10:
			cout << "Enter the index of cell: ";
			cin >> index;
			cout << "Enter s1: ";
			cin >> a1;
			cout << "Enter n: ";
			cin >> n;
			cout << "Enter s2: ";
			cin >> a2;
			cout << "Enter m: ";
			cin >> m;
			cells[index].LMutation(a1, a2, n, m);
			break;
		case 11:
			cout << "Enter the index of cell: ";
			cin >> index;
			cout << "Enter n: ";
			cin >> n;
			cout << "Enter m: ";
			cin >> m;
			cout << "Characters: " << endl;
			cin >> c1 >> c2;
			cells[index].SMutation(c1, c2, n, m);
			break;
		case 12:
			cout << "Enter the index of cell:";
			cin >> index;
			cout << "Enter s: ";
			cin >> a1;
			cout << "Enter n: ";
			cin >> n;
			cells[index].reverseMutation(a1, n);
			break;
		case 13:
			cout << "Enter the index of cell: ";
			cin >> index;
			cells[index].palindrome();
			break;
		case 14:
			exit(0);
			break;
		}
	}
}
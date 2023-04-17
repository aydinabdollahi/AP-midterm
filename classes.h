#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Genome class
// Contain DNA (two strings) and RNA
// Some methods to manipulate the date of genome
class Genome
{
private:
    string RNA;
    string DNA[2];

public:
    void setRNA(string s);
    void setDNA(string s1, string s2);
    string getRNA();
    string getDNA1();
    string getDNA2();

    void buildDNA();
    void SMutationRNA(char a, char b, int n);
    void SMutationDNA(char a, char b, int n);
    void LMutationRNA(string s1, string s2);
    void LMutationDNA(string s1, string s2);
    void reverseMutationRNA(string s);
    void reverseMutationDNA(string s);

    friend class Cell;
};

string complement(string s);

// Cell class
// Contain a list of chromosomes (genomes)
class Cell
{
private:
    int n;

public:
    Cell(int n);
    vector<Genome> chromosome;

    void addChromosome(string a, string b);
    bool isComplement(char a, char b);
    void cellDeath();

    void SMutation(char a, char b, int n, int m);
    void LMutation(string s1, string s2, int n, int m);
    void reverseMutation(string s, int n);
    void palindrome();
};
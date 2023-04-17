#include <iostream>
#include <algorithm>
#include <vector>
#include "classes.h"

using namespace std;

// Methods of genome

void Genome::setRNA(string s)
{
    RNA = s;
}
void Genome::setDNA(string s1, string s2)
{
    DNA[0] = s1;
    DNA[1] = s2;
}
string Genome::getRNA()
{
    return RNA;
}
string Genome::getDNA1()
{
    return DNA[0];
}
string Genome::getDNA2()
{
    return DNA[1];
}
string complement(string s)
{

    string complement = "";
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == 'A')
        {
            complement += 'T';
        }
        else if (s[i] == 'C')
        {
            complement += 'G';
        }
        else if (s[i] == 'T')
        {
            complement += 'A';
        }
        else
        {
            complement += 'C';
        }
    }
    return complement;
}
void Genome::buildDNA()
{
    cout << RNA << endl
         << complement(RNA) << endl;
}
void Genome::SMutationRNA(char a, char b, int n)
{

    int q = n;
    for (int i = 0; i < RNA.size(); i++)
    {
        if (q == 0)
        {
            break;
        }
        if (RNA[i] == a)
        {
            RNA[i] = b;
            q--;
        }
    }
    cout << RNA << endl;
}
void Genome::SMutationDNA(char a, char b, int n)
{
    int q = n;
    for (int i = 0; i < DNA[0].size(); i++)
    {
        if (q == 0)
        {
            break;
        }
        if (DNA[0][i] == a)
        {
            DNA[0][i] = b;
            string w = complement(string(1, b));
            DNA[1][i] = w[0];
            q--;
        }
        else if (DNA[1][i] == a)
        {
            DNA[1][i] = b;
            string w = complement(string(1, b));
            DNA[1][i] = w[0];
            q--;
        }
    }
    cout << DNA[0] << endl
         << DNA[1] << endl;
}
void Genome::LMutationRNA(string s1, string s2)
{

    int q = RNA.find(s1);
    if (q != -1)
    {
        RNA.replace(q, s1.size(), s2);
    }
    else
    {
        cout << "Not found";
    }
}
void Genome::LMutationDNA(string s1, string s2)
{

    int q1 = DNA[0].size(), q2 = DNA[1].size();
    if (DNA[0].find(s1) != -1)
    {
        q1 = DNA[0].find(s1);
    }
    if (DNA[1].find(s1) != -1)
    {
        q2 = DNA[1].find(s1);
    }
    if (q1 < q2)
    {
        DNA[0].replace(q1, s1.size(), s2);
        string w = complement(s2);
        DNA[1].replace(q1, s1.size(), w);
    }
    else
    {
        DNA[1].replace(q2, s1.size(), s2);
        string w = complement(s2);
        DNA[0].replace(q2, s1.size(), w);
    }
    cout << DNA[0] << endl
         << DNA[1];
}
void Genome::reverseMutationRNA(string s)
{

    if (RNA.find(s) != -1)
    {
        int q = RNA.find(s);
        reverse(s.begin(), s.end());
        RNA.replace(q, s.size(), s);
        cout << RNA;
    }
    else
    {
        cout << "Not found";
    }
}
void Genome::reverseMutationDNA(string s)
{
    string str = s;
    reverse(str.begin(), str.end());
    Genome::LMutationDNA(s, str);
}

// Methods of cell

Cell::Cell(int n)
{
    this->n = n;
}
void Cell::addChromosome(string a, string b)
{
    Genome gene;
    gene.DNA[0] = a;
    gene.DNA[1] = b;
    chromosome.push_back(gene);
}
bool Cell::isComplement(char a, char b)
{
    if (a == 'A' && b == 'T')
    {
        return true;
    }
    if (a == 'T' && b == 'A')
    {
        return true;
    }

    if (a == 'G' && b == 'C')
    {
        return true;
    }

    if (a == 'C' && b == 'G')
    {
        return true;
    }

    return false;
}
void Cell::cellDeath()
{
    bool flag = false;
    int bbonds = 0;
    for (int j = 0; j < n; j++)
    {
        string a = chromosome[j].getDNA1();
        string b = chromosome[j].getDNA2();
        if (!isComplement(a[j], b[j]))
        {
            bbonds++;
        }
        if (bbonds > 5)
        {
            flag = true;
            break;
        }
    }

    if (flag)
    {
        delete this;
        return;
    }

    int AT = 0, GC = 0;
    for (int j = 0; j < n; j++)
    {
        string a = chromosome[j].getDNA1();
        string b = chromosome[j].getDNA2();
        if ((a[j] == 'A' && b[j] == 'T') || (a[j] == 'T' && b[j] == 'A'))
        {
            AT++;
        }
        if ((a[j] == 'C' && b[j] == 'G') || (a[j] == 'G' && b[j] == 'C'))
        {
            GC++;
        }
    }
    if (AT > 3 * GC)
    {
        delete this;
    }
}
void Cell::SMutation(char a, char b, int n, int m)
{
    chromosome[m].SMutationDNA(a, b, n);
}
void Cell::LMutation(string s1, string s2, int n, int m)
{
    if ((chromosome[n].getDNA1().find(s1) || chromosome[n].getDNA2().find(s1)) && (chromosome[m].getDNA1().find(s2) || chromosome[m].getDNA2().find(s2)))
        chromosome[n].LMutationDNA(s1, s2);
    chromosome[m].LMutationDNA(s2, s1);
}
void Cell::reverseMutation(string s, int n)
{
    chromosome[n].reverseMutationDNA(s);
}
bool is_palindrome(string s)
{
    int length = s.length();
    for (int i = 0; i < length / 2; i++)
    {
        if (s[i] == 'A' && s[length - i - 1] != 'T')
        {
            return false;
        }
        else if (s[i] == 'T' && s[length - i - 1] != 'A')
        {
            return false;
        }
        else if (s[i] == 'G' && s[length - i - 1] != 'C')
        {
            return false;
        }
        else if (s[i] == 'C' && s[length - i - 1] != 'G')
        {
            return false;
        }
    }
    return true;
}
void Cell::palindrome()
{

    for (int p = 0; p < n; p++)
    {
        for (int t = 0; t < 2; t++)
        {
            string s;
            if (t == 0)
            {
                s = chromosome[p].getDNA1();
            }
            else
            {
                s = chromosome[p].getDNA2();
            }
            for (int i = 0; i < s.length(); i++)
            {
                for (int j = i + 3; j <= n; j += 2)
                {
                    string substr = s.substr(i, j - i);
                    if (is_palindrome(substr))
                    {
                        cout << substr << endl;
                    }
                }
            }
        }
    }
}
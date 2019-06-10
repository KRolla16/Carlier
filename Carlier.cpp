#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
int l_zad, kolumny;
class Task
{
public:
	int r;
    int p;
    int q;
    int nrZad;

	Task()
	{
        r = 0;
        p = 0;
        q = 0;
		nrZad = 0;
	}
};

int find(vector<Task> dane, int nrZad)
{
	for (int i = 0; i < dane.size(); i++)
	{
		if (nrZad == dane[i].nrZad)
			return i;

	}
}

Task minimum(vector<Task> dane)
{
	int minimum = 10000;
	Task zad;
	for (int i = 0; i < dane.size(); i++)
	{
		if (minimum >= dane[i].r)
		{
			zad = dane[i];
			minimum = dane[i].r;
		}

	}
	return zad;
}

Task maximum(vector<Task> dane)
{
	Task zad;
	int maximum = 0;
	for (int i = 0; i < dane.size(); i++)
	{
		if (maximum < dane[i].q)
		{
			zad = dane[i];
			maximum = dane[i].q;
		}

	}
	return zad;
}



void wypisz(vector<Task> dane)
{
	for (int i = 0; i < l_zad; i++)
		cout << dane[i].nrZad << " ";
	cout << endl;
}

int cmax(vector<Task> dane)
{
	vector<int> C(l_zad);
	vector<int> S(C.size() + 1);
	S[0] = 0;
	S[1] = max(dane[0].r, 0 + 0);
	C[0] = S[1] + dane[0].p;
	for (int j = 2; j <= l_zad; j++)
	{
		S[j] = max(dane[j - 1].r, S[j - 1] + dane[j - 2].p);
		C[j - 1] = S[j] + dane[j - 1].p;
	}
	for (int i = 0; i < C.size(); i++)
	{
		C[i] = C[i] + dane[i].q;
	}
		vector<int>::iterator it = max_element(begin(C), end(C));
	int index = distance(C.begin(), it);
	return C[index];
}

int FindB(vector<Task> dane)
{
	vector<int> C(l_zad);
	vector<int> S(C.size() + 1);
	S[0] = 0;
	S[1] = max(dane[0].r, 0 + 0);
	C[0] = S[1] + dane[0].p;
	for (int j = 2; j <= l_zad; j++)
	{
		S[j] = max(dane[j - 1].r, S[j - 1] + dane[j - 2].p);
		C[j - 1] = S[j] + dane[j - 1].p;
	}
	for (int i = 0; i < C.size(); i++)
	{
		C[i] = C[i] + dane[i].q;
	}
	vector<int>::iterator it = max_element(begin(C), end(C));
	int b = distance(C.begin(), it);
	return b;
}

int FindA(vector<Task> dane)
{
	int a=0;
	int C=0;
	C =dane[0].r;
	for (int i = 1; i < dane.size(); i++)
	{
		C = C + dane[i-1].p;
		if (dane[i].r > C)
		{
			C = dane[i].r;
			a = i;
		}
		}
	return a;
}


vector<Task> Schrage(vector<Task> dane)
{
	int i = 1;
	vector<Task> kolejnosc;
	vector<Task> Ng(0);
	vector<Task> Nn(l_zad);
	Nn = dane;
	Task j;
	int t = minimum(Nn).r;
	while (Ng.size() != 0 || Nn.size() != 0)
	{
		while (Nn.size() != 0 && minimum(Nn).r <= t)
		{
			j = minimum(Nn);

			Ng.push_back(j);
			Nn.erase(Nn.begin() + find(Nn, j.nrZad));

		}
		if (Ng.size() == 0)
			t = minimum(Nn).r;
		else
		{
			j = maximum(Ng);
			Ng.erase(Ng.begin() + find(Ng, j.nrZad));
			kolejnosc.push_back(j);
			i++;
			t = t + j.p;
		}
	}
	return kolejnosc;
}

int FindC(vector<Task> dane,int a,int b)
{
	int c = -1;
	for (int i = a; i < b; i++)
		if (dane[i].q < dane[b].q)
		{
			c = i;
		}
				return c;
}


int SchragePMTN(vector<Task> dane)
{
	int cmax = 0;
	vector<Task> Ng(0);
	vector<Task> Nn(l_zad);
	Nn = dane;
	Task j;
	Task l;
	int t = 0;
	l.q = 9999;
	l.p = 0;

	while (Ng.size() != 0 || Nn.size() != 0)
	{
		while (Nn.size() != 0 && minimum(Nn).r <= t)
		{
			j = minimum(Nn);

			Ng.push_back(j);
			Nn.erase(Nn.begin() + find(Nn, j.nrZad));

			if (j.q > l.q)
			{
				l.p = t - j.r;
				t = j.r;

				if (l.p > 0)
				{
					Ng.push_back(l);
				}
			}
		}
		if (Ng.size() == 0)
			t = minimum(Nn).r;
		else
		{
			j = maximum(Ng);
			Ng.erase(Ng.begin() + find(Ng, j.nrZad));
			l = j;
			t = t + j.p;
			cmax = max(cmax, t + j.q);
		}
	}
	return cmax;
}
int FindR(vector<Task>dane,int b, int c)
{
    int minR = dane[c + 1].r;
    for (auto i = c + 2; i <= b; i++)
    {
        if (dane[i].r < minR)
            minR = dane[i].r;
    }

    return minR;
}
int FindQ(vector<Task>dane,int b, int c)
{
    int minQ = dane[c + 1].q;
    for (auto i = c + 2; i <= b; i++)
    {
        if (dane[i].q < minQ)
            minQ = dane[i].q;
    }

    return minQ;
}
int FindP(vector<Task> dane, int b, int c)
{
    int sum = 0;

    for (auto i = c + 1; i <= b; i++)
    {
        sum += dane[i].p;
    }

    return sum;
}
bool koniec=false;
int UB = 999999;
vector<Task> kolejnosc_koncowa;

vector<Task> Carlier(vector<Task> dane)
{
	if (koniec == false)
	{
		int a = FindA(Schrage(dane));
		int b = FindB(Schrage(dane));
		int c = FindC(Schrage(dane), a, b);
		int LB;
		int rPrim = 999999;
        int pPrim = 0;
        int qPrim = 999999;
		vector<Task> kolejnosc1= Schrage(dane);
		vector<Task> kolejnosc_pom=kolejnosc1;
		int U = cmax(kolejnosc1);
		if (U < UB)
		{
			UB = U;
			kolejnosc_koncowa = kolejnosc1;
		}
		if (c == -1)
		{
		    cout << UB << endl;
			koniec = true;
			return kolejnosc_koncowa;
		}
		rPrim = FindR(kolejnosc1,b,c);
		qPrim = FindQ(kolejnosc1,b,c);
		pPrim = FindP(kolejnosc1,b,c);
		kolejnosc1[c].r = max(kolejnosc1[c].r, (rPrim + pPrim));
		LB = SchragePMTN(kolejnosc1);

		if (LB < UB)
		{
			Carlier(kolejnosc1);
		}
		kolejnosc1= kolejnosc_pom;
		kolejnosc1[c].q = max(kolejnosc1[c].q, (qPrim + pPrim));
		LB = SchragePMTN(kolejnosc1);
		if (LB < UB)
		{
			Carlier(kolejnosc1);
		}
		kolejnosc1= kolejnosc_pom;
	}
	return kolejnosc_koncowa;
}


int main()
{
	ifstream data("data.txt");
	data >> l_zad;
	data >> kolumny;
	vector<Task> dane(l_zad);
	for (int i = 0; i < l_zad; i++)
	{
		dane[i].nrZad = i + 1;
		data >> dane[i].r;
		data >> dane[i].p;
		data >> dane[i].q;
	}
vector<Task>wynik = Carlier(dane);
	cout << "cmax: ";
    cout << cmax(wynik)<<endl;
    cout << "kolejnosc : "<<endl;
    for(int i = 0;i<l_zad;i++)
    {
        cout<<wynik[i].nrZad<<" ";
    }
    cout << endl;
}
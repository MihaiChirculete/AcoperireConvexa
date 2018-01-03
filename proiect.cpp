#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "utils/renderer.h"

using namespace std;

float verificareOrientare(Punct A1, Punct A2, Punct A3)		//returneaza numar negativ daca e contra ceasornic, 0 daca sunt coliniare si pozitiv pentru ceasornic
{
	return (A2.get_y() - A1.get_y())*(A3.get_x() - A2.get_x()) - (A3.get_y() - A2.get_y())*(A2.get_x() - A1.get_x());
}

int citire(Punct* Puncte, ifstream& input, int n)
{
	float x, y;
	for(int i = 0; i < n ; i++)
	{
		if(input >> x >> y)
			Puncte[i].initializare(x, y);
		else
		{
			cout << "Eroare la citirea punctelor! Prea putine puncte introduse!(n prea mic)\n";
			return -1;
		}
	}

	int aux;

	input >> aux;                  //pentru a verifica EOF

	if(input.eof())
	{
		return 1;
	}
	else
	{
		cout << "Eroare la citirea punctelor! Prea multe puncte introduse!(n prea mare)\n";
		return -1;
	}
}

bool comp (Punct A, Punct B)			//vrem sa le ordonam dupa X
{
	if(A.get_x() == B.get_x())
		return A.get_y() < B.get_y();			//in cazul in care X egali, ordonam dupa Y
	else
		return A.get_x() < B.get_x();
}

void distribuireZone(Punct* Puncte, vector<Punct>& Zona1, vector<Punct>& Zona2, int n)
{
	for(int i = 0; i < n; i++)
	{
		if(Puncte[i].get_y() >= 0)
			Zona1.push_back(Puncte[i]);
		else
			Zona2.push_back(Puncte[i]);
	}
}

void gasireAcoperire(vector<Punct> Zona1, vector<Punct> Zona2, vector<Punct>& Acoperire)
{
	vector<Punct> Acoperire1, Acoperire2;      //Acoperire1 pt Zona1 si Acoperire2 pt Zona2

	Acoperire1.push_back(Zona1[0]);
	Acoperire1.push_back(Zona1[1]);

	Acoperire2.push_back(Zona2[0]);
	Acoperire2.push_back(Zona2[1]);

	for(int i = 2; i < Zona1.size(); i++)
	{
		if(Acoperire1.size() >= 2)
		{
			if(verificareOrientare(Acoperire1[Acoperire1.size() - 2], Acoperire1[Acoperire1.size() - 1], Zona1[i]) < 0)
			{
				Acoperire1.erase(Acoperire1.end() - 1);
				i--;
				continue;
			}
			else
			{
				if(verificareOrientare(Acoperire1[Acoperire1.size() - 2], Acoperire1[Acoperire1.size() - 1], Zona1[i]) == 0)
					Acoperire1.erase(Acoperire1.end() - 1);
			}
		}
		Acoperire1.push_back(Zona1[i]);
	}

	for(int i = 2; i < Zona2.size(); i++)
	{
		if(Acoperire2.size() >= 2)
		{
			if(verificareOrientare(Acoperire2[Acoperire2.size() - 2], Acoperire2[Acoperire2.size() - 1], Zona2[i]) > 0)
			{
				Acoperire2.erase(Acoperire2.end() - 1);
				i--;
				continue;
			}
			else
			{
				if(verificareOrientare(Acoperire2[Acoperire2.size() - 2], Acoperire2[Acoperire2.size() - 1], Zona2[i]) == 0)
					Acoperire2.erase(Acoperire2.end() - 1);
			}
		}
		Acoperire2.push_back(Zona2[i]);
	}


	for(int i = 0; i < Acoperire1.size(); i++)
		Acoperire.push_back(Acoperire1[i]);
	for(int i = Acoperire2.size() - 1; i >= 0; i--)
		Acoperire.push_back(Acoperire2[i]);

	for(int i = 0; i < Acoperire.size(); i++)
		cout << Acoperire[i] << endl;

}

int main(int argc, char **argv)
{
	Acoperire.clear();

	int n;

	if(argc > 1)
	{
		scale = atof(argv[1]);
	}

	ifstream input("input.in");

	
	if(!input.is_open())
	{
		cout << "Eroare la citirea fisierului \"input.in\"!\n";
		return -1;
	}
	

	input >> n;

	Punct* Puncte = new Punct[n];

	if(citire(Puncte, input, n) == -1)
	{
		return -1;
	}

	sort(Puncte, Puncte + n, comp);

	vector<Punct> Zona1, Zona2;					//Zona 1 = toate punctele cu Y >=0, Zona 2 = celelalte

	distribuireZone(Puncte, Zona1, Zona2, n);

	gasireAcoperire(Zona1, Zona2, Acoperire);
	

	Renderer* rend = new Renderer(argc, argv, 1366, 768, 0, 0, "Acoperire Convexa");
	rend->init();

	return 0;
}
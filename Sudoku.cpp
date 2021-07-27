#include<iostream>
#include<array>
#include<vector>
#include<map>
#include<set>
#include<sstream>
#include<fstream>
#include<time.h>
#include <stdlib.h> 
#include <algorithm>
#include <unordered_map>

using namespace std;



void vprint_Sudoku(std::vector<std::vector<int> > v) {
	int i, j;
	int brojac = 0, brojac2 = 0;

	for (i = 0; i < 9; i++) {
		brojac2++;
		if (brojac2 == 4 || brojac2 == 7)
			std::cout << "------+------+------" << std::endl;
		for (j = 0;j < 9;j++) {
			std::cout << v[i][j] << ' ';
			brojac++;
			if (brojac == 3 || brojac == 6) {
				std::cout << '|';
			}
			if (brojac > 8) {
				std::cout << std::endl;
				brojac = 0;
			}
		}
	}

}
// pretvori liniju teksta u vektor
void linija_u_polje(std::string linija, std::vector<int> &v) {
	for (int k = 0; linija[k] != '\0'; k++) {
		//std::cout << sLine[k];
		int pom = linija[k] - '0';
		v.push_back(pom);
		//std::cout << pom;
	}
}

//pretvori vektor u matricu 9*9
void polje_u_sudoku(std::vector<int> field, std::vector<std::vector<int> > &v) {
	int k = 0;
	for(int i = 0; i < 9; i++ )
		for (int j = 0; j < 9; j++) {
			v[i][j] = field[k];
			k++;
		}
}
// moze li n na to polje po liniji
int in_line(std::vector<std::vector<int> >& v, int n, int i,int  j) {
	if (v[i][j] != 0)
		return 0;
	for (int k = 0; k < 8; k++) {
		if (v[i][k] == n)
			return 0;
	}
	return 1; 
}
// moze li n na to polje po stupcu
int in_column(std::vector<std::vector<int> >& v, int n, int i, int  j) {
	if (v[i][j] != 0)
		return 0;
	for (int k = 0; k < 8; k++) {
		if (v[k][j] == n)
			return 0;
	}
	return 1;
}

// moze li n na to polje u kutiji
int check_box(std::vector<std::vector<int> >& v, int n, int i, int  j) {
	int x, y;
		x = i / 3 * 3;
		y = j / 3 * 3;
		int k, l;
		for (k = 0; k < 3; k++)
			for (l = 0; l < 3; l++) {
				if (v[x + k][y + l] == n)
					return 0;
			}




	return 1;
}

// u skup stavi sve moguće vrijednosti
void possible_value(std::vector<std::vector<int> >& v, int i, int  j, std::set<int> &vrijednosti) {
	for(int k = 1; k < 10; k++){
		
		if (!in_column(v, k, i, j))
			continue;
		if (!in_line(v, k, i, j))
			continue;
		if (!check_box(v, k, i, j))
			continue;
		vrijednosti.insert(k);
	}
}
int main() {
	//srand(time(NULL));



	std::fstream file_stream;
	std::string filename = "C:\\Users\\Borna\\Desktop\\Sudoku.txt";
	file_stream.open(filename);
	

	
// ostaci iz proslosti mozda neki jos trebaju :S
	int i, j;
	int brojac = 0;
	int brojac2 = 0;
	int polje[81];
	
	






	//uzmi jednu liniju iz filea
		std::string sLine;
		getline(file_stream, sLine);
	

	std::vector<int> field;
	

	linija_u_polje(sLine, field);
	

	//incijalizacija vektora za spremanje sudokua
	std::vector<std::vector<int> > v;
	v.resize(9);
	for (i = 0;i < 9; i++) {
		v[i].resize(9);
	}
	  
	polje_u_sudoku(field, v);

	vprint_Sudoku(v);
	
	
	//test
	if (check_box(v, 2, 0, 2)) {
		std::cout << "U kutiji moze 2 na toj poziciji" << std::endl;
	}
	
//test mogućih vrijednosti .. prebacit iz skupa u bitove
	std::set<int> skup;

	possible_value(v, 2, 0, skup);
	
	for (auto it = skup.begin(); it !=
		skup.end(); ++it)
		cout << ' ' << *it;
	return 0;
}



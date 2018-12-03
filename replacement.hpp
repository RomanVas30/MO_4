#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <clocale>

class Replacement {
public:
	Replacement(){}
	void normalization(bool);
	void acceptable_alternatives(unsigned criterion);
	void print_Pareto(unsigned, unsigned);
	void union_value();
	std::ifstream file;
	~Replacement() {
		file.close();
		for (unsigned i = 0; i < alternatives; ++i)
			delete[] table[i];
		delete[] table;
	}
private:
	double** table;
	double** norm_table;
	std::vector<double> marks;
	std::vector<double> expert_marks;
	std::vector<unsigned> low_marks_or_sum;
	std::vector<unsigned> suitable_alternatives;
	unsigned alternatives;
	unsigned criterions;
	void input_value();
	void print_alternatives(unsigned);
};
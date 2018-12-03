#include <iostream>
#include <thread>
#include <chrono>

#include "replacement.hpp"

int main() {
	setlocale(LC_CTYPE, "rus");
	unsigned number = 0; 
	bool end_of_the_program = false;
	while (!end_of_the_program) {
		std::cout << "�������� ����� �������: " << std::endl;
		std::cout << "1. ��������� ������ ����� ��������� � ������������� ���." << std::endl;
		std::cout << "2. ������ ��������� �������������." << std::endl;
		std::cout << "3. ������������ � ������� ��������� �����." << std::endl;
		std::cout << "4. ����������� � ����������� ���������." << std::endl;
		std::cout << "5. ����� ������� ��������." << std::endl;
		std::cout << "0. �����." << std::endl;
		std::cin >> number;
		switch (number)
		{
		case 1: {
			Replacement replace;
			replace.normalization(true);
		}break;
		case 2: {
			unsigned criterion;
			std::cout << "������� ����� �������� ��������: ";
			std::cin >> criterion;
			Replacement replace;
			replace.normalization(false);
			try {
				replace.acceptable_alternatives(criterion - 1);
			}
			catch (std::exception const& e)
			{
				std::cout << "Error: " << e.what() << std::endl;
			}
		}break;
		case 3: {
			unsigned first;
			unsigned second;
			std::cout << "������� ������ ��������: ";
			std::cin >> first;
			std::cout << "������� ������ ��������: ";
			std::cin >> second;
			Replacement replace;
			replace.normalization(false);
			replace.print_Pareto(first - 1, second - 1);

		}break;
		case 4: {
			Replacement replace;
			replace.normalization(false);
			replace.union_value();
		}break;
		case 5: {

		}break;
		default:
			end_of_the_program = true;
			break;
		}
	}
	std::cout << "�� �������:)" << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
}
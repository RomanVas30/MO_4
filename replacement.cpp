#include "replacement.hpp"

void Replacement::input_value() {
	file.open("value.txt");
	file >> alternatives;
	file >> criterions;
	table = new double*[alternatives];
	for (unsigned i = 0; i < alternatives; i++)
		table[i] = new double[criterions];
	for (unsigned i = 0; i < alternatives; i++)
		for (unsigned j = 0; j < criterions; j++)
			file >> table[i][j];
	for (unsigned i = 0; i < criterions; ++i) {
		unsigned tmp;
		file >> tmp;
		marks.push_back(tmp);
	}
}

void Replacement::normalization(bool number) {
	input_value();
	unsigned sum_criterion = 0;
	for (unsigned i = 0; i < criterions; ++i)
		sum_criterion += marks[i];
	if (number)
		std::cout << "Нормализованный вектор: " << std::endl;
	for (unsigned i = 0; i < criterions; ++i) {
		expert_marks.push_back(marks[i] / sum_criterion);
		if (number)
			std::cout << marks[i] / sum_criterion << std::endl;
	}
}

void Replacement::acceptable_alternatives(unsigned best_criterion) {
	for (unsigned i = 0; i < criterions; ++i) {
		unsigned tmp;
		file >> tmp;
		low_marks_or_sum.push_back(tmp);
	}
	bool valid = true;
	for (unsigned i = 0; i < alternatives; ++i) {
		for (unsigned j = 0; j < criterions; ++j) {
			if (table[i][j] >= low_marks_or_sum[j])
				continue;
			else {
				valid = false;
				break;
			}
		}
		if (valid) suitable_alternatives.push_back(i);
		valid = true;
	}
	if (suitable_alternatives.size() == 0) throw std::runtime_error{ "!" };
	print_alternatives(best_criterion);
}

void Replacement::print_alternatives(unsigned best_criterion) {
	std::cout << "Приемлемые альтернативы: " << std::endl;
	for (unsigned i = 0; i < suitable_alternatives.size(); ++i)
		std::cout << suitable_alternatives[i] + 1 << " ";
	std::cout << std::endl;
	/*union_value(false);
	std::cout << "Объединенные критерии альтернатив: " << std::endl;
	for (unsigned i = 0; i < marks.size(); ++i)
		std::cout << marks[i] << std::endl;*/
	unsigned max_value = table[suitable_alternatives[0]][best_criterion];
	unsigned max_criterion = suitable_alternatives[0];
	for (unsigned i = 1; i < suitable_alternatives.size(); ++i)
		if (table[suitable_alternatives[i]][best_criterion] > max_value) {
			max_value = table[suitable_alternatives[i]][best_criterion];
			max_criterion = suitable_alternatives[i];
		}
	std::cout << "Лучшая альтернатива: " << max_criterion + 1 << std::endl;

}

void Replacement::print_Pareto(unsigned first, unsigned second) {
	unsigned point_utopia_x = 0;
	unsigned point_utopia_y = 0;
	for (unsigned i = 0; i < alternatives; ++i) {
		if (table[i][first] > point_utopia_x)
			point_utopia_x = table[i][first];
		if (table[i][second] > point_utopia_y)
			point_utopia_y = table[i][second];
	}
	int distance_x = 0;
	int distance_y = 0;
	for (unsigned i = 0; i < alternatives; ++i) {
		distance_x = point_utopia_x - table[i][first];
		distance_y = point_utopia_y - table[i][second];
		suitable_alternatives.push_back(abs(distance_x) + abs(distance_y));
		std::cout << "Расстояние по Манхеттену до " << i + 1 << "-ой альтернативы: " << suitable_alternatives[i] << std::endl;
	}
	unsigned min_distance = suitable_alternatives[0];
	for (unsigned i = 0; i < alternatives; ++i)
		if (min_distance > suitable_alternatives[i])
			min_distance = suitable_alternatives[i];
	std::cout << "Оптимальная альтернатива по Парето: " << min_distance << std::endl;
}

void Replacement::union_value(bool number) {
	norm_table = new double*[alternatives];
	for (unsigned i = 0; i < alternatives; i++)
		norm_table[i] = new double[criterions];
	for (unsigned i = 0; i < alternatives; i++)
		for (unsigned j = 0; j < criterions; j++)
		    norm_table[i][j] = 0;
	unsigned sum = 0;
	for (unsigned j = 0; j < criterions; ++j) {
		for (unsigned i = 0; i < alternatives; ++i)
			sum += table[i][j];
		low_marks_or_sum.push_back(sum);
		sum = 0;
	}
	for (unsigned j = 0; j < alternatives; ++j)
		for (unsigned i = 0; i < criterions; ++i)
			norm_table[i][j] = table[i][j] / low_marks_or_sum[j];
	for (unsigned i = 0; i < alternatives; ++i) {
		marks[i] = 0;
		for (unsigned j = 0; j < criterions; ++j)
			marks[i] += norm_table[i][j] * expert_marks[j];
	}
	for (unsigned i = 0; i < alternatives; ++i)
			delete[] norm_table[i];
		delete[] norm_table;
	if (number)
	print_union_value();
}

void Replacement::print_union_value() {
	for (unsigned i = 0; i < alternatives; ++i) {
			std::cout << marks[i] << std::endl;
	}
}

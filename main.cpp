#define _CRT_SECURE_NO_WARNINGS
#include "Parallelogram.h"
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <vector>

using namespace std;

bool is_all_ch_allowable(char *, const char *);

void remove_ch(char *, char);

void swap_ch(char *, char, char);

void main() {
	setlocale(LC_ALL, "ru");
	srand(time(0));
	const char DIGITS[] = "0123456789,."; 
	const double EPS = 0.00000001;
	char * params_string = getenv("QUERY_STRING"), *tmp_str = strtok(params_string, ";");
	bool invalid_input = false;
	unsigned short int number_of_p = 0, op_index = 0, p_index = 0;
	double oper_param = 0, first_side = 0, second_side = 0, diagonal = 0;
	vector<char *> *params_vector = new vector<char *>();
	vector<parallelogram *> *parall_vector = new vector<parallelogram *>();
	printf("Content-Type: text/html\r\n\r\n");
	printf("<html> <head>\n");
	printf("<title>Parallelograms</title>\n");
	printf("</head>\n");
	printf("<body>\n");
	while (tmp_str) {
		params_vector->push_back(tmp_str);
		tmp_str = strtok(NULL, ";");
	}
	for (int str_i = 0; str_i < params_vector->size(); str_i++) {
		remove_ch(params_vector->at(str_i), ' ');
		invalid_input = !(is_all_ch_allowable(params_vector->at(str_i), DIGITS)) || !strcmp(params_vector->at(str_i), "") || !params_vector->at(str_i);
		if (!invalid_input) {
			tmp_str = strtok(params_vector->at(str_i), ",");
			op_index = strtol(tmp_str, NULL, 10);
			tmp_str = strtok(NULL, ",");
			switch (op_index) {
			case 1:
				if (!tmp_str) {
					invalid_input = true;
					break;
				}
				swap_ch(tmp_str, ',', '.');
				first_side = strtod(tmp_str, NULL);
				tmp_str = strtok(NULL, ",");
				if (!tmp_str) {
					invalid_input = true;
					break;
				}
				swap_ch(tmp_str, ',', '.');
				second_side = strtod(tmp_str, NULL);
				tmp_str = strtok(NULL, ",");
				if (!tmp_str) {
					invalid_input = true;
					break;
				}
				swap_ch(tmp_str, ',', '.');
				diagonal = strtod(tmp_str, NULL);
				tmp_str = strtok(NULL, ",");
				if (first_side + second_side > diagonal && first_side + diagonal > second_side && second_side + diagonal > first_side && !tmp_str)
					parall_vector->push_back(new parallelogram(first_side, second_side, diagonal));
				else {
					invalid_input = true;
					break;
				}
				break;
			case 2:
				number_of_p = strtol(tmp_str, NULL, 10);
				for (int i = 0; i < number_of_p; i++) {
					first_side = rand() % 101 + rand() % 1001 / 1000.0;
					second_side = rand() % 101 + rand() % 1001 / 1000.0;
					if (ceil(max(first_side, second_side)) < floor(first_side + second_side)) {
						diagonal = rand() % (int)(floor(first_side + second_side) - ceil(max(first_side, second_side)) + 1) + ceil(max(first_side, second_side));
						diagonal += fabs(diagonal - floor(first_side + second_side)) < EPS ? -rand() % 1001 / 1000.0 : rand() % 1001 / 1000.0;
					}
					else
						diagonal = (max(first_side, second_side) + first_side + second_side) / 2;
					parall_vector->push_back(new parallelogram(first_side, second_side, diagonal));
				}
				break;
			case 3:
				if (!tmp_str) {
					invalid_input = true;
					break;
				}
				p_index = strtol(tmp_str, NULL, 10);
				tmp_str = strtok(NULL, ",");
				if (!tmp_str || p_index >= parall_vector->size() || p_index < 0) {
					invalid_input = true;
					break;
				}
				swap_ch(tmp_str, ',', '.');
				oper_param = strtod(tmp_str, NULL);
				tmp_str = strtok(NULL, ",");
				if (tmp_str) {
					invalid_input = true;
					break;
				}
				(*parall_vector)[p_index]->size_variation(oper_param, 0);
				break;
			case 4:
				if (!tmp_str) {
					invalid_input = true;
					break;
				}
				p_index = strtol(tmp_str, NULL, 10);
				tmp_str = strtok(NULL, ",");
				if (!tmp_str || p_index >= parall_vector->size() || p_index < 0) {
					invalid_input = true;
					break;
				}
				swap_ch(tmp_str, ',', '.');
				oper_param = strtod(tmp_str, NULL);
				tmp_str = strtok(NULL, ",");
				if (tmp_str) {
					invalid_input = true;
					break;
				}
				(*parall_vector)[p_index]->size_variation(oper_param, 1);
				break;
			case 5:
				if (tmp_str) {
					invalid_input = true;
					break;
				}
				if (parall_vector->size()) {
					printf("<table cellpadding=\"10\" cellspacing=\"0\" border = \"1\">");
					printf("<tr>%s</tr><tr>%s%s%s%s%s%s%s%s%s</tr>",
						"<td colspan = \"9\">Список параллелограммов</td>",
						"<th>Номер параллелограмма</th>",
						"<th>Первая сторона</th>",
						"<th>Вторая сторона</th>",
						"<th>Первая диагональ</th>",
						"<th>Вторая диагональ</th>",
						"<th>Высота на первую сторону</th>",
						"<th>Высота на вторую сторону</th>",
						"<th>Квадратный корень периметра</th>",
						"<th>Квадратный корень площади</th>");
					for (int i = 0; i < parall_vector->size(); i++) {
						printf("<tr>");
						printf("<th>%d</th><th>%f</th><th>%f</th><th>%f</th><th>%f</th><th>%f</th><th>%f</th><th>%f</th><th>%f</th>", i,
							parall_vector->at(i)->get_first_side(), parall_vector->at(i)->get_second_side(), parall_vector->at(i)->get_first_diagonal(),
							parall_vector->at(i)->get_second_diagonal(), parall_vector->at(i)->get_height_on_first_side(), parall_vector->at(i)->get_height_on_second_side(),
							parall_vector->at(i)->perimeter_sqrt(), parall_vector->at(i)->area_sqrt());
						printf("</tr>");
					}
					printf("<p>\r\n</p>");
				}
				else
					printf("<p>Список параллелограммов пуст.</p>");
				break;
			case 6:
				if (!tmp_str) {
					invalid_input = true;
					break;
				}
				p_index = strtol(tmp_str, NULL, 10);
				tmp_str = strtok(NULL, ",");
				if (tmp_str || p_index >= parall_vector->size() || p_index < 0) {
					invalid_input = true;
					break;
				}
				parall_vector->erase(parall_vector->begin() + p_index);
				break;
			case 7:
				if (tmp_str) {
					invalid_input = true;
					break;
				}
				parall_vector->clear();
				break;
			default:
				invalid_input = true;
				break;
			}
		}
		if (invalid_input)
			printf("<h1>ОШИБКА!!</h1><p>Один, или несколько параметров были введены неверно в наборе параметров №%d.</p>", str_i + 1);
	}
	printf("</body> </html>\n");
}

bool is_all_ch_allowable(char * str, const char * allowable_ch) {
	for (int i = 0; i < strlen(str); i++)
		if (!strchr(allowable_ch, str[i]))
			return false;
	return true;
}

void remove_ch(char *str, char ch_del) {
	char *buff = new char[strlen(str)];
	_strset(buff, 0);
	while (strchr(str, ch_del)) {
		strcpy(buff, strchr(str, ch_del) + 1);
		_strset(strchr(str, ch_del), 0);
		strcat(str, buff);
	}
}

void swap_ch(char * str, char new_char, char old_char) {
	for (int i = 0; i < strlen(str); i++)
		if (str[i] == old_char)
			str[i] = new_char;
}


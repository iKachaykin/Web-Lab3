#define _CRT_SECURE_NO_WARNINGS
#include "Parallelogram.h"
#include <ctime>
#include <algorithm>
#include <cstdlib>
using namespace std;

bool is_all_ch_allowable(char *, const char *);

void remove_ch(char *, char);

void main() {
	setlocale(LC_ALL, "ru");
	srand(time(0));
	const char DIGITS[] = "0123456789,."; 
	const double EPS = 0.00000001;
	char * params_string = getenv("QUERY_STRING");
	bool invalid_input = false;
	unsigned short int number_of_p = 0, op_index = 0, p_index = 0, num_of_comas = 0, num_of_dots = 0;
	double oper_param = 0, first_side = 0, second_side = 0, diagonal = 0;
	printf("Content-Type: text/html\r\n\r\n");
	printf("<html> <head>\n");
	printf("<title>Parallelograms</title>\n");
	printf("</head>\n");
	printf("<body>\n");
	for (int i = 0; i < strlen(params_string); i++)
		if (params_string[i] == ',')
			num_of_comas++;
	for (int i = 0; i < strlen(params_string); i++)
		if (params_string[i] == '.')
			num_of_dots++;
	remove_ch(params_string, ' ');
	invalid_input = !(is_all_ch_allowable(params_string, DIGITS)) || !strcmp(params_string, "") || !params_string || num_of_comas != 2 && num_of_comas != 3 || num_of_dots != 1 && num_of_dots != 0;
	if (!invalid_input) {
		char * tmp_str = strtok(params_string, ",");
		number_of_p = strtol(tmp_str, NULL, 10);
		parallelogram ** p_arr = new parallelogram*[number_of_p];
		for (int i = 0; i < number_of_p; i++) {
			first_side = rand() % 101 + rand() % 1001 / 1000.0;
			second_side = rand() % 101 + rand() % 1001 / 1000.0;
			if (ceil(max(first_side, second_side)) < floor(first_side + second_side)) {
				diagonal = rand() % (int)(floor(first_side + second_side) - ceil(max(first_side, second_side)) + 1) + ceil(max(first_side, second_side));
				diagonal += fabs(diagonal - floor(first_side + second_side)) < EPS ? -rand() % 1001 / 1000.0 : rand() % 1001 / 1000.0;
			}
			else 
				diagonal = (max(first_side, second_side) + first_side + second_side) / 2;
			p_arr[i] = new parallelogram(first_side, second_side, diagonal);
			printf("<p>Параллелограм №%d - (первая сторона, вторая сторона, диагональ):%s</p>", i, p_arr[i]->to_string().c_str());
		}
		tmp_str = strtok(NULL, ",");
		p_index = strtol(tmp_str, NULL, 10);
		invalid_input = p_index >= number_of_p;
		if (!invalid_input) {
			tmp_str = strtok(NULL, ",");
			op_index = strtol(tmp_str, NULL, 10);
			tmp_str = strtok(NULL, ",");
			switch (op_index)
			{
			case 1:
				if (tmp_str) {
					for (int i = 0; i < strlen(tmp_str); i++) {
						if (tmp_str[i] == '.') {
							tmp_str[i] = ',';
							break;
						}
					}
					oper_param = strtod(tmp_str, NULL);
					p_arr[p_index]->size_variation(oper_param, 0);
					printf("<p>Увеличили параллелограм №%d на %f</p><p>Измененный список параллелограммов:</p>", p_index, oper_param);
					for (int i = 0; i < number_of_p; i++)
						printf("<p>Параллелограм №%d - (первая сторона, вторая сторона, диагональ):%s</p>", i, p_arr[i]->to_string().c_str());
				}
				else
					invalid_input = true;
				break;

			case 2:
				if (tmp_str) {
					for (int i = 0; i < strlen(tmp_str); i++) {
						if (tmp_str[i] == '.') {
							tmp_str[i] = ',';
							break;
						}
					}
					oper_param = strtod(tmp_str, NULL);
					p_arr[p_index]->size_variation(oper_param, 1);
					printf("<p>Уменьшили параллелограм №%d на %f</p><p>Измененный список параллелограммов:</p>", p_index, oper_param);
					for (int i = 0; i < number_of_p; i++)
						printf("<p>Параллелограм №%d - (первая сторона, вторая сторона, диагональ):%s</p>", i, p_arr[i]->to_string().c_str());
				}
				else
					invalid_input = true;
				break;
			case 3:
				printf("<p>Квадратный корень периметра %d-го параллелограмма: %f</p>", p_index, p_arr[p_index]->perimeter_sqrt());
				break;
			case 4:
				printf("<p>Квадратный корень площади %d-го параллелограмма: %f</p>", p_index, p_arr[p_index]->area_sqrt());
				break;
			case 5:
				printf("<p>Вторая диагональ %d-го параллелограмма: %f</p>", p_index, p_arr[p_index]->get_diagonal());
				break;
			case 6:
				printf("<p>Высота на первую сторону %d-го параллелограмма: %f</p>", p_index, p_arr[p_index]->get_height_on_first_side());
				break;
			case 7:
				printf("<p>Высота на вторую сторону %d-го параллелограмма: %f</p>", p_index, p_arr[p_index]->get_height_on_second_side());
				break;
			default:
				invalid_input = true;
				break;
			}
		}
	}
	if (invalid_input)
		printf("<h1>ОШИБКА!!</h1><p>Один, или несколько параметров были введены неверно.</p>");
	printf("</body> </html>\n");
}

bool is_all_ch_allowable(char * str, const char * allowable_ch) {
	for (int i = 0; i < strlen(str); i++)
		if (!strchr(allowable_ch, str[i]))
			return false;
	return true;
}

void remove_ch(char * str, char ch_del) {
	char *buff = new char[strlen(str)];
	_strset(buff, 0);
	while (strchr(str, ch_del)) {
		strcpy(buff, strchr(str, ch_del) + 1);
		_strset(strchr(str, ch_del), 0);
		strcat(str, buff);
	}
}

/*Задание 4. Оценка результатов игры в крестики-нолики
Что нужно сделать
Петя и Вася играли в крестики-нолики и не стёрли результаты своей игры. Теперь перед вами табличка 3 × 3, которая осталась после их поединка.
Вы хотите понять, выиграл ли кто-то из них или они не доиграли.
На вход программе даётся три строки, кодирующие верхнюю, среднюю и нижнюю строчки игрового поля.
Крестик обозначается символом X (английская заглавная буква X), нолик — символом O (заглавная английская буква O), пустая клетка — точкой.
Если ввод некорректен, то есть такая таблица не могла получиться в ходе настоящей игры, то надо написать в ответ слово Incorrect.
Если таблица корректна и выиграли крестики, то нужно вывести в ответ слова Petya won, если нолики — Vanya won, иначе (то есть они не доиграли или сыграли вничью) надо написать Nobody.

Примеры

X.. 
OXO 
OOO 
Ответ: Incorrect (потому что ноликов в конце игры не может быть больше, чем крестиков).

X.. 
.X. 
OO. 
Ответ: Nobody (потому что они не доиграли).

XXO 
OOX 
XOX 
Ответ: Nobody (потому что это ничья).

XO. 
XO. 
X.O 
Ответ: Incorrect (крестики уже победили, и ноликов не может быть столько же).

OX. 
XOX 
X.O 
Ответ: Incorrect (потому что нолики выиграли за три хода, и на поле за это время не могло успеть появиться четыре крестика).

..X 
OX. 
X.O 
Ответ: Petya won.

0.. 
... 
... 
Ответ: Incorrect (потому что допускаются только символы X, O и точка, а цифра 0 не является допустимым символом).

Рекомендации
Активно используйте оператор индексации строки str[i], но помните, что индексы начинаются с нуля, а не с единицы.
Чтобы обращаться к элементам игрового поля, стоит написать отдельную функцию получения элемента поля по его координатам (x, y). В таком случае часть алгоритмов поиска победителя можно обобщить.
Функции проверки поля на корректность можно отделить от функций и алгоритмов проверки победителя.
При достаточной модульности функций некоторые операции можно реализовать через уже существующие процедуры.
К примеру, если уже есть проверка победителя в строке и имеется функция получения колонки по индексу, то функцию поиска победителя в колонке можно реализовать через обе процедуры.
Проход по диагонали поля можно осуществить в цикле, используя счётчик цикла в качестве обоих координат элемента. Для второй диагонали нужно обратить одну из координат (2 − x или 2 − y).
Общие условия некорректности поля таковы:
выявлено несколько победителей одновременно;
нолики победили, а крестиков больше, чем ноликов;
крестики победили, а ноликов столько же или больше;
нолики и крестики победили несколько раз;
на поле есть невалидные символы.
Для упрощения лучше создать отдельные функции для проверки победителя в строке или столбце, которые на вход принимают строку, а на выходе выдают символ победителя. То есть ‘X’, ‘O’ или ‘.’*/

#include <iostream>
#include <string>
#include <algorithm>

// функция ввода входных данных
std::string enter_line (int n) {
	std::string str;
	std::cout << "Enter the line number " << n << ": ";
	std::cin >> str;
	while (str.length() != 3) {
		std::cout << "The length of the string must be 3 characters. Enter again: ";
		std::cin >> str;
	}
	return str;
}

//фунция получения символа по его координатам
char get_symbol_by_coordinates(std::string str, int x, int y) {
	int position = ((y - 1) * 3 + x) - 1;
	return str[position];
}

//функция определения победителя в строке
char who_won_in_string(std::string str) {
	if (std::search_n(str.cbegin(), str.cend(), 3, 'X') != str.cend()) {
		return 'X';
	}
	if (std::search_n(str.cbegin(), str.cend(), 3, 'O') != str.cend()) {
		return 'O';
	}
}

//функция получения линии по её номеру
std::string get_line(std::string str, int n) {
	n = 3 * --n;
	return str.substr(n,3);
}

//функция получения колонки по её номеру
std::string get_column(std::string str, int n) {
	std::string result;
	n--;
	for (int i = 0; i <= 6; i += 3) {
		result += str[n + i];
	}
	
	return  result;
}

//функция проверки игрового поля
bool checking_playing_field(std::string str) {
	
	//проверяем что все символы допустимые
	std::string correct = "XO.";

	for (int i = 0; i < str.length() - 1; i++) {
		if (correct.find(str[i]) == std::string::npos) {
			return false;
		}
	}

return true;
}

//функция определения победителя
void who_won(std::string str) {
	int Xwon = 0;
	int Owon = 0;
	// подсчитываем количество X и О
	int XChar = std::count(str.begin(), str.end(), 'X');
	int OChar = std::count(str.begin(), str.end(), 'O');
	
	std::string diagonal1 = "";
	std::string diagonal2 = "";

	for (int i = 1; i <= 3; i++) {
		//получаем линию и колонку
		std::string line = get_line(str,i);
		std::string column = get_column(str, i);

		//опрделяем есть ли победитель в линии или колонке
		if (who_won_in_string(line) == 'X') {
			Xwon++;
		}
		if (who_won_in_string(line) == 'O') {
			Owon++;
		}
		if (who_won_in_string(column) == 'X') {
			Xwon++;
		}
		if (who_won_in_string(column) == 'O') {
			Owon++;
		}

		//получаем две диагонали
		diagonal1 += get_symbol_by_coordinates(str, i, i);
		diagonal2 += get_symbol_by_coordinates(str, i, 4 - i);
	}

	//опрделяем есть ли победитель в первой диагонали
	if (who_won_in_string(diagonal1) == 'X') {
		Xwon++;
	}
	if (who_won_in_string(diagonal1) == 'O') {
		Owon++;
	}

	//опрделяем есть ли победитель во второй диагонали
	if (who_won_in_string(diagonal2) == 'X') {
		Xwon++;
	}
	if (who_won_in_string(diagonal2) == 'O') {
		Owon++;
	}

	//условия победы и ничьей так же зависят от количества Х и О
	if ((Xwon == 0 && Owon == 0) && ((XChar == OChar) || ((XChar - 1) == OChar))) {
		std::cout << "Nobody.";
		return;
	}else if (Xwon == 1 && Owon == 0 && (XChar - 1) == OChar) {
		std::cout << "Petya won.";
		return;
	}else if (Xwon == 0 && Owon == 1 && XChar == OChar) {
		std::cout << "Vanya won.";
		return;
	}

	std::cout << "Incorrect.";
	return;
}

int main() {

	std::string playingField = enter_line(1);
	playingField += enter_line(2);
	playingField += enter_line(3);
		
	if (checking_playing_field (playingField)) {
		who_won (playingField);
	}
	else {
		std::cout << "Incorrect.";
	}
}
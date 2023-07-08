#include "defaults.h"

class CustomString {
private:

	/*
	*	Так как мы не изобретаем велосипед, а лишь углубляемся в уже существующий
	*	класс std::string, то будем делать также, как устроено там. В принципе,
	*	другой реализации строк, кроме массива символов, в моей голове не возникает.
	*/

	// Указатель на массив из символов 
	// Символ _ перед переменной означает, 
	// что переменная не будет доступна 
	// вне класса, потому что она приватная 
	char* _str;	
	int _length;

public:
	
	// Конструктор без параметров
	CustomString() {
		// Если в конструктор ничего не передаётся, то мы явно указываем, что указатель пустой
		_str = nullptr;
		_length = 0;
	}

	// Конструктор с передачей в аргументы строки
	CustomString(const char* str) {
		/*
		*	Мы передаём в конструктор динамический массив типа char (далее - строка).
		*	Далее, мы создаём массив, на который будет указывать _str,
		*	длиною в передаваемую строку + 1 (для терминирующего нуля ('\0'))
		*	Далее, поочерёдно присваиваем каждому элементу массива НАШЕГО класса
		*	соответствующий символ передаваемой строки, а в самый последний элемент
		*	присваиваем терминирующий ноль, чтобы закрыть строку.
		*/
		_length = strlen(str);
		_str = new char[_length + 1];

		for (int i = 0; i < _length; i++) {
			_str[i] = str[i];
		}

		_str[_length] = '\0';
	}
	
	// Деструктор, для освобождения выделенной динамической памяти
	~CustomString() {
		delete[] _str;
	}

	// Конструктор копирования
	CustomString(const CustomString& other) {
		// Если указатель не пустой - удаляем динамически выделенный массив,
		// чтобы создать новый для новой строки
		if (this->_str != nullptr) {
			delete[] this->_str;
		}

		_length = other._length;
		this->_str = new char[_length + 1];

		for (int i = 0; i < _length; i++) {
			this->_str[i] = other._str[i];
		}

		_str[_length] = '\0';
	}

	// Конструктор перемещения
	CustomString(CustomString&& other) {
		this->_length = other._length;
		this->_str = other._str;

		other._str = nullptr;
	}

	// Перегрузка оператора присваивания (=)
	CustomString& operator = (const CustomString& other) {

		if (this->_str != nullptr) {
			delete[] this->_str;
			_str = nullptr;
		}

		_length = other._length;
		this->_str = new char[_length + 1];

		for (int i = 0; i < _length; i++) {
			this->_str[i] = other._str[i];
		}

		_str[_length] = '\0';

		return *this; // Вернуть ссылку на текущий объект
	}

	// Перегрузка оператора (+)
	CustomString operator + (const CustomString& other) {
		int newLength = _length + other._length;
		char* newStr = new char[newLength + 1];

		int i = 0;
		for (; i < _length; i++) {
			newStr[i] = _str[i];
		}

		for (int j = 0; j < other._length; j++, i++) {
			newStr[i] = other._str[j];
		}

		newStr[newLength] = '\0';

		return newStr;
	}

	// Перегрузка оператора (==)
	bool operator == (const CustomString& other) {
		if (this->_length != other._length) {
			return false;
		}
		
		for (int i = 0; i < this->_length; i++) {
			if (this->_str[i] != other._str[i]) {
				return false;
			}
		}

		return true;
	}

	// Перегрузка оператора ([])
	char& operator [] (unsigned int index) {
		return _str[index];
	}

	// Перегрузка оператора (!=)
	bool operator !=(const CustomString& other) {
		return !(this->operator==(other));
	}

	// Вывод строки
	void Print() {
		cout << _str << endl;
	}

	int Length() const {
		return _length;
	}
};

int main() {
	// Для корректного отображения кириллицы
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	CustomString str1 = "hello", str2 = "world";
	str1[0] = 'H';
	CustomString str3 = str1 + ", " + str2 + "!";
	CustomString str5, str4;
	str5 = str4 = str3;
	str5.Print();
	cout << "str5 length: " << str5.Length() << endl;
	str1 == str2 ? cout << "str1 == str2" << endl : cout << "str1 != str2" << endl;

	return 0;
}
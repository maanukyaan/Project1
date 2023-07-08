#include "defaults.h"

class CustomString {
private:

	/*
	*	��� ��� �� �� ���������� ���������, � ���� ����������� � ��� ������������
	*	����� std::string, �� ����� ������ �����, ��� �������� ���. � ��������,
	*	������ ���������� �����, ����� ������� ��������, � ���� ������ �� ���������.
	*/

	// ��������� �� ������ �� �������� 
	// ������ _ ����� ���������� ��������, 
	// ��� ���������� �� ����� �������� 
	// ��� ������, ������ ��� ��� ��������� 
	char* _str;	
	int _length;

public:
	
	// ����������� ��� ����������
	CustomString() {
		// ���� � ����������� ������ �� ���������, �� �� ���� ���������, ��� ��������� ������
		_str = nullptr;
		_length = 0;
	}

	// ����������� � ��������� � ��������� ������
	CustomString(const char* str) {
		/*
		*	�� ������� � ����������� ������������ ������ ���� char (����� - ������).
		*	�����, �� ������ ������, �� ������� ����� ��������� _str,
		*	������ � ������������ ������ + 1 (��� �������������� ���� ('\0'))
		*	�����, ��������� ����������� ������� �������� ������� ������ ������
		*	��������������� ������ ������������ ������, � � ����� ��������� �������
		*	����������� ������������� ����, ����� ������� ������.
		*/
		_length = strlen(str);
		_str = new char[_length + 1];

		for (int i = 0; i < _length; i++) {
			_str[i] = str[i];
		}

		_str[_length] = '\0';
	}
	
	// ����������, ��� ������������ ���������� ������������ ������
	~CustomString() {
		delete[] _str;
	}

	// ����������� �����������
	CustomString(const CustomString& other) {
		// ���� ��������� �� ������ - ������� ����������� ���������� ������,
		// ����� ������� ����� ��� ����� ������
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

	// ����������� �����������
	CustomString(CustomString&& other) {
		this->_length = other._length;
		this->_str = other._str;

		other._str = nullptr;
	}

	// ���������� ��������� ������������ (=)
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

		return *this; // ������� ������ �� ������� ������
	}

	// ���������� ��������� (+)
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

	// ���������� ��������� (==)
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

	// ���������� ��������� ([])
	char& operator [] (unsigned int index) {
		return _str[index];
	}

	// ���������� ��������� (!=)
	bool operator !=(const CustomString& other) {
		return !(this->operator==(other));
	}

	// ����� ������
	void Print() {
		cout << _str << endl;
	}

	int Length() const {
		return _length;
	}
};

int main() {
	// ��� ����������� ����������� ���������
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
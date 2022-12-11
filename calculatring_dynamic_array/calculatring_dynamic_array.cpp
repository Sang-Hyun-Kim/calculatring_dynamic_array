#include <iostream>
#include <sstream>
#include <algorithm>
//dynamic_array라는 이름의 클래스 템플릿을 작성하고, 주요 멤버 변수를 선언
template <typename T>
class dynamic_array
{
	T* data;
	size_t n;
public://배열 크기를 인자로 받은 생성자와 복사 생성자 추가
	dynamic_array(int n)
	{
		this->n = n;
		data = new T[n];
	}

	dynamic_array(const dynamic_array<T>& other)
	{
		n = other.n;
		data = new T[n];
		for (int i = 0; i < n; i++)
		{
			data[i] = other[i];
		}
	}
	//멤버 데이터에 직접 접근하기 위한 []연산자와 at() 함수를 작성, []연산자를 제공함으로써 std::array와 비슷한 방식으로 배열 원소에 접근 할 수가 있다.
	T& operator[](int index)
	{
		return data[index];
	}
	const T& operator[](int index) const
	{
		return data[index];
	}
	T& at(int index)
	{
		if (index < n)
			return data[index];
		throw "Index out of rage";
	}
	//배열 크기를 반환하는 size() 멤버 함수와 소멸자를 구현한다. 소멸자는 메모리 누수를 방지하기 위해 할당된 메모리를 해제함
	size_t size() const
	{
		return n;
	}
	~dynamic_array()
	{
		delete[] data;
	}
	//dynamic_array의 배열 원소를 순회할 때 사용할 반복자 관련 함수를 정의
	T* begin() { return data; }
	const T* begin() const { return data; }
	T* end() { return data + n; }
	const T* end() const { return data + n; }
	// 두 배열을 하나로 합치는 연산을 수행하는 +연산자 함수를 정의합니다. 이 함수는 friend로 선언한다.

	friend dynamic_array<T> operator+(const dynamic_array<T>& arr1, dynamic_array<T>& arr2)
	{
		dynamic_array<T> result(arr1.size() + arr2.size());
		std::copy(arr1.begin(), arr1.end(), result.begin());
		std::copy(arr2.begin(), arr2.end(), result.begin() + arr1.size());

		return result;
	}
	//배열에 저장된 모든 데이터를 문자열로 반환하는 to_string() 멤버 함수를 작성한다. 이 함수는 데이터 구분을 위한 문자열 sep를 인자로 받으며, sep의 기본값은 쉼표(",")로 지정한다.
	std::string to_string(const std::string& sep = ",")
	{
		if (n == 0)
			return "";
		std::ostringstream os;
		os << data[0];

		for (int i = 1; i < n; i++)
			os << sep << data[i];
		
		
		return os.str();
    }


};
//학생 정보를 저장할 구조체 student를 정의한다. 이구조체는 학생의 이름 anme과 학생의 학급정보를 담고있는 standard 멤버를 가지고 있고 << 연산자를 이용한 표준 출력을 지원함
struct student
{
	std::string name;
	int standard;
};
std::ostream& operator<<(std::ostream& os, const student& s)
{
	return (os << "[" << s.name << "," << s.standard << "]");
}
//이제 main 함수에서 dynamic_array를 사용하는 코드를 작성합니다.
int main()
{
	int nStudnets;
	std::cout << "1반 학생수를 입력하세요: ";
	std::cin >> nStudnets;

	dynamic_array<student> class1(nStudnets);
	for (int i = 0; i < nStudnets; i++)
	{
		std::string name;
		int standard;
		std::cout << i + 1 << "번째 학생 이름과 나이를 입력하세요: ";
		std:: cin >> name >> standard;
		class1[i] = student{ name, standard };
	}

	//배열 크기보다 큰 인덱스의 학생에 접근
	try
	{
		//아래 주석을 해제하면 프로그램이 비정상 종류 됨
		//class1[nStudnets] = student{"John",8}//예상할 수 없는 동작
			
		class1.at(nStudnets) = student{ "John",8 };// 예외발생
	}
	catch(...)
	{
		std::cout << "예외 발생!" << std::endl;
	}
	//깊은 복사
	auto class2 = class1;
	std::cout << "1반을 복사하려 2반을 생성: " << class2.to_string() << std::endl;
	//두학급을 합쳐서 새롱누 큰 학급을 생성
	auto class3 = class1 + class2;
	std::cout << "1반과 2반을 합쳐 3반 생성: " << class3.to_string() << std::endl;

	return 0;
}
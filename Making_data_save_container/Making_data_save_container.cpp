/*
   다양한 타입의 데이터 여러 개를인자로 받아 공통 타입으로 변환하는 함수를 만들어볼 것이다
   이 함수가 반환하는 컨테이너는 모든인자를 공통 타입으로 변환하여 저장하며, 전체 원소를 빠르게 순회할 수 있어야 합니다.
*/
#include <iostream>
#include <array>
#include <type_traits>

//컨테이너를 생성하는 build_array() 함수를 선언할 것이다. 이 함수는 빠른 원소 순회를 보장하는  std::array를 반환합니다. 그리고 임의 개수의 매개변수를 허용하기 위해 가변 템플릿을 사용함
//template<typename ... Args>
//std::array<?,?> build_array(Args&&...arg)
//반환된 컨테이너는 빠르게 순회할 수 있어야 한다는 조건이 있으므로 배열 또는 벡터(vector)를 사용할 수 있습니다.
//이 예제에서는 컴파일 시간에 함수의 인자 개수로부터 원소 개수를 유추할 수 있으므로 std::array를 사용함
//std::array를 사용하려면 원소의 타입과 원소 개수를 지정해야 합니다. std::array에 저장할 원소의 타입을 결정하기 위해 std::common_type 템플릿을 사용할 수 있습니다.
//이 작업은 함수 인자에 의존적이기 때문에 함수 환환형을 후행 리턴 타입(trailing return type)으로 지정합니다.

template<typename ... Args>
auto build_array(Args&&... args)->std::array<typename std::common_type<Args...>::type, sizeof...(args)>
{
    using commonType = typename std::common_type<Args...>::type;
    //배열 생성
    return{ std::forward<commonType>((Args&&)args)... };
}

int main()
{
    auto data = build_array(1, 0u, 'a', 3.2f, false);

    for (auto i : data)
    {
        std::cout << i << " ";//함수에 전달된 인자들이 모두 float 자료형으로 변환될 수 있기 때문에 최종출력은 float 형식으로 나타납니다.
    }
    std::cout << std::endl;
    //auto data2 = build_array(1,"Packt",2.0);
    //모든 데이터 타입을 하나의 공통 타입으로 변환 할 수 업어서 에러가 발생함
    //template argument deduction/substitution failed 같은 문자열을 포함합니다. 라는 에러메세지 발생
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.

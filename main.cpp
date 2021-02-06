#include <iostream>
#include <cmath>

int multiply(int a, int b) {

    return a * b;
}

int divide(int a, int b) {

    return a / b;
}

void f() {}

int main()
{
    int a{7}, b{6};
    std::cout << "Hello, master";
    std::cout << pow(a, b) << std::endl;
    std::cout << std::sqrt(pow(a,2) + pow(b,2)) << std::endl;
    std::cout << a + b << std::endl;
    std::cout << a - b << std::endl;
    ++a;
    --b;
    std::cout << multiply(a, b) << std::endl;

    //при использовании Merge мы подгружали всю историю коммитов. Благодаря этому сохраняется детальное описание
    //всех действий, но если коммитов в ветке было сделано сильно много (или паралельно в нескольких ветках работают
    //несколько разработчиков), то Log нагромаждается. Для простоты и чистоты Loga вместо Merge используем Rebase.
    //Тогда в Loge видим только одну петельку, которая отображает перемещение из новой ветки в ветку мастера (даже
    //если в новой ветке много комитов). Причем эта петелька поднимается выше последнего коммита

    return 0;
}

#include <iostream>
#include <p2matrix.h>

int main()
{
    p2Mat22 m1(p2Vec2(2.0f, 3.0f), p2Vec2(5.0f, 6.0f));
    p2Mat22 m2(p2Vec2(7.0f, 9.0f), p2Vec2(1.0f, 4.0f));
    
    std::cout << "\n" << "m1:" << "\n";
    m1.Show();
    
    std::cout << "\n" << "m2:" << "\n";
    m2.Show();
    
    std::cout << "\n" << "m1-m2:" << "\n";
    (m1 - m2).Show();
    
    std::cout << "\n" << "Determinant m1: " << m1.GetDeterminant() << "\n";
    std::cout << "\n" << "Determinant m2: " << m2.GetDeterminant() << "\n";
    
    std::cout << "\n" << "m1 inverse:" << "\n";
    m1.Invert().Show();
    
    std::cout << "\n" << "m2 inverse:" << "\n";
    m2.Invert().Show();
    
    std::cout << "\n" << "m1*2:" << "\n";
    (m1 * 2.0f).Show();
    
    system("pause");
    return 0;
}

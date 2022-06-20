#include <iostream>
#include <string>
class setInt {
private:
    int* _set;
    int _length;
    int _capacity;
    bool _is_duplicate(int num);
    void _double_capacity();
    void _push_back(int num);
public:
    setInt operator+(setInt anSet);
    setInt operator*(setInt anSet);
    setInt operator/(setInt anSet);
    friend std::ostream& operator<<(std::ostream& out, setInt set);
    setInt();
    void input();
    int length();
    bool isIn(int num);
    int capacity();
    void print();
    void insert(int num);
};

bool isNumber(std::string num);



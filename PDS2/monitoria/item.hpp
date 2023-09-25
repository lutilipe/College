#include <iostream>

using namespace std;

class Item {
private:
    int _key, _val;

public:
    Item() : _key(0), _val(0) {}

    Item(int key, int val) : _key(key), _val(val) {}

    friend std::ostream& operator<<(std::ostream& out, const Item& i) {
        out << "(" << i._key << "," << i._val << ")";
        return out;
    }

    bool operator>(const Item& other) const {
        return _val > other._val;
    }

};
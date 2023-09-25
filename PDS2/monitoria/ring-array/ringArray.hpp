#include <iostream>
#include <vector>

using namespace std;

template<class T>
class RingArray {
private:
    std::vector<T> _buffer;
    int _capacidade;
    int _tamanho;
    int _head = 0;
    int _tail = 0;

public:
    RingArray(int capacidade) : _capacidade(capacidade), _tamanho(0), _head(0) {
        _buffer.resize(capacidade);
    }

    void push(T item) {
        if (is_full()) {
            _head = (_head + 1) % _capacidade;
        }
        _buffer[_tail] = item;
        _tail = (_tail + 1) % _capacidade;
        _tamanho = std::min(_tamanho + 1, _capacidade);
    }

    T get(int index) {
        int realIndex = is_full()
            ? (_head + index) % _capacidade
            : (_head + ((_head + index) % _tamanho)) % _capacidade;
        return _buffer[realIndex];
    }

    T pop() {
        T value = _buffer[_head];
        _head = (_head + 1) % _capacidade;
        _tamanho--;
        return value;
    }

    void print() {
        int current = _head;
        for (int i = 0; i < _tamanho; i++) {
            std::cout << _buffer[current] << std::endl;
            current = (current + 1) % _capacidade;
        }
    }

    T get_maior() {
        T maxVal = _buffer[_head];
        int i = (_head + 1) % _capacidade;
        int count = 1;
        while (count < _tamanho) {
            if (_buffer[i] > maxVal) {
                maxVal = _buffer[i];
            }
            i = (i + 1) % _capacidade;
            count++;
        }
        return maxVal;
    }

    int size() {
        return _tamanho;
    }

    bool is_empty() {
        return _tamanho == 0;
    }

    bool is_full() {
        return _tamanho == _capacidade;
    }
};

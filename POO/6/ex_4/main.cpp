// Base code

class Base{
    int i;
    
    protected:
        void set(int ii) { i = ii; }
        int read() const { return i; }
    
    public:
        Base(int ii = 0) : i(ii) {}
        int value(int m) const { return m*i; }
};


class Derived : protected Base {
    int j;
    public:
        Derived(int jj = 0) : j(jj) {}
        void change(int x) { set(x); }
        int test1() { return read(); };
};

class Derived2 : public Derived {
    public:
        void test2() { read(); value(0); };
};


int main () {
    // Derived d;
    // d.test();

    return 0;
}

/*

RESPOSTAS:

1) Sim, pois o método "read" da classe Base é protected, podendo ser usado em classes derivadas dela

2) Sim, pois Derived herda o metodo "read" como privado. Assim, um objeto da classe Derived nao
podera usar esse metodo, mas ele podera ser usado em outro metodo dentro dessa classes

3) Nao. Se a classe for herdada como "public", o metodo "read" sera protected. Se for herdada como
private, o metodo sera privado. Em ambos os casos, o metodo podera ser usado apenas dentro da classe,
mas nao em um objeto que instancia ela.

4) Sim, pois a classe Derived herda esses dois metodos como protected da classe Base. Assim, a classe
Derived2, que deriva Derived com heranca publica, tambem consegue utilizar esses metodos
internamente.

*/
#include <iostream>
#include <vector>
#include <string>

class Livro {
private:
    int _id = 0;
    static int _prox_id;
    std::string _titulo;
    std::string _autor;
    int _anoPublicacao;
    std::string _genero;

public:
    Livro(std::string titulo, std::string autor, int anoPublicacao)
        : _titulo(titulo), _autor(autor), _anoPublicacao(anoPublicacao) {
        _id = ++_prox_id;
        _genero = "Livro";
    }

    virtual ~Livro() {
        std::cout << "Destrutor Livro" << std::endl;
    }

    virtual void print_info() {
        std::cout << "Info: Livro " << _id << std::endl;
        std::cout << "\tTitulo: " << _titulo << std::endl;
        std::cout << "\tAutor: " << _autor << std::endl;
        std::cout << "\tAno de publicacao: " << _anoPublicacao << std::endl;
        std::cout << "\tGenero: " << _genero << std::endl;
    }

    int getId() {
        return _id;
    }

    void setGenre(std::string genre) {
        _genero = genre;
    }
};

int Livro::_prox_id = 0;

class LivroFiccao : public Livro {
private:
    std::string _subgenero;

public:
    LivroFiccao(std::string titulo, std::string autor, int anoPublicacao, std::string subgenero)
        : Livro(titulo, autor, anoPublicacao), _subgenero(subgenero) {
            setGenre("Ficcao");
        }

    virtual ~LivroFiccao() {
        std::cout << "Destrutor LivroFiccao" << std::endl;
    }

    virtual void print_info() override {
        Livro::print_info();
        std::cout << "\tSubgenero: " << _subgenero << std::endl;
    }
};

class LivroNaoFiccao : public Livro {
private:
    std::string _assunto;

public:
    LivroNaoFiccao(std::string titulo, std::string autor, int anoPublicacao, std::string assunto)
        : Livro(titulo, autor, anoPublicacao), _assunto(assunto) {
            setGenre("NaoFiccao");
        }

    virtual ~LivroNaoFiccao() {
        std::cout << "Destrutor LivroNaoFiccao" << std::endl;
    }

    virtual void print_info() override {
        Livro::print_info();
        std::cout << "\tAssunto: " << _assunto << std::endl;
    }
};

class LivroInfantil : public Livro {
private:
    int _faixaEtariaMinima;

public:
    LivroInfantil(std::string titulo, std::string autor, int anoPublicacao, int faixaEtariaMinima)
        : Livro(titulo, autor, anoPublicacao), _faixaEtariaMinima(faixaEtariaMinima) {
            setGenre("Infantil");
        }

    virtual ~LivroInfantil() {
        std::cout << "Destrutor LivroInfantil" << std::endl;
    }

    virtual void print_info() override {
        Livro::print_info();
        std::cout << "\tFaixa etaria minima: " << _faixaEtariaMinima << std::endl;
    }
};

class Biblioteca {
private:
    std::vector<Livro*> _livros;

public:
    Biblioteca() {}

    ~Biblioteca() {
        for (int i = 0; i < _livros.size(); i++) {
            delete _livros[i];
        }
    }

    void add_livro(Livro* livro) {
        _livros.push_back(livro);
    }

    void list_livros() {
        for (Livro* livro : _livros) {
            livro->print_info();
        }
    }

    void find_livro(int id) {
        bool encontrado = false;
        for (Livro* livro : _livros) {
            if (livro->getId() == id) {
                livro->print_info();
                encontrado = true;
                break;
            }
        }
        if (!encontrado) {
            std::cout << "Erro ao pesquisar: livro com ID " << id << " nao encontrado" << std::endl;
        }
    }

    void remove_livro(int id) {
        for (auto it = _livros.begin(); it != _livros.end(); ++it) {
            if ((*it)->getId() == id) {
                delete *it;
                _livros.erase(it);
                return;
            }
        }
        std::cout << "Erro ao remover: livro com ID " << id << " nao encontrado" << std::endl;
    }
};

int main() {
    Biblioteca* biblioteca = new Biblioteca();
    std::string comando;

    while (std::cin >> comando) {
        if (comando == "add_f") {
            std::string titulo, autor, subgenero;
            int anoPublicacao;
            std::cin >> titulo >> autor >> anoPublicacao >> subgenero;
            biblioteca->add_livro(new LivroFiccao(titulo, autor, anoPublicacao, subgenero));
        } else if (comando == "add_nf") {
            std::string titulo, autor, assunto;
            int anoPublicacao;
            std::cin >> titulo >> autor >> anoPublicacao >> assunto;
            biblioteca->add_livro(new LivroNaoFiccao(titulo, autor, anoPublicacao, assunto));
        } else if (comando == "add_i") {
            std::string titulo, autor;
            int anoPublicacao, faixaEtariaMinima;
            std::cin >> titulo >> autor >> anoPublicacao >> faixaEtariaMinima;
            biblioteca->add_livro(new LivroInfantil(titulo, autor, anoPublicacao, faixaEtariaMinima));
        } else if (comando == "rm") {
            int id;
            std::cin >> id;
            biblioteca->remove_livro(id);
        } else if (comando == "find") {
            int id;
            std::cin >> id;
            biblioteca->find_livro(id);
        } else if (comando == "list") {
            biblioteca->list_livros();
        }
    }

    delete biblioteca;

    return 0;
}

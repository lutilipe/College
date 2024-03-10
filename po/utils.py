import csv

def ler_dados_viagens(nome_arquivo):
    horario = []
    duracao = []
    preco_passagem = []
    num_passageiros = []

    with open(nome_arquivo, 'r') as file:
        reader = csv.reader(file, delimiter=';')

        next(reader, None)

        for row in reader:
            horario.append(int(row[0]))
            duracao.append(int(row[1]))
            preco_passagem.append(int(row[2]))
            num_passageiros.append(int(row[3]))

    return {
        'horario': horario,
        'duracao': duracao,
        'preco_passagem': preco_passagem,
        'num_passageiros': num_passageiros
    }

def ler_dados_avioes(nome_arquivo):
    capacidade = []

    with open(nome_arquivo, 'r') as file:
        reader = csv.reader(file, delimiter=';')

        next(reader, None)

        for row in reader:
            capacidade.append(int(row[0]))

    return capacidade

def ler_matriz_de_custos(nome_do_arquivo):
    dados = {}

    with open(nome_do_arquivo, 'r') as file:
        reader = csv.reader(file, delimiter=';')

        next(reader, None)

        for row in reader:
            for i, valor in enumerate(row):
                if i not in dados:
                    dados[i] = []
                dados[i].append(float(valor) / 60)

    return [value for value in dados.values()]
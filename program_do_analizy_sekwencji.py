import sys


def liczenie_zawartosci_GC():
    file = open(sys.argv[1], "r")
    ilosc_zasad_azotowych = 0
    ilosc_GC = 0
    zasady = ["A", "T", "C", "G"]

    for line in file:
        line = line.strip()  # usuwa znaki biale z konca i poczatku stringa
        for letter in line:
            if (letter in zasady):
                ilosc_zasad_azotowych += 1
            if (letter == "G" or letter == "C"):
                ilosc_GC += 1

    return ilosc_GC/ilosc_zasad_azotowych
#print(f"Wspolczynnik GC = {liczenie_zawartosci_GC()}")


def liczenie_ATCG_w_wielu_sekwencjach():
    liczba_A = 0
    liczba_T = 0
    liczba_C = 0
    liczba_G = 0
    for plik in sys.argv[1:]:
        with open(plik, "r") as file:
            for line in file:
                line = line.strip()
                for letter in line:
                    if (letter == "A"):
                        liczba_A += 1
                    elif (letter == "T"):
                        liczba_T += 1
                    elif (letter == "C"):
                        liczba_C += 1
                    elif (letter == "G"):
                        liczba_G += 1
            print(f"{plik} A: {liczba_A} T: {liczba_T} C: {liczba_C} G: {liczba_G}")


def Tworzenie_listy_z_pliku(x):
    lista_sekwencja = []
    zasady = ["A", "T", "C", "G"]
    plik = sys.argv[x]
    with open(plik, "r") as sekwencja:
        for line in sekwencja:
            line = line.strip()
            for letter in line:
                if (letter in zasady):
                    lista_sekwencja.append(letter)

    return lista_sekwencja


def Dot_plot():

    sekwencja_1 = Tworzenie_listy_z_pliku(1)
    sekwencja_2 = Tworzenie_listy_z_pliku(2)
    # print(sekwencja_1)
    # print(sekwencja_2)
    macierz = [[None for _ in range(len(sekwencja_2))]
               for _ in range(len(sekwencja_1))]

    row = 0
    for zasada_1 in sekwencja_1:
        column = 0
        for zasada_2 in sekwencja_2:
            if (zasada_1 == zasada_2):
                macierz[row][column] = 1
            else:
                macierz[row][column] = 0
            column += 1
        row += 1

    print(f" {str.join(' ', sekwencja_2)}")
    i = 0
    for row in macierz:
        print(f"{sekwencja_1[i]} {str.join(' ',map(lambda x: str(x),row))}")
        i += 1


print("\n")
Dot_plot()


def Liczenie_wystapien(nr_pliku, aminokwasy: list):
    slownik = {}
    Model = 0
    prev_amino_number = 0

    with open(sys.argv[nr_pliku], "r") as sekwencja:
        for line in sekwencja:
            tab = line.split()
            if (tab[0] == "MODEL"):
                Model += 1
            elif (Model == 1 and tab[0] == 'ATOM'):
                if (tab[3] in aminokwasy and tab[5] != prev_amino_number):
                    prev_amino_number = tab[5]
                    if tab[3] in slownik.keys():  # jesli aminokwas jest juz w slowniku
                        slownik[tab[3]] += 1  # to tylko zwiekszam jego wartosc
                    else:
                        slownik[tab[3]] = 1

            elif tab[0] == "ENDML":
                break

    print(slownik)


def Liczenie_aminokwasow():

    aminokwasy = ["GLY", "ALA", "VAL", "LEU", "ILE", "PRO", "SER", "THR", "CYS",
                  "MET", "PHE", "TYR", "TRP", "ASP", "ASN", "GLU", "GLN", "LYS", "ARG", "HIS"]
    # for amino in aminokwasy:
    Liczenie_wystapien(1, aminokwasy)


def Statystyki_kodonow(FASTA):

    Kodony = [
        ["Ala", "GCT", "GCC", "GCA", "GCG"],
        ["Ile", "ATT", "ATC", "ATA"],
        ["Arg", "CGT", "CGC", "CGA", "CGG", "AGA", "AGG"],
        ["Leu", "CTT", "CTC", "CTA", "CTG" "TTA", "TTG"],
        ["Asn", "AAT", "AAC"],
        ["Lys", "AAA", "AAG"],
        ["Asp", "GAT", "GAC"],
        ["Met", "ATG"],
        ["Phe", "TTT", "TTC"],
        ["Cys", "TGT", "TGC"],
        ["Pro", "CCT", "CCC", "CCA", "CCG"],
        ["Gln", "CAA", "CAG"],
        ["Ser", "TCT", "TCC", "TCA", "TCG", "AGT", "AGC"],
        ["Glu", "GAA", "GAG"],
        ["Thr", "ACT", "ACC", "ACA", "ACG"],
        ["Trp", "TGG"],
        ["Gly", "GGT", "GGC", "GGA", "GGG"],
        ["Tyr", "TAT", "TAC"],
        ["His", "CAT", "CAC"],
        ["Val", "GTT", "GTC", "GTA", "GTG"],
        ["START", "ATG"],
        ["STOP", "TAA", "TGA", "TAG"]]

    Slownik_kodonow = dict((x[0], dict((y, 0) for y in x[1:])) for x in Kodony)
    # print(Slownik_kodonow)
    with open(FASTA, 'r') as file:
        sekwencja = file.read()
        zasady = ["A", "T", "C", "G"]
        kodon = ""
        for x in sekwencja:
            if (x in zasady):
                kodon = kodon+x
                if (len(kodon) == 3):
                    for aminokwas in Slownik_kodonow:
                        if kodon in list(Slownik_kodonow[aminokwas].keys()):
                            break

                        else:
                            raise Exception(
                                f"{kodon} nie znaleziony!")
                    # aminokwas = list(Slownik_kodonow.keys())[
                    #     list(Slownik_kodonow.values()).index(kodon)]
                    Slownik_kodonow[aminokwas][kodon] = Slownik_kodonow[aminokwas][kodon] + 1
                    print(kodon)
                    kodon = ""


Statystyki_kodonow("FKBP5.fna")

# Liczenie_aminokwasow()

# liczenie_ATCG_w_wielu_sekwencjach()

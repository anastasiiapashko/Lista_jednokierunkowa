#include "Lista_jednokierunkowa.h"

int main(){
{
    ap::ListaStudentow lista;

    lista.wyswietlListe();
    lista.odczyt_z_pliku("listaStudentow.txt");
   
    int wybor;
    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Dodaj studenta\n";
        std::cout << "2. Wyszukaj studenta\n";
        std::cout << "3. Zamien studentow miejscami\n";
        std::cout << "4. Wyswietl liste\n";
        std::cout << "5. Sortuj dane (wedlug nazwisk)\n";
        std::cout << "6. Usun studenta\n";
        std::cout << "0. Zakoncz program\n";
        std::cout << "Wybierz opcje: ";
        std::cin >> wybor;

        switch (wybor) {
        case 1: {
            lista.dodanie();
            break;
        }
        case 2: {
            lista.szukanie();
            break;
        }
        case 3: {
            lista.zamienMiejscami_Studentow();
            break;
        }
        case 4:
            std::cout << "Lista studentow wczytana z pliku:" << std::endl;
            lista.wyswietlListe();
            break;
        case 5:
            lista.sortujPoNazwisku();
           break;
        case 6:
            lista.usuwanie();
            break;
        case 0:
            std::cout << "Program zakonczony.\n";
            break;
        default:
            std::cout << "Nieprawidlowy wybor. Sprobuj ponownie.\n";
            break;
        }
    } while (wybor != 0);
    lista.wpis_do_pliku();
    system("cls");
    return 0;
}
}

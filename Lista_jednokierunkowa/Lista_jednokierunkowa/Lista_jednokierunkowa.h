#pragma once
#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <algorithm>
namespace ap {
    struct Student {
        std::string imie;
        std::string nazwisko;
        int oceny[5];
        std::string przedmioty[5];
        std::shared_ptr<Student> next; // Używamy std::shared_ptr zamiast zwykłego wskaźnika
        // Konstruktor domyślny
        Student() : imie(""), nazwisko(""), next(nullptr) {
            for (int i = 0; i < 5; ++i) {
                oceny[i] = 0;
                przedmioty[i] = "";
            }
        }

        // Konstruktor bezargumentowy
        Student(const std::string& im, const std::string& naz, std::shared_ptr<Student> n = nullptr)
            : imie(im), nazwisko(naz), next(n) {
            for (int i = 0; i < 5; ++i) {
                oceny[i] = 0;
                przedmioty[i] = "";
            }
        }
        
        // Konstruktor z argumentami
        Student(const std::string& im, const std::string& naz, const int oc[5], const std::string przed[5], std::shared_ptr<Student> n = nullptr)
            : imie(im), nazwisko(naz), next(n) {
            for (int i = 0; i < 5; ++i) {
                oceny[i] = oc[i];
                przedmioty[i] = przed[i];
            }
        }

        // Konstruktor kopiujący
        Student(const Student& other) : imie(other.imie), nazwisko(other.nazwisko), next(other.next) {
            for (int i = 0; i < 5; ++i) {
                oceny[i] = other.oceny[i];
                przedmioty[i] = other.przedmioty[i];
            }
        }

        // Konstruktor przenoszący
        Student(Student&& other) noexcept
            : imie(std::move(other.imie)), nazwisko(std::move(other.nazwisko)), next(other.next) {
            for (int i = 0; i < 5; ++i) {
                oceny[i] = other.oceny[i];
                przedmioty[i] = std::move(other.przedmioty[i]);
            }
            other.next = nullptr;
        }

        // Operator przypisania kopiującego
        Student& operator=(const Student& other) {
            if (this != &other) {
                imie = other.imie;
                nazwisko = other.nazwisko;
                for (int i = 0; i < 5; ++i) {
                    oceny[i] = other.oceny[i];
                    przedmioty[i] = other.przedmioty[i];
                }
                next = other.next;
            }
            return *this;
        }

        // Operator przypisania przenoszącego
        Student& operator=(Student&& other) noexcept {
            if (this != &other) {
                imie = std::move(other.imie);
                nazwisko = std::move(other.nazwisko);
                for (int i = 0; i < 5; ++i) {
                    oceny[i] = other.oceny[i];
                    przedmioty[i] = std::move(other.przedmioty[i]);
                }
                next = other.next;
                other.next = nullptr;
            }
            return *this;
        }

        /*
        Poniższa metoda sprawdza, czy oba podane wskaźniki studentów są
        różne od nullptr. Następnie szuka poprzedników obu studentów.
        W zależności od ich położenia na liście, zamienia
        */
        void zamienMiejscami(std::shared_ptr<Student> student1, std::shared_ptr<Student> student2, std::shared_ptr<Student> listaHead) {

            // Sprawdź, czy oba wskaźniki są różne od nullptr
            if (student1 && student2) {
                // Szukamy poprzedników obu studentów
                std::shared_ptr<Student> poprzednik1 = nullptr;
                std::shared_ptr<Student> poprzednik2 = nullptr;
                std::shared_ptr<Student> obecny = listaHead;

                while (obecny) {
                    if (obecny->next == student1) {
                        poprzednik1 = obecny;
                    }
                    if (obecny->next == student2) {
                        poprzednik2 = obecny;
                    }

                    obecny = obecny->next;
                }

                // Zamień miejscami tylko jeśli oba znaleziono poprzedniki
                if (poprzednik1 && poprzednik2) {
                    // Jeśli studenty nie są obok siebie, a jedynie jeden z nich jest głową listy
                    if (poprzednik1->next != student2 && poprzednik2->next != student1) {
                        std::shared_ptr<Student> temp = student1->next;
                        student1->next = student2->next;
                        student2->next = temp;

                        poprzednik1->next = student2;
                        poprzednik2->next = student1;
                    }
                    // Jeśli studenty są obok siebie
                    else {
                        // Obsłuż zamianę miejscami głowy listy
                        if (poprzednik1->next == student2) {
                            student1->next = student2->next;
                            student2->next = student1;
                            poprzednik2->next = student1;
                            listaHead = student2;
                        }
                        else if (poprzednik2->next == student1) {
                            student2->next = student1->next;
                            student1->next = student2;
                            poprzednik1->next = student2;
                            listaHead = student1;
                        }
                    }
                }
            }
        }
    };

    class ListaStudentow {
    private:
        std::shared_ptr<Student> head;
        size_t size;

    public:
        ListaStudentow() : head(nullptr), size(0){};

        // Metoda dodająca nowego studenta na początku listy
        void dodajStudenta(const Student& student) {
            std::shared_ptr<Student> nowyStudent = std::make_shared<Student>(student);
            nowyStudent->next = head;
            head = nowyStudent;
            size++;
        }
        void dodanie() {
            std::string imie, nazwisko;
            int oceny[5];
            std::string przedmioty[5];

            std::cout << "Podaj imie studenta: ";
            std::cin >> imie;
            std::cout << "Podaj nazwisko studenta: ";
            std::cin >> nazwisko;
            std::cout << "Podaj przedmioty i ich oceny (np. Matematyka 90): ";
            for (int i = 0; i < 5; ++i) {
                std::cout << "Podaj przedmiot " << i + 1 << " ";
                std::cin >> przedmioty[i];
                while (true) {
                    if (std::cin >> oceny[i]) {
                        break;
                    }
                    std::cout << "\nWprowadzono nie koreknie dane. Prosze jeszcze raz podac ocene:\n";
                    // Wyczyść błąd wejścia i zignoruj nieprawidłowe znaki
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                
            }

            dodajStudenta(Student(imie, nazwisko, oceny, przedmioty));
            std::cout << "Student dodany.\n";
        }
        // Metoda usuwająca studenta o podanym nazwisku z listy
        std::shared_ptr<Student> usunStudenta(const std::string& nazwisko) {
            std::shared_ptr<Student>  current = head;
            std::shared_ptr<Student>  prev = nullptr;

            while (current != nullptr && current->nazwisko != nazwisko) {
                prev = current;
                current = current->next;
            }

            if (current != nullptr) {
                if (prev != nullptr) {
                    prev->next = current->next;
                }
                else {
                    head = current->next;
                }
                current->next = nullptr;
            }
            size--;

            return current;
        }
        void usuwanie() {
            std::string nazwisko;
            std::cout << "Podaj nazwisko studenta do usuniecia: ";
            std::cin >> nazwisko;

            std::shared_ptr<Student> usunietyStudent = usunStudenta(nazwisko);

            if (usunietyStudent) {
                std::cout << "\nUsunieto studenta o nazwisku " << nazwisko << ":\n";
                std::cout << "Imie: " << usunietyStudent->imie << ", Nazwisko: " << usunietyStudent->nazwisko;
                std::cout << ", Przedmioty[Oceny]: ";
                for (int i = 0; i < 5; ++i) {
                    std::cout << " " << usunietyStudent->przedmioty[i] << "[" << usunietyStudent->oceny[i] << "]";
                }
                std::cout << std::endl;
            }
            else {
                std::cout << "\nNie znaleziono studenta o nazwisku " << nazwisko << std::endl;
            }
        }
        // Metoda wyszukująca studenta o podanym nazwisku
        std::shared_ptr<Student> wyszukajStudenta(const std::string& nazwisko) const {
            std::shared_ptr<Student> current = head;
            while (current != nullptr) {
                if (current->nazwisko == nazwisko) {
                    return current;
                }
                current = current->next;
            }
            return nullptr; // Nie znaleziono studenta
        }
        void szukanie() const {
            std::string nazwisko;
            std::cout << "Podaj nazwisko studenta do wyszukania: ";
            std::cin >> nazwisko;

            std::shared_ptr<Student> szukanyStudent = wyszukajStudenta(nazwisko);

            if (szukanyStudent) {
                std::cout << "\nZnaleziono studenta o nazwisku " << nazwisko << ":\n";
                std::cout << std::setw(11) << szukanyStudent->imie << std::setw(11) << szukanyStudent->nazwisko;
                for (int i = 0; i < 5; ++i) {
                    std::cout << std::setw(11) << szukanyStudent->przedmioty[i] << "[" << szukanyStudent->oceny[i] << "]";
                }
                std::cout << std::endl;
            }
            else {
                std::cout << "\nNie znaleziono studenta o nazwisku " << nazwisko << std::endl;
            }
        }
        // Sortowanie quick_sort
        int partition(std::shared_ptr<Student> arr[], int start, int end) {
            std::string pivot = arr[start]->nazwisko;

            int count = 0;
            for (int i = start + 1; i <= end; i++) {
                if (arr[i]->nazwisko <= pivot) {
                    count++;
                }
            }
            // Nadanie elementowi pivot właściwej pozycji
            int pivotIndex = start + count;
            std::swap(arr[pivotIndex], arr[start]);
            // Sortowanie lewej i prawej części elementu pivot
            int i = start, j = end;

            while (i < pivotIndex && j > pivotIndex) {
                while (arr[i]->nazwisko <= pivot) {
                    i++;
                }
                while (arr[j]->nazwisko > pivot) {
                    j--;
                }
                if (i < pivotIndex && j > pivotIndex) {
                    std::swap(arr[i], arr[j]);
                }
            }
            return pivotIndex;
        }
        void quickSort(std::shared_ptr<Student> arr[], int start, int end) {
            // przypadek podstawowy
            if (start >= end) {
                return;
            }
            //podział tablicy
            int podzial = partition(arr, start, end);
            //sortowanie lewej strony
            quickSort(arr, start, podzial - 1);
            //sortowanie prawej strony
            quickSort(arr, podzial + 1, end);
        }
        // Wywołanie quickSort 
        void sortujPoNazwisku() {
            if (head != nullptr) {
                std::shared_ptr<Student>* arr = new std::shared_ptr<Student>[size];
                int i = 0;

                // Przepisanie wskaźników z listy do tablicy
                std::shared_ptr<Student> current = head;
                while (current != nullptr && i < size) {
                    arr[i++] = current;
                    current = current->next;
                }
                //wywołanie sortowania
                quickSort(arr, 0, i - 1);

                // Przepisz posortowane elementy z powrotem do listy
                head = arr[0];
                current = head;
                for (int j = 1; j < i; ++j) {
                    current->next = arr[j];
                    current = current->next;
                }
                current->next = nullptr; // Ustaw next z ostatniego elementu na nullptr
                delete[] arr; // Zwolnij zaalokowaną pamięć
            }
            std::cout << "Lista zostala posortowana" << std::endl;
        }

        // Metoda wyświetlająca zawartość listy
        void wyswietlListe() const {
            std::shared_ptr<Student> current = head;
            while (current != nullptr) {
                std::cout << std::setw(11) << current->imie << "\t" << std::setw(11) << current->nazwisko << "\t";
                // Wyświetl oceny i przedmi
                for (int i = 0; i < 5; ++i) {
                    std::cout << std::setw(11) << current->przedmioty[i] << "[" << current->oceny[i] << "]";
                }
                std::cout << std::endl;
                current = current->next;
            }
        }

        void zamienMiejscami_Studentow() {
            std::string nazwisko1, nazwisko2;

            std::cout << "Podaj nazwisko pierwszego studenta: ";
            std::cin >> nazwisko1;

            std::cout << "Podaj nazwisko drugiego studenta: ";
            std::cin >> nazwisko2;

            std::shared_ptr<Student> student1 = wyszukajStudenta(nazwisko1);
            std::shared_ptr<Student> student2 = wyszukajStudenta(nazwisko2);

            if (student1 && student2) {
                // Używamy metody zamienMiejscami z klasy Student
                student1->zamienMiejscami(student1, student2, head);
            }
            else {
                std::cout << "Nie znaleziono jednego lub obu studentow o podanych nazwiskach." << std::endl;
            }
            std::cout<<"Studentow zamieniono miejscami"<< std::endl;
        }

        //Metoda do odczytu z pliku
        void odczyt_z_pliku(const std::string& plik) {

            // Strumień do odczytu z pliku
            std::ifstream Odczyt(plik);

            // Sprawdź, czy plik został otwarty poprawnie
            if (!Odczyt.is_open()) {
                std::cerr << "Nie mozna otworzyc pliku do odczytu: " << plik << std::endl;
                return;
            }
            // Odczytaj zawartość pliku linia po linii
            std::string linia;

            while (std::getline(Odczyt, linia)) {
                std::istringstream ss(linia);
                std::string imie, nazwisko, przedmiot, ocena;
                int oceny[5];
                std::string przedmioty[5];

                // Odczytaj imię i nazwisko
                ss >> imie >> nazwisko;

                int i = 0;
                // Odczytaj przedmioty i oceny
                while (ss >> przedmiot) {
                    size_t pozycjaOtwarcia = przedmiot.find('[');
                    size_t pozycjaZamkniecia = przedmiot.find(']');

                    if (pozycjaOtwarcia != std::string::npos && pozycjaZamkniecia != std::string::npos) {
                        std::string nazwaPrzedmiotu = przedmiot.substr(0, pozycjaOtwarcia);
                        int ocenaPrzedmiotu = std::stoi(przedmiot.substr(pozycjaOtwarcia + 1, pozycjaZamkniecia));
                        przedmioty[i] = nazwaPrzedmiotu;
                        oceny[i++] = ocenaPrzedmiotu;

                    }
                }
                dodajStudenta(Student(imie, nazwisko, oceny, przedmioty));
            }

            // Zamykamy plik po zakończeniu operacji odczytu
            Odczyt.close();
        }
        void wpis_do_pliku() {
            std::ofstream zapis("listaStudentow.txt");
            std::shared_ptr<Student> current = head;
            if (zapis.is_open()) {

                while (current != nullptr) {
                    zapis << std::fixed << std::setw(11) << current->imie << "\t " << std::setw(11) << current->nazwisko << "\t";

                    for (int i = 0;i < 5; ++i) {
                        zapis << " " << std::setw(11) << current->przedmioty[i] << "[" << current->oceny[i] << "]\t";
                    }
                    zapis << std::endl;
                    current = current->next;
                }

            }
            else {
                std::cout << "Nie udalo sie zapisac do pliku." << std::endl;
            }
            zapis.close();
        }
    };
}

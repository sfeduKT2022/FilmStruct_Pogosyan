


/* *****************************************************************************
Погосян Артур Славикович
КТбо1-2
Лабораторная работа №5 «Файлы данных»
Вариант № 8
Задание: Написать программу, которая записывает с клавиатуры в файл структуру согласно выданному варианту задания.
         В качестве разделителя полей структуры использовать символ табуляции. В программе реализовать:
         а) дополнение  существующего массива структур новыми структурами;
         б) поиск структуры с заданным значением выбранного элемента;
         в) вывод на экран содержимого массива структур;
         г) упорядочение массива структур по заданному полю (элементу), например государство по численности.
****************************************************************************** */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
//#define DEBUG
#define COUNT_FILM_PROPERTYS 8

//«Фильм»:     название,     режиссер     (фамилия,     имя,     отчество), страна,  год выпуска,  стоимость  (расходы  на выпуск), кассовые  сборы (доход). 

struct Film
{
    std::string name,
        producerSurname,
        producerName,
        producerMiddlename,
        country;
    int year;
    long long int cost, earnings;
};

void show_film_info(const Film film);

void fill_film_info(Film& film);

bool is_film_property(const std::string property);

void show_films_by_property(const std::vector<Film> films, const std::string property, const std::string typeOfProperty);

void read_films_from_file(const std::string filePath, std::vector<Film>& vectorForFilms);

void fill_film_in_file(const Film film, std::string beautyFilmInfoPath, std::string filmInfoPath);

void sort_films_by(std::vector<Film>& films, const std::string typeOfProperty, bool& sortedByCost, bool& sortedByEarnings, bool& sortedByYear);

void add_new_films(const std::string beautyFilmInfoPath, const std::string filmInfoPath);

void find_a_films_with_your_property(const std::vector<Film> films);

void show_all_films(const std::vector<Film> films);

void sort_films(std::vector<Film>& films, bool& sortedByCost, bool& sortedByEarnings, bool& sortedByYear);

void sort_by_cost(std::vector<Film>& films, bool& sortedByCost, bool& sortedByEarnings, bool& sortedByYear);

void sort_by_earnings(std::vector<Film>& films, bool& sortedByCost, bool& sortedByEarnings, bool& sortedByYear);

void sort_by_year(std::vector<Film>& films, bool& sortedByCost, bool& sortedByEarnings, bool& sortedByYear);


int main()
{
    bool sortedByCost, sortedByEarnings, sortedByYear, thisExist = true;
    sortedByCost = sortedByEarnings = sortedByYear = false;
    while (thisExist)
    {
        int filmsCount;
        const std::string BEAUTY_FILM_INFO_PATH = "b_films.txt";
        const std::string FILM_INFO_PATH = "films.txt";
        std::vector<Film> films;
        int choice;
        read_films_from_file(FILM_INFO_PATH, films);
        if (sortedByCost)
        {
            sort_by_cost(films, sortedByCost, sortedByEarnings, sortedByYear);
        }
        if (sortedByEarnings)
        {
            sort_by_earnings(films, sortedByCost, sortedByEarnings, sortedByYear);
        }
        if (sortedByYear)
        {
            sort_by_year(films, sortedByCost, sortedByEarnings, sortedByYear);
        }
        std::cout << "What do you want?\n1 - add new film\n2 - find a films with your property\n3 - show all films\n4 - sort a films with your property\n5 - quite\n";
        std::cin >> choice;
        system("cls");
        switch (choice)
        {
        case 1:
            add_new_films(BEAUTY_FILM_INFO_PATH, FILM_INFO_PATH);
            system("cls");
            films.clear();
            read_films_from_file(FILM_INFO_PATH, films);
            break;
        case 2:
            find_a_films_with_your_property(films);
            system("cls");
            break;
        case 3:
            show_all_films(films);
            system("cls");
            break;
        case 4:
            sort_films(films, sortedByCost, sortedByEarnings, sortedByYear);
            system("cls");
            break;
        case 5:
            thisExist = false;
            break;
#ifdef DEBUG
        case 6:
            std::cout << films.size() << std::endl;
            system("pause");
            system("cls");
            break;
#endif // DEBUG 
        default:
            std::cout << "wrong choice";
            break;
        }
    }
}


void show_films_by_property(const std::vector<Film> films, const std::string property, const std::string typeOfProperty)
{
    for (Film film : films)
    {
        if (film.name == property && typeOfProperty == "name")
            show_film_info(film);
        else if (film.producerSurname == property && typeOfProperty == "Poducer Surname")
            show_film_info(film);
        else if (film.producerName == property && typeOfProperty == "Poducer Name")
            show_film_info(film);
        else if (film.producerMiddlename == property && typeOfProperty == "Poducer Middlename")
            show_film_info(film);
        else if (film.country == property && typeOfProperty == "country")
            show_film_info(film);

        else if (typeOfProperty == "year")
        {
            if (film.cost == stoi(property))
                show_film_info(film);
        }
        else if (typeOfProperty == "cost")
        {
            if (film.cost == stoi(property))
                show_film_info(film);
        }
        else if (typeOfProperty == "earnings")
        {
            if (film.earnings == stoi(property))
                show_film_info(film);
        }


    }
}

void read_films_from_file(const std::string filePath, std::vector<Film>& vectorForFilms)
{
    std::fstream file;
    file.open(filePath, std::fstream::app | std::fstream::in);
    if (!file.is_open())
    {
        std::cout << "File is not open!";
        return;
    }
    std::string line;
    while (!file.eof())
    {
        file >> line;
        if (!line.empty())
        {
            std::string temp;
            Film film;
            int filmPropertyIndex = 0;
            for (int i = 0; i < line.size(); ++i)
            {
                if (line[i] == ',')
                {
                    switch (filmPropertyIndex)
                    {
                    case 0:
                        film.name = temp;
                        temp = "";
                        break;
                    case 1:
                        film.producerSurname = temp;
                        temp = "";
                        break;
                    case 2:
                        film.producerName = temp;
                        temp = "";
                        break;
                    case 3:
                        film.producerMiddlename = temp;
                        temp = "";
                        break;
                    case 4:
                        film.country = temp;
                        temp = "";
                        break;
                    case 5:
                        film.year = stoi(temp);
                        temp = "";
                        break;
                    case 6:
                        film.cost = stoi(temp);
                        temp = "";
                        break;
                    case 7:
                        film.earnings = stoi(temp);
                        temp = "";
                        break;
                    default:
                        break;
                    }

                    ++filmPropertyIndex;
                    continue;
                }
                temp = temp + line[i];
            }
            if (!line.empty())
            {
                film.cost = stoi(temp);
                film.earnings = stoi(temp);
            }

            vectorForFilms.push_back(film);
        }
    }
    file.close();

}

void fill_film_in_file(const Film film, std::string beautyFilmInfoPath, std::string filmInfoPath)
{
    std::fstream file;
    file.open(beautyFilmInfoPath, std::fstream::app);
    if (!file.is_open())
    {
        std::cout << "File is not open!\n";
        return;
    }
    file << "name: " << film.name << '\n' << "producer surname: " << film.producerSurname << '\n' << "producer name: " << film.producerName << '\n'
        << "producer middlename: " << film.producerMiddlename << '\n' << "country: " << film.country << '\n'
        << "year " << film.year << '\n' << "cost: " << film.cost << '$' << '\n' << "earnings: " << film.earnings << '$' << '\n' << '\n';
    file.close();
    file.open(filmInfoPath, std::fstream::app);
    if (!file.is_open())
    {
        std::cout << "File is not open!\n";
        return;
    }
    file << film.name << ',' << film.producerSurname << ',' << film.producerName << ',' << film.producerMiddlename << ','
        << film.country << ',' << film.year << ',' << film.cost << ',' << film.earnings << '\n';
    file.close();
}

void sort_films_by(std::vector<Film>& films, const std::string typeOfProperty, bool& sortedByCost, bool& sortedByEarnings, bool& sortedByYear)
{
    if (typeOfProperty == "cost")
    {
        sort_by_cost(films, sortedByCost, sortedByEarnings, sortedByYear);
        sortedByCost = true;
    }
    else if (typeOfProperty == "earnings")
    {
        sort_by_earnings(films, sortedByCost, sortedByEarnings, sortedByYear);
        sortedByEarnings = true;
    }
    else if (typeOfProperty == "year")
    {
        sort_by_year(films, sortedByCost, sortedByEarnings, sortedByYear);
        sortedByYear = true;
    }
    else
    {
        std::cout << "Incorrect property!\n";
    }


}

void add_new_films(const std::string beautyFilmInfoPath, const std::string filmInfoPath)
{
    int filmsCount;
    std::cout << "Enter the number of films you want to add: ";
    std::cin >> filmsCount;
    if (filmsCount < 0)
    {
        std::cout << "Incorrect films count";
        system("pause");
        system("cls");
    }
    else if (filmsCount > 0)
    {
        for (int i = 0; i < filmsCount; ++i)
        {
            Film film;
            fill_film_info(film);
            fill_film_in_file(film, beautyFilmInfoPath, filmInfoPath);
            system("cls");
        }
    }
}


void find_a_films_with_your_property(const std::vector<Film> films)
{
    std::string typeOfProperty;
    std::cout << "Select property \n(Name, Producer Surname, Producer Name, Producer Middlename, Country, Year, Cost, Earnings):\n";
    std::cin.ignore();
    std::getline(std::cin, typeOfProperty);
    if (!is_film_property(typeOfProperty))
    {
        std::cout << "Incorrect property\n";
    }
    else
    {
        std::cout << "Enter film " << typeOfProperty << ": ";
        std::string property;
        std::getline(std::cin, property);
        system("cls");
        show_films_by_property(films, property, typeOfProperty);
    }
    system("pause");
}

void show_all_films(const std::vector<Film> films)
{
    int choice;
    std::cout << "Show all Films?(1 - Yes; 2 - No)\n";
    std::cin >> choice;
    if (choice == 1)
    {
        for (Film film : films)
        {
            show_film_info(film);
        }
        system("pause");
    }
}

void sort_films(std::vector<Film>& films, bool& sortedByCost, bool& sortedByEarnings, bool& sortedByYear)
{
    std::string typeOfProperty;
    std::cout << "By what you want to sort the films list?(cost, earnings, year)\n";
    std::cin.ignore();
    std::getline(std::cin, typeOfProperty);
    sort_films_by(films, typeOfProperty, sortedByCost, sortedByEarnings, sortedByYear);
}

void sort_by_cost(std::vector<Film>& films, bool& sortedByCost, bool& sortedByEarnings, bool& sortedByYear)
{
    std::sort(films.begin(), films.end(), [&](Film film1, Film film2)
        {
            return film1.cost < film2.cost;
        });
    sortedByEarnings = sortedByYear = false;
}

void sort_by_earnings(std::vector<Film>& films, bool& sortedByCost, bool& sortedByEarnings, bool& sortedByYear)
{
    std::sort(films.begin(), films.end(), [&](Film film1, Film film2)
        {
            return film1.earnings < film2.earnings;
        });
    sortedByCost = sortedByYear = false;
}

void sort_by_year(std::vector<Film>& films, bool& sortedByCost, bool& sortedByEarnings, bool& sortedByYear)
{
    std::sort(films.begin(), films.end(), [&](Film film1, Film film2)
        {
            return film1.year < film2.year;
        });
    sortedByEarnings = sortedByCost = false;
}


void show_film_info(const Film film)
{
    printf("Name = %s\nProducer Surname = %s\nProducer Name = %s\nProducer Middlename = %s\nCountry = %s\nYear = %d\nCost = %d$\nEarnings = %d$\n\n",
        film.name.c_str(), film.producerSurname.c_str(), film.producerName.c_str(), film.producerMiddlename.c_str(), film.country.c_str(), film.year, film.cost, film.earnings);
}

void fill_film_info(Film& film)
{
    bool allIsCorrect = false;
    while (!allIsCorrect)
    {

        std::cout << "\n\nPlease do not use the space bar!\n\n";

        std::cout << "Enter Film Name: ";
        std::cin >> film.name;
        std::cout << "Enter Producer Surname: ";
        std::cin >> film.producerSurname;
        std::cout << "Enter Producer Name: ";
        std::cin >> film.producerName;
        std::cout << "Enter Producer Middlename: ";
        std::cin >> film.producerMiddlename;
        std::cout << "Enter film Country: ";
        std::cin >> film.country;
        std::cout << "Enter Year: ";
        std::cin >> film.year;




        if (film.year < 1895 && film.year > 2022)
        {
            std::cout << "Incorrect year! (could not come out earlier than 1895 and later than 2022)";
            system("pause");
            system("cls");
            continue;
        }

        std::cout << "Enter Cost: ";
        std::cin >> film.cost;
        if (film.cost <= 0)
        {
            std::cout << "Incorrect value! Can't be smaller than 0";
            system("pause");
            system("cls");
            continue;
        }

        std::cout << "Enter Earnings: ";
        std::cin >> film.earnings;
        if (film.cost <= 0)
        {
            std::cout << "Incorrect value! Can't be smaller than 0";
            system("pause");
            system("cls");
            continue;
        }
        allIsCorrect = true;
    }

}

bool is_film_property(const std::string property)
{
    if (property == "name")
        return true;
    else if (property == "Producer Surname")
        return true;
    else if (property == "Producer Name")
        return true;
    else if (property == "Producer Middlename")
        return true;
    else if (property == "Country")
        return true;
    else if (property == "Year")
        return true;
    else if (property == "Cost")
        return true;
    else if (property == "Earnings")
        return true;
    return false;
}

#include "Database.h"

#include <iostream>
#include <ranges>

/*!
 * @brief Фасад (Fasade) - позволяющий скрыть сложность системы путём сведения всех возможных внешних вызовов к одному объекту, делегирующему их соответствующим объектам системы
 * унифицированный интерфейс для набора интерфейсов в подсистеме. Фасад определяет интерфейс более высокого уровня, который упрощает использование подсистемы. Это можно использовать для упрощения ряда сложных взаимодействий с объектами в едином интерфейсе.
 * предоставить более простой интерфейс для всей подсистемы, состоящей из множества объектов
 */

namespace utils
{
    inline void tolower(std::string &iSource)
    {
        std::transform(iSource.begin(), iSource.end(), iSource.begin(), ::tolower);
    }

    inline unsigned constexpr Hash(const char *iSource)
    {
        return *iSource ? static_cast<unsigned int>(*iSource) + 33 * Hash(iSource + 1) : 5381;
    }
}

auto& db = DatabaseFacade::Instance();

namespace database
{
    void AddUser()
    {
        while (true)
        {
            std::cout << "user - добавить пользователя, users - добавить пользователей, return/назад - вернуться: " << std::endl;
            std::string input;
            std::cin >> input;
            utils::tolower(input);
            switch (utils::Hash(input.c_str()))
            {
                case utils::Hash("user") :
                {
                    std::cout << "Введите фамилию: " <<  std::endl;
                    std::string surname;
                    std::cin >> surname;
                    std::cout << "Введите имя: " <<  std::endl;
                    std::string name;
                    std::cin >> name;
                    std::cout << "Введите отчество: " <<  std::endl;
                    std::string patronymic;
                    std::cin >> patronymic;
                    std::cout << "Введите пол: " <<  std::endl;
                    std::string sex;
                    std::cin >> sex;
                    std::cout << "Введите возраст: " <<  std::endl;
                    unsigned age;
                    std::cin >> age;
                    db.AddUser(surname, name, patronymic, sex, age);
                }

                case utils::Hash("users") :
                {
                    std::cout << "Кол-во пользователей: " <<  std::endl;
                    unsigned count;
                    std::cin >> count;
                    std::vector<DatabaseFacade::Data> users;
                    for (const auto _ : std::views::iota(0u, count))
                    {
                        std::cout << "Введите фамилию: " <<  std::endl;
                        std::string surname;
                        std::cin >> surname;
                        std::cout << "Введите имя: " <<  std::endl;
                        std::string name;
                        std::cin >> name;
                        std::cout << "Введите отчество: " <<  std::endl;
                        std::string patronymic;
                        std::cin >> patronymic;
                        std::cout << "Введите пол: " <<  std::endl;
                        std::string sex;
                        std::cin >> sex;
                        std::cout << "Введите возраст: " <<  std::endl;
                        unsigned age;
                        std::cin >> age;
                        users.emplace_back(surname, name, patronymic, sex, age);
                    }
                    
                    db.AddUsers(users);
                    break;
                }
                case utils::Hash("return") :
                case utils::Hash("назад") :
                    return;
            }
        }
    }

    void DeleteUser()
    {
        while (true)
        {
            std::cout << "id - удалить пользователя по id, "
            " anthroponym - удалить пользователя по фамилии, имени, отчеству, "
            "return/назад - вернуться: " << std::endl;
            std::string input;
            std::cin >> input;
            utils::tolower(input);
            switch (utils::Hash(input.c_str()))
            {
                case utils::Hash("id") :
                {
                    std::cout << "Введите id: " <<  std::endl;
                    unsigned key;
                    std::cin >> key;
                    db.DeleteUser(key);
                }
                    
                case utils::Hash("anthroponym") :
                {
                    std::cout << "Введите фамилию: " <<  std::endl;
                    std::string surname;
                    std::cin >> surname;
                    std::cout << "Введите имя: " <<  std::endl;
                    std::string name;
                    std::cin >> name;
                    std::cout << "Введите отчество: " <<  std::endl;
                    std::string patronymic;
                    std::cin >> patronymic;
                    
                    db.DeleteUser(surname, name, patronymic);
                    break;
                }
                case utils::Hash("return") :
                case utils::Hash("назад") :
                    return;
            }
        }
    }
}


int main(int argc, const char * argv[])
{
    auto& db = DatabaseFacade::Instance();
    
    if (!db.Load())
        return EXIT_FAILURE;
    
    if (!db.Connection())
        return EXIT_FAILURE;

    if (!db.IsOpen())
        return EXIT_FAILURE;
    
    while (true)
    {
        try
        {
            std::cout << "Введите номер операции ("
            "createtable - создать таблицу, "
            "deletetable - удалить таблицу, "
            "checktableempty - проверить таблицу на пустоту, "
            "adduser - добавить пользователя(ей)"
            "deleteuser - добавить пользователя(ей)"
            "esc/выход - выход из приложения): " << std::endl;
            std::string input;
            std::cin >> input;
            utils::tolower(input);
            switch (utils::Hash(input.c_str()))
            {
                case utils::Hash("createtable") :
                {
                    db.CreateTable();
                }
                case utils::Hash("deletetable") :
                {
                    db.DeleteTable();
                    break;
                }
                case utils::Hash("checktableempty") :
                {
                    db.IsTableEmpty();
                    break;
                }
                case utils::Hash("adduser") :
                {
                    database::AddUser();
                    break;
                }
                case utils::Hash("5") :
                {
                    break;
                }
                case utils::Hash("6") :
                {
                    break;
                }
                case utils::Hash("7") :
                {
                    break;
                }
                case utils::Hash("8") :
                {
                    break;
                }
                case utils::Hash("9") :
                {
                    break;
                }
                case utils::Hash("10") :
                {
                    break;
                }
                case utils::Hash("11") :
                {
                    break;
                }
                case utils::Hash("12") :
                {
                    break;
                }
                case utils::Hash("13") :
                {
                    break;
                }
                case utils::Hash("esc") :
                case utils::Hash("выход") :
                    std::cout << "Вы вышли из программы" << std::endl;
                    exit(0);
            }
        }
        catch (...)
        {
            std::cerr << "Неизвестная ошибка!" << std::endl;
        }
    }
    
    db.IsTableEmpty();
    db.Disconnect();
    
    
    return EXIT_SUCCESS;
}

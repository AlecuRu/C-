```cpp
#include <iostream>
#include <fstream>
#include <array>
#include <string>
#include <sstream>
#include <vector>

enum class Gender { Male, Female };

struct Person {
    std::array<char, 256> name;
    int age;
    Gender gender;
};

// Сериализация строки
void serializeString(const std::array<char, 256>& str, std::ostream& os) {
    os << str.data();
}

// Сериализация целого числа
void serializeInt(int value, std::ostream& os) {
    os << value;
}

// Сериализация enum Gender
void serializeGender(Gender gender, std::ostream& os) {
    os << (gender == Gender::Male ? 'M' : 'F');
}

// Сериализация объекта Person
void serializePerson(const Person& person, std::ostream& os) {
    serializeString(person.name, os);
    os << "," << person.age << ",";
    serializeGender(person.gender, os);
    os << "\n";
}

// Десериализация строки
std::array<char, 256> deserializeString(std::istream& is) {
    std::array<char, 256> buffer;
    is.getline(buffer.data(), buffer.size(), ',');
    return buffer;
}

// Десериализация целого числа
int deserializeInt(std::istream& is) {
    std::string value;
    std::getline(is, value, ',');
    return std::stoi(value);
}

// Десериализация enum Gender
Gender deserializeGender(std::istream& is) {
    char genderChar;
    is.get(genderChar);
    return (genderChar == 'M') ? Gender::Male : Gender::Female;
}

// Десериализация объекта Person
Person deserializePerson(std::istream& is) {
    return { deserializeString(is), deserializeInt(is), deserializeGender(is) };
}

// Структура для результата десериализации
struct DeserializationResult {
    bool success;
    Person value;
};

// Общая десериализация
DeserializationResult deserialize(std::istream& is) {
    try {
        return { true, deserializePerson(is) };
    } catch (const std::exception& e) {
        return { false, {} };
    }
}

// Сериализация массива объектов Person
void serializePeople(const std::vector<Person>& people, std::ostream& os) {
    for (const auto& person : people) {
        serializePerson(person, os);
    }
}

// Десериализация массива объектов Person
std::vector<Person> deserializePeople(std::istream& is) {
    std::vector<Person> people;
    std::string line;
    while (std::getline(is, line)) {
        std::istringstream iss(line);
        people.push_back(deserializePerson(iss));
    }
    return people;
}

int main() {
    // Пример использования

    // Сериализация данных в файл
    std::ofstream outFile("data.csv");
    Person person1 = { "John", 25, Gender::Male };
    Person person2 = { "Alice", 30, Gender::Female };
    serializePeople({ person1, person2 }, outFile);
    outFile.close();

    // Десериализация данных из файла, изменение и перезапись
    std::ifstream inFile("data.csv");
    std::vector<Person> people = deserializePeople(inFile);
    inFile.close();

    people[0].age = 26;
    people.push_back({ "Bob", 28, Gender::Male });

    // Перезапись в файл
    std::ofstream outFileUpdated("data_updated.csv");
    serializePeople(people, outFileUpdated);
    outFileUpdated.close();

    return 0;
}
```
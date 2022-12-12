#include <iostream>
#include <exception>
#include <string>

class BadLeght : public std::exception {
public:
    virtual const char* what() const noexcept {
        return "You entered a word of forbidden length! Goodbye";
    }
};

int function(const std::string& str, const int& forbidden_length) {
    if (str.size() == forbidden_length)
        throw BadLeght();
    return str.size();
}

int main() {
    int forbidden_lenght = 0;
    std::string str;
    std::cout << "Enter forbidden length: ";
    std::cin >> forbidden_lenght;
    while (true) {
        std::cout << "Enter a word: ";
        std::cin >> str;
        try {
            int i = function(str, forbidden_lenght);
            std::cout << "The length of the word " << str << " is " <<
                i << '\n';
        }
        catch (const BadLeght& ex) { std::cout << ex.what() << '\n'; break; }
    }
    return 0;
}
#include <iostream>

class OutOfRangeException : public std::exception {
private:
    int id;
    int value;
    std::string message;
public:
    OutOfRangeException(int id, int value) noexcept: id(id), value(value) {
        message = "The parameter " + std::to_string(this->id) + " is "
                  + std::to_string(this->value) + " which is out of range (0-100).";
    }

    const char *what() const noexcept override {
        return message.c_str();
    }
};

double calculateAverage(int mark1, int mark2, int mark3, int mark4) {
    if (mark1 < 0 or mark1 > 100) {
        throw OutOfRangeException(1, mark1);
    }
    if (mark2 < 0 or mark2 > 100) {
        throw OutOfRangeException(2, mark2);
    }
    if (mark3 < 0 or mark3 > 100) {
        throw OutOfRangeException(3, mark3);
    }
    if (mark4 < 0 or mark4 > 100) {
        throw OutOfRangeException(4, mark4);
    }

    return (mark1 + mark2 + mark3 + mark4) / 4.0;
}


int main() {
    int mark1, mark2, mark3, mark4;

    std::string con;
    do {
        std::cout << "Please enter marks for four courses (0-100): ";
        std::cin >> mark1 >> mark2 >> mark3 >> mark4;

        try {
            double average = calculateAverage(mark1, mark2, mark3, mark4);
            std::cout << "The average of the four courses is: " << average << std::endl;
        } catch (const OutOfRangeException &e) {
            std::cerr << e.what() << std::endl;
        }

        std::cout << "Would you want to enter another marks for 4 courses? (y/n): ";
        std::cin >> con;

    } while (con == "y");

    std::cout << "Bye, see you next time." << std::endl;

    return 0;
}
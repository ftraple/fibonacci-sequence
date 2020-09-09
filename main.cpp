#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::string addString(const std::string &str_a, const std::string &str_b) {
    std::string result{""};
    int counter_a = str_a.size() - 1;
    int counter_b = str_b.size() - 1;
    int carry{0};
    while (counter_a >= 0 || counter_b >= 0 || carry > 0) {
        // Get A value
        int value_a = 0;
        if (counter_a >= 0) {
            value_a = str_a[counter_a] - 48;
            counter_a--;
        }
        // Get B value
        int value_b = 0;
        if (counter_b >= 0) {
            value_b = str_b[counter_b] - 48;
            counter_b--;
        }
        // Add
        int total = value_a + value_b + carry;
        if (total < 10) {
            result.push_back(char(total + 48));
            carry = 0;
        } else {
            result.push_back(char(total - 10 + 48));
            carry = 1;
        }
    }
    std::reverse(result.begin(), result.end());
    return result;
}

class BigInt {
public:
    BigInt(const std::string &value) : m_value(value) {}

    size_t size() { return m_value.size(); }

    BigInt operator+(const BigInt &big_int) {
        return BigInt(addString(m_value, big_int.m_value));
    }

    friend std::ostream &operator<<(std::ostream &out, const BigInt &big_int);

private:
    std::string m_value;
};

std::ostream &operator<<(std::ostream &out, const BigInt &big_int) {
    out << big_int.m_value;
    return out;
}

BigInt fib(int n) {
    BigInt lastTwo[2] = {std::string{"0"}, std::string{"1"}};
    for (int i = 2; i < n; i++) {
        BigInt new_fib = lastTwo[0] + lastTwo[1];
        lastTwo[0] = lastTwo[1];
        lastTwo[1] = new_fib;
        std::cout << "fib(" << i + 1 << ") size =" << new_fib.size() << std::endl;
    }
    return (n == 1) ? lastTwo[0] : lastTwo[1];
}

int main() {
    int n = 10;
    BigInt result = fib(n);
    std::cout << "uint64_t= " << UINT64_MAX << std::endl;
    // Save result to a file
    std::stringstream file_name;
    file_name << "results/fib_" << n << "_size_" << result.size() << ".txt";
    std::ofstream file(file_name.str());
    file << result;
    file.close();
    exit(EXIT_SUCCESS);
}
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class IPv4 {
private:
    unsigned char bytes[4]{};

public:
    IPv4() : bytes{0, 0, 0, 0} {}

    IPv4(const unsigned char b1, const unsigned char b2, const unsigned char b3, const unsigned char b4)
        : bytes{b1, b2, b3, b4} {}

    explicit IPv4(const unsigned int ip) {
        bytes[0] = ip >> 24 & 0xFF;
        bytes[1] = ip >> 16 & 0xFF;
        bytes[2] = ip >> 8 & 0xFF;
        bytes[3] = ip & 0xFF;
    }

    explicit IPv4(const std::string& ip_str) {
        std::istringstream iss(ip_str);
        std::string token;
        int i = 0;

        while (std::getline(iss, token, '.') && i < 4) {
            int byte = std::stoi(token);
            bytes[i++] = static_cast<unsigned char>(byte);
        }
    }

    explicit operator unsigned int() const {
        return static_cast<unsigned int>(bytes[0]) << 24 |
               static_cast<unsigned int>(bytes[1]) << 16 |
               static_cast<unsigned int>(bytes[2]) << 8 |
               static_cast<unsigned int>(bytes[3]);
    }

    bool operator==(const IPv4& other) const {
        return static_cast<unsigned int>(*this) == static_cast<unsigned int>(other);
    }

    bool operator!=(const IPv4& other) const {
        return !(*this == other);
    }

    bool operator<(const IPv4& other) const {
        return static_cast<unsigned int>(*this) < static_cast<unsigned int>(other);
    }

    bool operator<=(const IPv4& other) const {
        return static_cast<unsigned int>(*this) <= static_cast<unsigned int>(other);
    }

    bool operator>(const IPv4& other) const {
        return static_cast<unsigned int>(*this) > static_cast<unsigned int>(other);
    }

    bool operator>=(const IPv4& other) const {
        return static_cast<unsigned int>(*this) >= static_cast<unsigned int>(other);
    }

    IPv4& operator++() {
        auto ip = static_cast<unsigned int>(*this);
        ++ip;
        *this = IPv4(ip);
        return *this;
    }
    
    IPv4 operator++(int) {
        IPv4 temp = *this;
        ++*this;
        return temp;
    }
    
    friend std::istream& operator>>(std::istream& is, IPv4& ip) {
        std::string ip_str;
        is >> ip_str;
        ip = IPv4(ip_str);
        return is;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const IPv4& ip) {
        os << static_cast<int>(ip.bytes[0]) << "."
           << static_cast<int>(ip.bytes[1]) << "."
           << static_cast<int>(ip.bytes[2]) << "."
           << static_cast<int>(ip.bytes[3]);
        return os;
    }
};

std::vector<IPv4> get_ip_range(const IPv4& start, const IPv4& end) {
    std::vector<IPv4> result;
    IPv4 current = start;

    while (current <= end) {
        result.push_back(current);
        ++current;
    }

    return result;
}

int main() {
    IPv4 start_ip, end_ip;

    std::cout << "Enter start IP address: ";
    std::cin >> start_ip;

    std::cout << "Enter end IP address: ";
    std::cin >> end_ip;

    std::vector<IPv4> ip_range = get_ip_range(start_ip, end_ip);

    std::cout << "\nIP addresses in range " << start_ip << " - " << end_ip << ":\n";
    for (const auto& ip : ip_range) {
        std::cout << ip << '\n';
    }

    std::cout << "\nTotal IP addresses: " << ip_range.size() << '\n';

    return 0;
}

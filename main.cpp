#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

class Vector3F {
private:
    float x, y, z;
    int State;

public:
    Vector3F() : x(0.0f), y(0.0f), z(0.0f), State(0) {}
    Vector3F(float val) : x(val), y(val), z(val), State(0) {}
    Vector3F(float _x, float _y, float _z) : x(_x), y(_y), z(_z), State(0) {}
    Vector3F(float* arrPtr) : State(0) {
        if (arrPtr == nullptr) {
            State = -1;
        } else {
            x = arrPtr[0];
            y = arrPtr[1];
            z = arrPtr[2];
        }
    }

    ~Vector3F() {
        cout << "Vector3F object is being destroyed. State: " << State << endl;
    }

    Vector3F& operator++() {
        ++x; ++y; ++z;
        return *this;
    }
    Vector3F operator++(int) {
        Vector3F temp = *this;
        ++(*this);
        return temp;
    }
    Vector3F& operator--() {
        --x; --y; --z;
        return *this;
    }
    Vector3F operator--(int) {
        Vector3F temp = *this;
        --(*this);
        return temp;
    }
    bool operator!() const {
        return (x != 0.0f || y != 0.0f || z != 0.0f);
    }
    Vector3F operator~() const {
        return Vector3F(-x, -y, -z);
    }
    Vector3F operator-() const {
        return Vector3F(-x, -y, -z);
    }

    Vector3F& operator=(const Vector3F& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            z = other.z;
            State = other.State;
        }
        return *this;
    }
    Vector3F& operator+=(const Vector3F& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
    Vector3F& operator-=(const Vector3F& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }
    Vector3F& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
        return *this;
    }
    Vector3F& operator/=(float scalar) {
        if (scalar != 0.0f) {
            x /= scalar;
            y /= scalar;
            z /= scalar;
        } else {
            State = -2;
        }
        return *this;
    }
    Vector3F& operator&=(const Vector3F& other) {
        float newX = y * other.z - z * other.y;
        float newY = z * other.x - x * other.z;
        float newZ = x * other.y - y * other.x;
        x = newX;
        y = newY;
        z = newZ;
        return *this;
    }
    Vector3F& operator%=(int divisor) {
        if (divisor != 0) {
            x = static_cast<int>(x) % divisor;
            y = static_cast<int>(y) % divisor;
            z = static_cast<int>(z) % divisor;
        } else {
            State = -3;
        }
        return *this;
    }

    friend Vector3F operator+(Vector3F lhs, const Vector3F& rhs) {
        lhs += rhs;
        return lhs;
    }
    friend Vector3F operator-(Vector3F lhs, const Vector3F& rhs) {
        lhs -= rhs;
        return lhs;
    }
    friend Vector3F operator*(Vector3F vec, float scalar) {
        vec *= scalar;
        return vec;
    }
    friend Vector3F operator*(float scalar, Vector3F vec) {
        return vec * scalar;
    }
    friend Vector3F operator/(Vector3F vec, float scalar) {
        vec /= scalar;
        return vec;
    }
    friend Vector3F operator%(Vector3F vec, int divisor) {
        vec %= divisor;
        return vec;
    }

    bool operator==(const Vector3F& other) const {
        return (x == other.x && y == other.y && z == other.z);
    }
    bool operator!=(const Vector3F& other) const {
        return !(*this == other);
    }

    float& operator[](int index) {
        if (index == 0) return x;
        else if (index == 1) return y;
        else if (index == 2) return z;
        else {
            State = -4;
            return z;
        }
    }

    friend ostream& operator<<(ostream& os, const Vector3F& vec);
    friend istream& operator>>(istream& is, Vector3F& vec);
};

ostream& operator<<(ostream& os, const Vector3F& vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}

istream& operator>>(istream& is, Vector3F& vec) {
    is >> vec.x >> vec.y >> vec.z;
    return is;
}

class AssociatedEntities {
private:
    unordered_map<string, string> phonebook;

public:
    void addEntry(const string& phoneNumber, const string& fullName) {
        phonebook[phoneNumber] = fullName;
    }

    string operator[](const string& phoneNumber) {
        if (phonebook.find(phoneNumber) != phonebook.end()) {
            return phonebook[phoneNumber];
        } else {

            return "Error: Entry not found";
        }
    }

    friend istream& operator>>(istream& input, AssociatedEntities& ae) {
        string phoneNumber, fullName;
        cout << "Enter phone number: ";
        input >> phoneNumber;
        cout << "Enter full name: ";
        input.ignore();
        getline(input, fullName);
        ae.addEntry(phoneNumber, fullName);
        return input;
    }

    friend ostream& operator<<(ostream& output, const AssociatedEntities& ae) {
        for (const auto& entry : ae.phonebook) {
            output << "Phone Number: " << entry.first << ", Full Name: " << entry.second << endl;
        }
        return output;
    }
};

void firstTask() {
    Vector3F vec1;
    Vector3F vec2(2.0f);
    float arr[3] = {1.0f, 2.0f, 3.0f};
    Vector3F vec3(arr);

    cout << "Vector1: " << vec1 << endl;
    cout << "Vector2: " << vec2 << endl;
    cout << "Vector3: " << vec3 << endl;

    ++vec1;
    cout << "Vector1 after prefix increment: " << vec1 << endl;

    vec2++;
    cout << "Vector2 after postfix increment: " << vec2 << endl;

    --vec3;
    cout << "Vector3 after prefix decrement: " << vec3 << endl;

    vec1--;
    cout << "Vector1 after postfix decrement: " << vec1 << endl;

    cout << "Logical NOT (!) result for Vector1: " << !vec1 << endl;
    cout << "Logical NOT (!) result for Vector2: " << !vec2 << endl;

    cout << "Bitwise NOT (~) result for Vector3: " << ~vec3 << endl;
    cout << "Negative (-) result for Vector1: " << -vec1 << endl;

    Vector3F vec4;
    vec4 = vec1;
    cout << "Vector4 after assignment from Vector1: " << vec4 << endl;

    vec4 += vec2;
    cout << "Vector4 after addition with Vector2: " << vec4 << endl;

    vec4 -= vec3;
    cout << "Vector4 after subtraction with Vector3: " << vec4 << endl;

    vec4 *= 2.0f;
    cout << "Vector4 after multiplication by scalar 2.0: " << vec4 << endl;

    vec4 /= 2.0f;
    cout << "Vector4 after division by scalar 2.0: " << vec4 << endl;

    vec4 &= vec3;
    cout << "Vector4 after vector product with Vector3: " << vec4 << endl;

    vec4 %= 2;
    cout << "Vector4 after modulo operation with divisor 2: " << vec4 << endl;

    Vector3F vec5 = vec1 + vec2;
    cout << "Vector5 after addition of Vector1 and Vector2: " << vec5 << endl;

    Vector3F vec6 = vec2 - vec3;
    cout << "Vector6 after subtraction of Vector2 from Vector3: " << vec6 << endl;

    Vector3F vec7 = vec3 * 2.0f;
    cout << "Vector7 after multiplication of Vector3 by scalar 2.0: " << vec7 << endl;

    Vector3F vec8 = vec4 / 2.0f;
    cout << "Vector8 after division of Vector4 by scalar 2.0: " << vec8 << endl;

    Vector3F vec9 = vec5 % 3;
    cout << "Vector9 after modulo operation of Vector5 with divisor 3: " << vec9 << endl;

    cout << "Equality check between Vector1 and Vector2: " << (vec1 == vec2) << endl;
    cout << "Equality check between Vector1 and Vector4: " << (vec1 == vec4) << endl;

    cout << "Value of the first element of Vector1: " << vec1[0] << endl;

    cout << "Enter three float values for a new vector (x, y, z): ";
    cin >> vec1;
    cout << "New vector after input: " << vec1 << endl;
}

void secondTask() {
    AssociatedEntities phonebook;

    phonebook.addEntry("123456789", "John Doe");
    phonebook.addEntry("987654321", "Jane Smith");

    cout << "Phonebook Entries:" << endl;
    cout << phonebook << endl;

    cout << "Search result for phone number 123456789: " << phonebook["123456789"] << endl;
    cout << "Search result for phone number 999999999: " << phonebook["999999999"] << endl;
}
int main() {
   firstTask();
   secondTask();
    return 0;
}


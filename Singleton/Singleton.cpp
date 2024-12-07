
#include <iostream>
#include <type_traits>
#include <concepts>

// Define a concept to ensure the type is default-constructible and non-copyable
template <typename T>
concept SingletonType = std::is_default_constructible_v<T> &&
                        !std::is_copy_constructible_v<T> &&
                        !std::is_move_constructible_v<T>;

// Singleton class template
template <SingletonType T>
class Singleton {
public:
    // Get the Singleton instance
    static T& getInstance() requires SingletonType<T> {
        static T instance;
        return instance;
    }

private:
    Singleton() = default;  // Private constructor to prevent instantiation
    ~Singleton() = default; // Private destructor

    // Delete copy and move operations
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    Singleton(Singleton&&) = delete;
    Singleton& operator=(Singleton&&) = delete;
};

// Example class that meets the SingletonType concept
class MySingleton {
public:
    MySingleton() = default;

    void showMessage() const {
        std::cout << "Hello from MySingleton!" << std::endl;
    }

    // Deleted copy and move operations to satisfy SingletonType
    MySingleton(const MySingleton&) = delete;
    MySingleton& operator=(const MySingleton&) = delete;
    MySingleton(MySingleton&&) = delete;
    MySingleton& operator=(MySingleton&&) = delete;
};

int main() {
    // Access the Singleton instance and call its method
    MySingleton& instance = Singleton<MySingleton>::getInstance();
    instance.showMessage();

    // The following line would cause a compilation error due to concept constraints:
    // MySingleton anotherInstance = Singleton<MySingleton>::getInstance();

    return 0;
}


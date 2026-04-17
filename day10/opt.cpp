#include <iostream>
#include <optional>

std::optional<int> find(int id)
{
    if (id == 10)
        return 100;

    return std::nullopt;  // explicitly no value
}

int main()
{
    auto result = find(5);

    if (result)
        std::cout << "Found: " << *result << "\n";
    else
        std::cout << "Not found\n";
}


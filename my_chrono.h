#include <chrono>

namespace my_chrono
{
    using witki = std::chrono::duration<int, std::ratio<15*60,1>>;

    namespace chrono_literals
    {
        constexpr std::chrono::minutes operator "" _witek(unsigned long long w)
        {
            return std::chrono::minutes(15 * w);
        }

        constexpr std::chrono::duration<long double, std::ratio<15*60,1>> operator "" _witek(long double w)
        {
            return std::chrono::duration<long double, std::ratio<15*60,1>> (w);
        }
    }
}
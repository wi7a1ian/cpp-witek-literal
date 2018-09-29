#include <chrono>
#include <cassert>

bool are_equal(double const d1, double const d2, double const epsilon = 0.001)
{
    return std::fabs(d1 - d2) < epsilon;
}

namespace special_time
{
    enum class standard
    {
        minute,
        witek,
        kamil
    };

    template <standard S>
    class quantity
    {
        const double amount;

    public:
        constexpr explicit quantity(double const a) : amount(a) {}

        explicit operator double() const { return amount; }
    };

    template <standard S>
    inline bool operator==(quantity<S> const &lhs, quantity<S> const &rhs)
    {
        return are_equal(static_cast<double>(lhs), static_cast<double>(rhs));
    }

    template <standard S>
    inline bool operator!=(quantity<S> const &lhs, quantity<S> const &rhs)
    {
        return !(lhs == rhs);
    }

    template <standard S>
    inline bool operator<(quantity<S> const &lhs, quantity<S> const &rhs)
    {
        return static_cast<double>(lhs) < static_cast<double>(rhs);
    }

    template <standard S>
    inline bool operator>(quantity<S> const &lhs, quantity<S> const &rhs)
    {
        return rhs < lhs;
    }

    template <standard S>
    inline bool operator<=(quantity<S> const &lhs, quantity<S> const &rhs)
    {
        return !(lhs > rhs);
    }

    template <standard S>
    inline bool operator>=(quantity<S> const &lhs, quantity<S> const &rhs)
    {
        return !(lhs < rhs);
    }

    template <standard S>
    constexpr quantity<S> operator+(quantity<S> const &q1, quantity<S> const &q2)
    {
        return quantity<S>(static_cast<double>(q1) + static_cast<double>(q2));
    }

    template <standard S>
    constexpr quantity<S> operator-(quantity<S> const &q1, quantity<S> const &q2)
    {
        return quantity<S>(static_cast<double>(q1) - static_cast<double>(q2));
    }

    template <standard S, standard R>
    struct conversion_traits
    {
        static double convert(double const value) = delete;
    };

    template <>
    struct conversion_traits<standard::witek, standard::minute>
    {
        static double convert(double const value)
        {
            return value * 15;
        }
    };

    template <>
    struct conversion_traits<standard::kamil, standard::minute>
    {
        static double convert(double const value)
        {
            return value * 3600 + 1;
        }
    };

    template <>
    struct conversion_traits<standard::minute, standard::witek>
    {
        static double convert(double const value)
        {
            return value / 15;
        }
    };

    template <>
    struct conversion_traits<standard::minute, standard::kamil>
    {
        static double convert(double const value)
        {
            return (value - 1) / 3600;
        }
    };

    template <standard R, standard S>
    constexpr quantity<R> time_cast(quantity<S> const q)
    {
        return quantity<R>(conversion_traits<S, R>::convert(static_cast<double>(q)));
    }

    namespace special_time_literals
    {
        constexpr quantity<standard::witek> operator"" _witek(unsigned long long const amount)
        {
            return quantity<standard::witek>{static_cast<double>(amount)};
        }

        constexpr quantity<standard::witek> operator"" _witek(long double const amount)
        {
            return quantity<standard::witek>{static_cast<double>(amount)};
        }

        constexpr quantity<standard::kamil> operator"" _kamil(long double const amount)
        {
            return quantity<standard::kamil>{static_cast<double>(amount)};
        }
    } // namespace special_time_literals
} // namespace special_time

int main()
{
    using namespace special_time;
    using namespace special_time_literals;

    auto t1{1_witek};
    auto t2{1.5_witek};
    auto t3{3.677_kamil};

    {
        auto tf = time_cast<standard::minute>(t1);
        auto tc = time_cast<standard::witek>(tf);
        assert(t1 == tc);
    }
}

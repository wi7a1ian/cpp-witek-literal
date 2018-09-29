#include <cmath>

bool are_equal(const double d1, const double d2, const double epsilon = 0.001)
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
        constexpr explicit quantity(const double a) : amount(a) {}

        explicit operator double() const { return amount; }
    };

    template <standard S>
    inline bool operator==(const quantity<S> &lhs, const quantity<S> &rhs)
    {
        return are_equal(static_cast<double>(lhs), static_cast<double>(rhs));
    }

    template <standard S>
    inline bool operator!=(const quantity<S> &lhs, const quantity<S> &rhs)
    {
        return !(lhs == rhs);
    }

    template <standard S>
    inline bool operator<(const quantity<S> &lhs, const quantity<S> &rhs)
    {
        return static_cast<double>(lhs) < static_cast<double>(rhs);
    }

    template <standard S>
    inline bool operator>(const quantity<S> &lhs, const quantity<S> &rhs)
    {
        return rhs < lhs;
    }

    template <standard S>
    inline bool operator<=(const quantity<S> &lhs, const quantity<S> &rhs)
    {
        return !(lhs > rhs);
    }

    template <standard S>
    inline bool operator>=(const quantity<S> &lhs, const quantity<S> &rhs)
    {
        return !(lhs < rhs);
    }

    template <standard S>
    constexpr quantity<S> operator+(const quantity<S> &q1, const quantity<S> &q2)
    {
        return quantity<S>(static_cast<double>(q1) + static_cast<double>(q2));
    }

    template <standard S>
    constexpr quantity<S> operator-(const quantity<S> &q1, const quantity<S> &q2)
    {
        return quantity<S>(static_cast<double>(q1) - static_cast<double>(q2));
    }

    template <standard S, standard R>
    struct conversion_traits
    {
        static double convert(const double value) = delete;
    };

    template <>
    struct conversion_traits<standard::witek, standard::minute>
    {
        static double convert(const double value)
        {
            return value * 15;
        }
    };

    template <>
    struct conversion_traits<standard::kamil, standard::minute>
    {
        static double convert(const double value)
        {
            return value * 3600 + 1;
        }
    };

    template <>
    struct conversion_traits<standard::minute, standard::witek>
    {
        static double convert(const double value)
        {
            return value / 15;
        }
    };

    template <>
    struct conversion_traits<standard::minute, standard::kamil>
    {
        static double convert(const double value)
        {
            return (value - 1) / 3600;
        }
    };

    template <standard R, standard S>
    constexpr quantity<R> time_cast(const quantity<S> q)
    {
        return quantity<R>(conversion_traits<S, R>::convert(static_cast<double>(q)));
    }

    namespace special_time_literals
    {
        constexpr quantity<standard::witek> operator"" _witek(const unsigned long long amount)
        {
            return quantity<standard::witek>{static_cast<double>(amount)};
        }

        constexpr quantity<standard::witek> operator"" _witek(const long double amount)
        {
            return quantity<standard::witek>{static_cast<double>(amount)};
        }

        constexpr quantity<standard::kamil> operator"" _kamil(const long double amount)
        {
            return quantity<standard::kamil>{static_cast<double>(amount)};
        }
    }
}

#include <cassert>

#include "my_chrono.h"
#include "special_time.h"

void UsingSpecialType()
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

void UsingChronoType()
{
    using namespace my_chrono;
    using namespace my_chrono::chrono_literals;
    using namespace std::chrono_literals;

    assert(1_witek == 15min);

    {
        using std::chrono::duration_cast;
        auto t1{1_witek};
        auto t2{15min};
        auto tm = std::chrono::duration_cast<std::chrono::minutes>(t1);
        auto tw = std::chrono::duration_cast<witki>(tm);
        assert(t1 == tw);
    }
}

int main()
{
    UsingSpecialType();
    UsingChronoType();
}

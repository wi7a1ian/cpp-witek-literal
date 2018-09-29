#include <cassert>
#include <thread>

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

void FixControlCenterIn(std::chrono::seconds s)
{
    std::this_thread::sleep_for(s);
}

void UsingChronoType()
{
    using namespace my_chrono::chrono_literals;
    using namespace std::chrono_literals;

    assert(1_witek == 15min);

    {
        using namespace my_chrono;
        using std::chrono::duration_cast;
        auto t1{1_witek};
        auto t2{4_witki};
        auto tm = std::chrono::duration_cast<std::chrono::minutes>(t2);
        auto tw = std::chrono::duration_cast<witki>(tm);
        assert(t2 == tw);
    }

    {
        FixControlCenterIn(1_witek);
    }
}

int main()
{
    UsingSpecialType();
    UsingChronoType();
}

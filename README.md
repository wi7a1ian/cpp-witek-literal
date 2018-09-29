# cpp-witek-literal
Usage:

```cpp
#include <cassert>
#include "my_chrono.h"

using namespace my_chrono::chrono_literals;
using namespace std::chrono_literals;

void FixControlCenterIn(std::chrono::seconds s);

int main()
{
  assert(1_witek == 15min);
  assert(4_witki == 1hour);
  
  auto duration = 1_witek;
  FixControlCenterIn(duration);
}
```

Credits to ***BBQ Team***!

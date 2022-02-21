#include <rapidcheck.h>

#include <cstdlib>
#include <climits>

int main()
{
  rc::check("abs is always >= 0",
            [](int x)
            {
              RC_ASSERT(std::abs(x) >= 0);
            });
  return 0;
}
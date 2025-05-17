#include <foundation/bootstrap/bootstrap.h>
#include <fmt/core.h>

int main() {
  cupix::foundation::bootstrap::load();

  fmt::print("Hello World!\n");

  cupix::foundation::bootstrap::unload();

  return 0;
}

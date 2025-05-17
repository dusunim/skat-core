#include <foundation/bootstrap/bootstrap.h>

namespace cupix::foundation {

void load() {}

void unload() {}

bootstrap::Registrar registrar(load, unload);
}  // namespace cupix::foundation
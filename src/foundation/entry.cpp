#include <foundation/bootstrap/bootstrap.h>

namespace cupix::foundation {

void loader() {}

void unloader() {}

bootstrap::Registrar registrar(loader, unloader);
}  // namespace cupix::foundation
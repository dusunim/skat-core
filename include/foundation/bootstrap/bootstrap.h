#pragma once

#include "../visibility.h"

#include <functional>

namespace cupix::foundation::bootstrap {
FOUNDATION_VISIBLE
void load();

FOUNDATION_VISIBLE
void unload();

FOUNDATION_VISIBLE
void registerLoaderAndUnloader(const std::function<void()>& loader,
                               const std::function<void()>& unloader);

struct FOUNDATION_VISIBLE Registrar {
  Registrar(const std::function<void()>& loader, const std::function<void()>& unloader);
};
}  // namespace cupix::foundation::bootstrap
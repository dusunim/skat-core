#include <foundation/bootstrap/bootstrap.h>
#include <list>
#include <mutex>
#include <stdexcept>

namespace cupix::foundation {
static std::list<std::function<void()>> loaders_, unloaders_;
static std::mutex load_lock_;
static int32_t load_count_ = 0;

void bootstrap::load() {
  std::unique_lock lg(load_lock_);

  if (load_count_ == 0) {
    for (auto& loader : loaders_) {
      if (loader) {
        loader();
      }
    }
  }

  ++load_count_;
}

void bootstrap::unload() {
  std::unique_lock lg(load_lock_);

  auto count = --load_count_;
  if (count < 0) {
    throw std::runtime_error("unloader is called more times than that of loader.");
  } else if (count == 0) {
    for (auto& unloader : unloaders_) {
      unloader();
    }
  }
}

void bootstrap::registerLoaderAndUnloader(const std::function<void()>& loader,
                                          const std::function<void()>& unloader) {
  std::unique_lock lg(load_lock_);

  if (loader) {
    loaders_.push_back(loader);

    if (load_count_ != 0) {
      loader();
    }
  }

  if (unloader) {
    unloaders_.push_front(unloader);
  }
}

bootstrap::Registrar::Registrar(const std::function<void()>& loader,
                                const std::function<void()>& unloader) {
  registerLoaderAndUnloader(loader, unloader);
}
}  // namespace cupix::foundation
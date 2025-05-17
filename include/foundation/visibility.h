#pragma once

// specify public visibility macro
#if defined(USE_STATIC_LIBRARY)
#define FOUNDATION_VISIBLE
#else
#if defined(_WIN32) || defined(__MINGW32__) || defined(__MINGW64__) || defined(__CYGWIN__)
#if defined(__GNUC__)
#ifdef foundation_EXPORTS
#define FOUNDATION_VISIBLE __attribute__((dllexport))
#else
#define FOUNDATION_VISIBLE __attribute__((dllimport))
#endif
#else
#ifdef foundation_EXPORTS
#define FOUNDATION_VISIBLE __declspec(dllexport)
#else
#define FOUNDATION_VISIBLE __declspec(dllimport)
#endif
#endif
#else
#define FOUNDATION_VISIBLE __attribute__((visibility("default")))
#endif
#endif

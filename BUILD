package(default_visibility = ["//visibility:public"])
load(':bazel/glog.bzl', 'glog_library')
#glog_library() # Uncomment this for linux/mac

cc_library(
  name = "glog",
  deps = select({
    "@bazel_tools//src/conditions:windows": [":glogdll"],
     "//conditions:default": [":glogint"],
  })
)

cc_library(
    name = "windows_event_log_sink",
    hdrs = ["windows_event_log_sink.h"],
    linkopts = [
      "-DEFAULTLIB:ws2_32.lib",
    ]
)

cc_library(
  name = "glogwinhdrs",
  hdrs = [
    "glog/log_severity.h",
    "glog/logging.h",
    "glog/raw_logging.h",
    "glog/stl_logging.h",
    "glog/vlog_is_on.h",
  ],
  copts = ["-Isrc/windows", "-Iexternal/glog/src/windows"],
  defines = [
    "HAVE_SNPRINTF",
    "WINDOWS",
    "_WINDOWS",
    "NDEBUG",
    "GFLAGS_DLL_DECLARE_FLAG=",
    "GFLAGS_DLL_DEFINE_FLAG=",
    "GLOG_NO_ABBREVIATED_SEVERITIES",
    "GOOGLE_GLOG_DLL_DECL=",
    "GFLAGS_IS_A_DLL=0",
    "HAVE_LIB_GFLAGS",
  ],
  deps = [
    "@gflags//:gflags",
  ],
)

cc_library(
  name = "glogwin",
  hdrs = [
    "glog/log_severity.h",
    "glog/logging.h",
    "glog/raw_logging.h",
    "glog/stl_logging.h",
    "glog/vlog_is_on.h",
  ],
  srcs = [
    "src/base/commandlineflags.h",
    "src/base/googleinit.h",
    "src/glog/log_severity.h",
    "src/base/mutex.h",
    "src/windows/config.h",
    "src/demangle.cc",
    "src/demangle.h",
    "src/glog/logging.h",
    "src/glog/raw_logging.h",
    "src/glog/vlog_is_on.h",
    "src/logging.cc",
    "src/raw_logging.cc",
    "src/signalhandler.cc",
    "src/stacktrace.h",
    "src/stacktrace_generic-inl.h",
    "src/stacktrace_libunwind-inl.h",
    "src/stacktrace_powerpc-inl.h",
    "src/stacktrace_windows-inl.h",
    "src/stacktrace_x86-inl.h",
    "src/stacktrace_x86_64-inl.h",
    "src/symbolize.cc",
    "src/symbolize.h",
    "src/utilities.cc",
    "src/utilities.h",
    "src/vlog_is_on.cc",
    "src/windows/port.h",
    "src/windows/port.cc",
  ],
  copts = ["-Isrc/windows", "-Iexternal/glog/src/windows"],
  defines = [
    "HAVE_SNPRINTF",
    "WINDOWS",
    "_WINDOWS",
    "NDEBUG",
    "GFLAGS_DLL_DECLARE_FLAG=",
    "GFLAGS_DLL_DEFINE_FLAG=",
    "GLOG_NO_ABBREVIATED_SEVERITIES",
    "GOOGLE_GLOG_DLL_DECL=",
    "GFLAGS_IS_A_DLL=0",
    "HAVE_LIB_GFLAGS",
  ],
  deps = [
    "@gflags//:gflags",
  ],
)

load("//:windows_dll_library.bzl", "windows_dll_library")
windows_dll_library(
  name = "glogdll",
  copts = ["-Isrc/windows", "-Iexternal/glog/src/windows"],
  hdrs = [
    "glog/log_severity.h",
    "glog/logging.h",
    "glog/raw_logging.h",
    "glog/stl_logging.h",
    "glog/vlog_is_on.h",
  ],
  srcs = [
    "src/base/commandlineflags.h",
    "src/base/googleinit.h",
    "src/glog/log_severity.h",
    "src/base/mutex.h",
    "src/windows/config.h",
    "src/demangle.cc",
    "src/demangle.h",
    "src/glog/logging.h",
    "src/glog/raw_logging.h",
    "src/glog/vlog_is_on.h",
    "src/logging.cc",
    "src/raw_logging.cc",
    "src/signalhandler.cc",
    "src/stacktrace.h",
    "src/stacktrace_generic-inl.h",
    "src/stacktrace_libunwind-inl.h",
    "src/stacktrace_powerpc-inl.h",
    "src/stacktrace_windows-inl.h",
    "src/stacktrace_x86-inl.h",
    "src/stacktrace_x86_64-inl.h",
    "src/symbolize.cc",
    "src/symbolize.h",
    "src/utilities.cc",
    "src/utilities.h",
    "src/vlog_is_on.cc",
    "src/windows/port.h",
    "src/windows/port.cc",
  ],
  defines = [
    "HAVE_SNPRINTF",
    "WINDOWS",
    "_WINDOWS",
    "NDEBUG",
    "GFLAGS_DLL_DECLARE_FLAG=",
    "GFLAGS_DLL_DEFINE_FLAG=",
    "GLOG_NO_ABBREVIATED_SEVERITIES",
    'GOOGLE_GLOG_DLL_DECL="__declspec(dllexport)"',
    "GOOGLE_GLOG_IS_A_DLL=1",
    "GFLAGS_IS_A_DLL=0",
    "HAVE_LIB_GFLAGS",
  ],
  deps = [
    "@gflags//:gflags",
  ],
)

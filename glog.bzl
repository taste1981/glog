load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

def load_deps_for_glog_gflags():
  http_archive(
      name = "rules_cc",
      sha256 = "36fa66d4d49debd71d05fba55c1353b522e8caef4a20f8080a3d17cdda001d89",
      strip_prefix = "rules_cc-0d5f3f2768c6ca2faca0079a997a97ce22997a0c",
      urls = [
          "https://mirror.bazel.build/github.com/bazelbuild/rules_cc/archive/0d5f3f2768c6ca2faca0079a997a97ce22997a0c.zip",
          "https://github.com/bazelbuild/rules_cc/archive/0d5f3f2768c6ca2faca0079a997a97ce22997a0c.zip",
      ],
  )

  git_repository(
      name = "gflags",
      commit = "7e709881881c2663569cd49a93e5c8d9228d868e",
      remote = "https://github.intel.com/mdharmap/gflags.git",
  )

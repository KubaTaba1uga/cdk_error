# C Development Kit: Error
# ******************************************************************************
# *    Project
# ******************************************************************************
project(
  'cdk_error',
  'c',
  version : '1.0.1',
  meson_version: '>=1.1',
  default_options: [
    'werror=true',
    'c_std=c11',
  ],
)
project_description = 'An errno like mechanism with additional string messages, backtraces, and a try-catch mechanism written in C.'

project_headers = [
  'include/cdk_error.h'
]

project_source_files = [
  'src/cdk_error.c'
]

build_args = [
]

# ******************************************************************************
# *    Library
# ******************************************************************************
public_headers = include_directories('include')

build_args += [
  '-DPROJECT_NAME=' + meson.project_name(),
  '-DPROJECT_VERSION=' + meson.project_version(),
]

project_target = shared_library(
  meson.project_name(),
  project_source_files,
  install : true,
  c_args : build_args,
  include_directories : public_headers,
)

# Make this library usable as a Meson subproject.
project_dep = declare_dependency(
  include_directories: public_headers,
  link_with : project_target
)
set_variable(meson.project_name() + '_dep', project_dep)

# Make this library usable from the system's
# package manager.
install_headers(project_headers, subdir : meson.project_name())

pkg_mod = import('pkgconfig')
pkg_mod.generate(
  name : meson.project_name(),
  filebase : meson.project_name(),
  description : project_description,
  subdirs : meson.project_name(),
  libraries : project_target,
)


# ******************************************************************************
# *    Tests
# ******************************************************************************
if get_option('tests')
    subdir('test')
endif

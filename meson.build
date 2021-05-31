project(
    'LedController',
    'c', 
    'cpp',
    default_options : [
        'c_std=c11', 
        'cpp_std=c++17',
        'b_lto=true',
        'b_pgo=generate',
        'b_coverage=false',
    ],
    version:'0.4.1',
    meson_version: '>= 0.54.0',
)

CC = meson.get_compiler('c')

LedController_deps = [
    dependency('ArduinoRaspi', required: true, fallback: 'ArduinoRaspi'),
]

incdir = include_directories('src')

sources = [
    'src/implementations/LedController_MAX72XX.cpp',
    'src/SPIAbstraction.cpp',
]

LedController = library(
    'LedController',
    sources,
    version : meson.project_version(),
    soversion : '0',
    include_directories : incdir,
    dependencies: LedController_deps,
    install : true,
)

LedController_dep = declare_dependency(
    include_directories : incdir,
    link_with : LedController,
    dependencies : LedController_deps,
    version: meson.project_version(),
)

install_subdir('include', install_dir : 'include/LedController', strip_directory : true)

pkg = import('pkgconfig')
pkg.generate(LedController)

meson.override_dependency('LedController',LedController_dep)

#if not get_option('no-data')
#    install_subdir('data', install_dir : get_option('datadir') / 'libtrainsim')
#endif

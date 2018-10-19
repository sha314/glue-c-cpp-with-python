from distutils.core import setup, Extension

src_directory = 'src'

source_list = [src_directory + '/ext3.cpp']

module1 = Extension(
	'myextension',
	include_dirs = ['/usr/local/include'],
	libraries = ['pthread'],
	sources=source_list,
	language="c++",  # so that the compiler knows about the language
	extra_compile_args=["-std=c++11"],
	extra_link_args=["-std=c++11"]
	)
	
setup(
	name = 'myextension',
	version ='1.0',
	description='Python C api example',
	author='Shahnoor',
	url='not provided',
	ext_modules=[module1]
	)

from distutils.core import setup, Extension
import os
homedir = os.environ['HOME']  # get the home_directory
# print (homedir)

scr_dir = 'src'
source_list = [scr_dir + '/ext3.cpp']

include_directory_list = [
		'/usr/local/include',
		homedir + '/.local/lib/python3.6/site-packages/numpy/core/include/numpy/'
		]

module1 = Extension(
	'myextension',
	include_dirs = include_directory_list,
	libraries = ['pthread'],
	sources= source_list,
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

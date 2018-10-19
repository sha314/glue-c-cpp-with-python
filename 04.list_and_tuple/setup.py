from distutils.core import setup, Extension

scr_dir = 'src'
source_list = [scr_dir + '/ext3.cpp']

module1 = Extension(
	'myextension',
	include_dirs = ['/usr/local/include'],
	libraries = ['pthread'],
	sources= source_list
	)
	
setup(
	name = 'myextension',
	version ='1.0',
	description='Python C api example',
	author='Shahnoor',
	url='not provided',
	ext_modules=[module1]
	)

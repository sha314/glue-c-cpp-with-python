from distutils.core import setup, Extension


src_directory = 'src'

module1 = Extension(
	'myextension',
	include_dirs = ['/usr/local/include'],
	libraries = ['pthread'],
	sources=[src_directory + '/ext3.c'],
	)
	
setup(
	name = 'myextension',
	version ='1.0',
	description='Python C api example',
	author='Shahnoor',
	url='not provided',
	ext_modules=[module1]
	)

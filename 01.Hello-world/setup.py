from distutils.core import setup, Extension

module1 = Extension(
	'myextension',
	include_dirs = ['/usr/local/include'],
	libraries = ['pthread'],
	sources=['ext3.c']
	)
	
setup(
	name = 'myextension',
	version ='1.0',
	description='Python C api example',
	author='Shahnoor',
	url='not provided',
	ext_modules=[module1]
	)

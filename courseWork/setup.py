"""
This is a setup.py script generated by py2applet

Usage:
    python setup.py py2app
"""

from setuptools import setup

APP = ['course.py']
DATA_FILES = ["GUI.py", "GenericMatrixOperations.py", "Solutions.py",
              "White.png", "WhiteWithQ.png", "BlackWithQ.png", "Black.png"]
OPTIONS = {}

setup(
    app=APP,
    data_files=DATA_FILES,
    options={'py2app': OPTIONS},
    setup_requires=['py2app'],
)
from setuptools import setup, find_packages

setup(
    name="faust-python",
    version="0.1.0",
    description="Python bindings for DspFaust using cppyy",
    packages=find_packages(),
    install_requires=[
        "cppyy>=1.9.0",
        "numpy>=1.19.0",
    ],
    python_requires=">=3.7",
)

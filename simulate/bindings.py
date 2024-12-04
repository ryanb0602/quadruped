import ctypes
from ctypes import c_int, c_float
from _ctypes import LoadLibrary

handle = LoadLibrary("./simulate/kinecore.dll")
lib = ctypes.WinDLL("./simulate/kinecore.dll", handle=handle)

print(dir(lib))

lib.setup.restype = None
lib.setup.argtypes = [c_float]

lib.test_function.restype = c_int

if __name__ == "__main__":
    print(f"Binding validate: {lib.test_function()}")
import ctypes
from ctypes import c_int, c_float
from _ctypes import LoadLibrary

handle = LoadLibrary("./simulate/kinecore.dll")
lib = ctypes.WinDLL("./simulate/kinecore.dll", handle=handle)

class leg_deltas(ctypes.Structure):
    _fields_ = [
        ("array1", c_float * 4),
        ("array2", c_float * 4)
    ]

lib.test_function.restype = c_int

def test_func():
    return lib.test_function()

lib.setup.restype = None
lib.setup.argtypes = [c_float]

def setup(float):
    lib.setup(float)

lib.set_real_thetas.restype = None
lib.set_real_thetas.argtypes = [c_int, c_float, c_float]

def set_real_thetas(int, f1, f2):
    lib.set_real_thetas(int, f1, f2)

lib.get_deltas.restype = leg_deltas

def get_deltas():
    array = []
    leg_ds = lib.get_deltas()
    array.append(leg_ds.array1)
    array.append(leg_ds.array2)
    return array

if __name__ == "__main__":
    print(f"Binding validate: {lib.test_function()}")
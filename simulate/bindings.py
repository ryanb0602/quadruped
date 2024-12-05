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

class leg_position(ctypes.Structure):
    _fields_ = [("value1", ctypes.c_float), ("value2", ctypes.c_float)]

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

lib.setup_basic_test.restype = None

def setup_basic_test():
    lib.setup_basic_test()

lib.update_basic_test.restype = None

def update_basic_test():
    lib.update_basic_test()

lib.data_basic_test.restype = leg_position

def data_basic_test():
    data = lib.data_basic_test()
    return data.value1, data.value2

if __name__ == "__main__":
    print(f"Binding validate: {lib.test_function()}")
from bindings import setup, test_func, set_real_thetas, get_deltas, leg_deltas, setup_basic_test, \
update_basic_test, data_basic_test
import time
import matplotlib.pyplot as plt

MOTOR_SPEED = 10
LEG_LENGTHS = 6

print(f"BINDING TEST: {test_func()}")

runtime = float(input("Enter runtime in seconds: "))
start_time = time.time()

leg_a_position_array = []
leg_a = {"real_a": 0, "real_b": 0, "ideal_a": 0, "ideal_b": 0, "last_update": 0}
leg_a_deltas = leg_deltas()

leg_a_xs = []
leg_a_ys = []

def sim_real_pos(leg):
    direction_a = (leg["ideal_a"] - leg["real_a"]) / abs(leg["ideal_a"] - leg["real_a"]) if abs(leg["ideal_a"] - leg["real_a"]) else 0
    leg["real_a"] = direction_a * (time.time() - leg["last_update"]) * MOTOR_SPEED

    direction_b = (leg["ideal_b"] - leg["real_b"]) / abs(leg["ideal_b"] - leg["real_b"]) if abs(leg["ideal_b"] - leg["real_b"]) else 0
    leg["real_b"] = direction_b * (time.time() - leg["last_update"]) * MOTOR_SPEED

def update_ideals():
    delta_vals = get_deltas()
    leg_a["ideal_a"] = leg_a["real_a"] + delta_vals[0][0]
    leg_a["ideal_b"] = leg_a["real_b"] + delta_vals[1][0]

def store_xy_data(x, y):
    leg_a_xs.append(x)
    leg_a_ys.append(y)


setup(LEG_LENGTHS)

setup_basic_test()

last_sample = 0

while time.time() - start_time < runtime:
    sim_real_pos(leg_a)
    set_real_thetas(0, leg_a["real_a"], leg_a["real_b"])
    update_ideals()
    update_basic_test()

    if time.time() - last_sample > .2:
        data_tup = data_basic_test()
        store_xy_data(data_tup[0], data_tup[1])
        last_sample = time.time()


plt.plot(leg_a_xs, leg_a_ys, 'o')
plt.show()
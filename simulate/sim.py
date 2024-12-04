from bindings import setup, test_func, set_real_thetas, get_deltas, leg_deltas
import time

MOTOR_SPEED = 10
LEG_LENGTHS = 6

print(f"BINDING TEST: {test_func()}")

runtime = int(input("Enter runtime in seconds: "))
start_time = time.time()

leg_a_position_array = []
leg_a = {"real_a": 0, "real_b": 0, "ideal_a": 0, "ideal_b": 0, "last_update": 0}
leg_a_deltas = leg_deltas()

def sim_real_pos(leg):
    direction_a = (leg["ideal_a"] - leg["real_a"]) / abs(leg["ideal_a"] - leg["real_a"]) if abs(leg["ideal_a"] - leg["real_a"]) else 0
    leg["real_a"] = direction_a * (time.time() - leg["last_update"]) * MOTOR_SPEED

    direction_b = (leg["ideal_b"] - leg["real_b"]) / abs(leg["ideal_b"] - leg["real_b"]) if abs(leg["ideal_b"] - leg["real_b"]) else 0
    leg["real_b"] = direction_b * (time.time() - leg["last_update"]) * MOTOR_SPEED

def update_ideals():
    delta_vals = get_deltas()
    leg_a["ideal_a"] = delta_vals[0][0]
    leg_a["ideal_b"] = delta_vals[1][1]


setup(LEG_LENGTHS)

while time.time() - start_time < runtime:
    sim_real_pos(leg_a)
    set_real_thetas(0, leg_a["real_a"], leg_a["real_b"])
    update_ideals()
    
from bindings import setup, test_func, set_real_thetas, get_deltas, leg_deltas, setup_basic_test, \
update_basic_test, data_basic_test, leg_theta_values
import time
import matplotlib.pyplot as plt
import math
from matplotlib.animation import FuncAnimation
import numpy as np

MOTOR_SPEED = 10
LEG_LENGTHS = 6

print(f"BINDING TEST: {test_func()}")

runtime = float(input("Enter runtime in seconds: "))
start_time = time.time()

leg_a_position_array = []
leg_a = {"real_a": 0, "real_b": 0, "ideal_a": 0, "ideal_b": 0, "last_update": 0}
leg_a_deltas = leg_deltas()

leg_a_a = []
leg_a_b = []

leg_a_xs = []
leg_a_ys = []

def store_xy_data(x, y):
    leg_a_xs.append(x)
    leg_a_ys.append(y)

setup(LEG_LENGTHS)

setup_basic_test()

last_sample = 0

while time.time() - start_time < runtime:
    update_basic_test()

    if time.time() - last_sample > .2 and time.time() - start_time > .3:
        data_tup = data_basic_test()
        store_xy_data(data_tup[0], data_tup[1])
        last_sample = time.time()
        leg_thetas = leg_theta_values(0)
        leg_a_a.append(leg_thetas[0])
        leg_a_b.append(leg_thetas[1])


fig, ax = plt.subplots()
ax.set_xlim(-12, 12)  # Set the x-axis limits
ax.set_ylim(-12, 12)  # Set the y-axis limits
ax.set_aspect('equal')  # Keep the aspect ratio square

line1, = ax.plot([], [], 'r-', lw=2)  # First segment (red line)
line2, = ax.plot([], [], 'b-', lw=2)  # Second segment (blue line)

num_frames = len(leg_a_a)

ax.scatter(leg_a_ys, leg_a_xs)

ax.invert_yaxis()

for i in range(len(leg_a_a)):
    print(str(leg_a_a[i]) + ", " + str(leg_a_b[i]))

def update(i):
    # Calculate the coordinates for the first segment
    y1 = [0, 6 * math.sin(leg_a_a[i])]
    x1 = [0, 6 * math.cos(leg_a_a[i])]
    
    # Calculate the coordinates for the second segment
    y2 = [6 * math.sin(leg_a_a[i]), 6 * math.sin(leg_a_a[i]) - 6 * math.cos(leg_a_b[i])]
    x2 = [6 * math.cos(leg_a_a[i]), 6 * math.cos(leg_a_a[i]) + 6 * math.sin(leg_a_b[i])]

    # Update the line data
    line1.set_data(x1, y1)
    line2.set_data(x2, y2)
    
    return line1, line2

# Create the animation
ani = FuncAnimation(fig, update, frames=num_frames, interval=50, blit=True)

# Show the animation
plt.show()
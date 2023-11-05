import matplotlib.pyplot as plt


ax_lst, ay_lst, az_lst, gx_lst, gy_lst, gz_lst = [], [], [], [], [], []
with open('data.txt', 'r') as f:
    while line := f.readline().strip():
        ax, ay, az, gx, gy, gz = line.split()
        ax_lst.append(float(ax))
        ay_lst.append(float(ay))
        az_lst.append(float(az))
        gx_lst.append(float(gx))
        gy_lst.append(float(gy))
        gz_lst.append(float(gz))

# X
for i, ax in enumerate(ax_lst):
    if ax <= 200 and ax >= -200:
        ax_lst[i] = 0

vx_lst = [0]
for i, ax in enumerate(ax_lst):
    vx_lst.append(vx_lst[-1] + ax * 0.01)

xx_lst = [0]
for i, vx in enumerate(vx_lst):
    xx_lst.append(xx_lst[-1] + vx * 0.01)

# Y
for i, ay in enumerate(ay_lst):
    if ay <= 200 and ay >= -200:
        ay_lst[i] = 0

vy_lst = [0]
for i, ay in enumerate(ay_lst):
    vy_lst.append(vy_lst[-1] + ay * 0.01)

xy_lst = [0]
for i, vy in enumerate(vy_lst):
    xy_lst.append(xy_lst[-1] + vy * 0.01)

plt.subplot(3, 2, 1)
plt.title('ax')
plt.plot(ax_lst)
plt.subplot(3, 2, 3)
plt.title('vx')
plt.plot(vx_lst)
plt.subplot(3, 2, 5)
plt.title('xx')
plt.plot(xx_lst)

plt.subplot(3, 2, 2)
plt.title('ay')
plt.plot(ay_lst)
plt.subplot(3, 2, 4)
plt.title('vy')
plt.plot(vy_lst)
plt.subplot(3, 2, 6)
plt.title('xy')
plt.plot(xy_lst)

plt.show()

cum_x, cum_y = [], []
for x,y in zip(xx_lst,xy_lst):
    cum_x.append(x)
    cum_y.append(y)
    plt.clf()
    plt.scatter(cum_x, cum_y)
    plt.pause(0.000001)

plt.scatter(xx_lst, xy_lst)

plt.show()

import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D


p_global = [6.97744, 9.91473, 6.88343]

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')



ax.scatter(*p_global, color='blue', s=50, label='Инструмент')


ax.quiver(0, 0, 0, *p_global, color='red', linewidth=2, label='Вектор из начала координат')


ax.set_xlim([0, max(1, p_global[0] + 1)])
ax.set_ylim([0, max(1, p_global[1] + 1)])
ax.set_zlim([0, max(1, p_global[2] + 1)])

ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.legend()
ax.set_title("Положение инструмента в глобальной системе координат")

plt.show()
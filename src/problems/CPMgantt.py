import matplotlib.pyplot as plt
import numpy as np

# Assuming `tasks` is a dictionary where the keys are task IDs and the values are dictionaries
# Each dictionary has 'es', 'ef', 'ls', 'lf', and 'time' attributes
tasks = {}
with open('nodes.txt') as f:
    next(f)
    for line in f:
        node, es, ef, ls, lf, weight = map(int, line.split())
        tasks[node] = {'es': es, 'ef': ef, 'ls': ls, 'lf': lf, 'time': weight}

fig, ax = plt.subplots()

# Set the y-axis labels to the task IDs
y_labels = [str(task_id) for task_id in tasks.keys()]
ax.set_yticks(np.arange(len(y_labels)))
ax.set_yticklabels(y_labels)

# Set the x-axis labels to the time units
x_labels = list(range(max(task['lf'] for task in tasks.values()) + 1))
ax.set_xticks(x_labels)
ax.set_xticklabels(x_labels)

# Draw a bar for each task
for i, (task_id, task) in enumerate(tasks.items()):
    ax.broken_barh([(task['es'], task['ef'] - task['es'])], (i-0.4, 0.8), facecolors='blue')  # Early start and finish times
    ax.broken_barh([(task['ls'], task['lf'] - task['ls'])], (i-0.4, 0.8), facecolors='red')  # Late start and finish times

ax.legend(['Early start/finish', 'Late start/finish'])

ax.set_xlabel('Time')
ax.set_ylabel('Task ID')
ax.set_title('Gantt Chart')

plt.show()

# Learn ROS2

ROS 2 learning workspace with small example packages for topics, services, and custom interfaces.

## Packages

- `example_msgs`: custom service interfaces.
- `topic_examples`: basic publisher and subscriber examples.
- `service_examples`: service example package.
- `action_examples`: placeholder package currently ignored by colcon.

## Build

From the workspace root:

```bash
source /opt/ros/$ROS_DISTRO/setup.bash
colcon build
source install/setup.bash
```

To build only one package:

```bash
colcon build --packages-select example_msgs
```

Generated `build/`, `install/`, and `log/` directories are intentionally ignored by Git.

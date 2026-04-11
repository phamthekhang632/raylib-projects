# raylib-container

This is a template repository that provides everything you need to start developing [raylib](https://www.raylib.com/) applications in a isolated environment. It includes:

- **Docker environment** with all raylib dependencies pre-installed
- **CMake build system** for modern C++ project management
- **Development CLI** (`dev.sh`) provides convenient commands for setup, building, linting, and running
- **Code quality tools**, including clang-tidy, clang-format, cmake-format and pre-commit

## Prerequisites

- [Docker Engine](https://docs.docker.com/engine/) (or [Docker Desktop](https://docs.docker.com/desktop/) for a GUI experience)
    - Optional: With the provided `devcontainer.json`, you can use the container with other container management of your choice, such as [DevPod CLI](https://devpod.sh/docs/quickstart/devpod-cli)

## Quick Start

Click on `Use this template` and create your own repository, or clone this project:
```sh
git clone https://github.com/phamthekhang632/raylib-container.git raylib-project
```

### VS Code

When opening the project with VS Code, a prompt will guide you on how to set up the project. If not , you can also follow instruction [here](https://code.visualstudio.com/docs/devcontainers/containers).

### DevPod CLI

```sh
devpod up . --devcontainer-path .devcontainer/devcontainer.json --ide=none --id raylib-project
```

Change `ide` and `id` if necessary. Connect to host:

```sh
ssh raylib-project
```

## Development

### pre-commit

Install [pre-commit](https://pre-commit.com/#install)

```sh
pip install pre-commit
pre-commit install
```

From then on, whenever you commit your changes, pre-commit will check your code for simple formatting issues.
For more in depth analysis, run `clang-tidy` using the following command. You can also remove the line `stages: [manual]` in pre-commit to let `clang-tidy` run automatically everytime you make a commit.

```sh
pre-commit run --hook-stage manual clang-tidy --all-files
```

### `dev.sh`

Use `dev.sh` to quickly lint, build, and run your application.
```sh
./dev.sh all
```

To see all options:

```sh
./dev.sh
```
```
  Usage: ./dev.sh [command]

  Commands:
    setup     Configure CMake and generate compile_commands.json
    lint      Run clang-tidy on all source files
    fix       Run clang-tidy and auto-fix issues
    build     Build the project
    run       Build and run the game
    clean     Delete the build directory
    all       setup + lint + build + run
```

ARG VARIANT=debian13
FROM mcr.microsoft.com/devcontainers/base:${VARIANT}

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install build-essential clang cmake \
    && apt-get -y install clang-format clang-tidy pre-commit \
    && apt-get -y install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev \
    && apt-get autoremove -y && apt-get clean -y && rm -rf /var/lib/apt/lists/*

# Install Oh My Zsh for the vscode user
RUN git clone https://github.com/zsh-users/zsh-autosuggestions \
        /home/vscode/.oh-my-zsh/custom/plugins/zsh-autosuggestions \
    && git clone https://github.com/zsh-users/zsh-completions \
        /home/vscode/.oh-my-zsh/custom/plugins/zsh-completions \
    && chown -R vscode:vscode /home/vscode/.oh-my-zsh \
    && chsh -s /bin/zsh vscode

# Build and install raylib
WORKDIR /usr/local/
RUN git clone https://github.com/raysan5/raylib.git raylib \
    && cd raylib \
    && mkdir build && cd build \
    && cmake .. \
	&& make install \
    && ldconfig

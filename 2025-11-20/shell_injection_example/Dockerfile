FROM rust:1.91

# Set the working directory to /app
WORKDIR /app

# Install HID Cloudflare CA certificate from local assets
COPY .devcontainer/assets/CF_ca.crt /usr/local/share/ca-certificates/Cloudflare_HID_CA.crt
RUN update-ca-certificates

RUN apt update && apt install -y sudo

RUN useradd -ms /bin/bash vscode
RUN usermod -aG sudo vscode
RUN echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers

COPY . .
RUN chown -R vscode:vscode /app

USER vscode

# Build the Rust application
RUN cargo build

# Copy the built application into the working directory
RUN cp ./target/debug/shell_injection_example .

# Expose the port that the application will listen on
# EXPOSE 8000

# Run the command to start the application when the container is launched
CMD ["./shell_injection_example"]
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <termios.h>

#define UART_BAUD B9600

#define UART_DEVICE "/dev/ttyUSB0"
#define UART_BUFFER_SIZE 4096

int main(int argc, char** argv) {

    (void)argc;
    (void)argv;

    int uart_device = open(UART_DEVICE, O_RDWR);

    if (uart_device < 0) {
        printf("Error opening serial device");
        return 1;
    }

    struct termios uart_tty;

    if(tcgetattr(uart_device, &uart_tty) != 0) {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
    }

    cfmakeraw(&uart_tty);
    cfsetispeed(&uart_tty, UART_BAUD);
    cfsetospeed(&uart_tty, UART_BAUD);

    uart_tty.c_cflag |= (CLOCAL | CREAD);
    uart_tty.c_cflag &= ~PARENB;
    uart_tty.c_cflag &= ~CSTOPB;
    uart_tty.c_cflag &= ~CSIZE;
    uart_tty.c_cflag |= CS8;

    uart_tty.c_cc[VMIN]  = 0;
    uart_tty.c_cc[VTIME] = 1;

    uart_tty.c_iflag &= ~(IXON | IXOFF | IXANY);
    uart_tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);

    uart_tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    uart_tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

    char read_buf [256];
    memset(read_buf, 0, sizeof(read_buf));

    while(1) {
        int n = read(uart_device, &read_buf, sizeof(read_buf));

        if (n < 0) {
            printf("Error: '%d'\n", n);
        }
        else if (n == 0) {
            printf("timeout\n");
            continue;
        }
        else {
            printf("Read data: '%d'\n", n);
        }
    }


    close(uart_device);

}
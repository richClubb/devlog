#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <termios.h>
#include <sys/epoll.h>

#define BAUD B115200

#define UART_DEVICE "/dev/ttyUSB0"
#define MAX_EVENTS 1
#define BUF_SIZE 256
#define UART_BUFFER_SIZE 4096

unsigned char uart_buffer[UART_BUFFER_SIZE];
unsigned int uart_buffer_size = 0;

typedef struct uart_context {
    int fd;
    void (*on_receive)(struct uart_context *ctx);
} uart_context_t;

static int uart_open(const char *device)
{
    int fd = open(device,
                  O_RDWR |
                  O_NOCTTY |
                  O_NONBLOCK | 
                  O_NDELAY);

    if (fd < 0) {
        perror("open");
        return -1;
    }

    struct termios tty;

    if (tcgetattr(fd, &tty) != 0) {
        perror("tcgetattr");
        close(fd);
        return -1;
    }

    cfmakeraw(&tty);

    cfsetispeed(&tty, BAUD);
    cfsetospeed(&tty, BAUD);

    tty.c_cflag |= (CLOCAL | CREAD);
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    // experiment
    tty.c_iflag &= ~(IGNBRK | BRKINT | ICRNL |
                    INLCR | PARMRK | INPCK | ISTRIP | IXON);
    tty.c_lflag &= ~ICANON;   // non-canonical mode
    // tty.c_cflag |= ICANON;   // canonical mode

    tty.c_cc[VMIN]  = 1;
    tty.c_cc[VTIME] = 0;

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        perror("tcsetattr");
        close(fd);
        return -1;
    }

    tcflush(fd, TCIOFLUSH);

    return fd;
}

static void handle_uart_read(uart_context_t *ctx)
{
    uint8_t buffer[BUF_SIZE];

    for (;;) {

        ssize_t num_bytes = read(ctx->fd,
                         buffer,
                         BUF_SIZE);
        printf("Num bytes %d\n", (u_int32_t)num_bytes);

        if (num_bytes > 0) {
    
            if ((num_bytes + uart_buffer_size) > UART_BUFFER_SIZE) {
                printf("input too large for buffer, dumping");
                uart_buffer_size = 0;
                memset(uart_buffer, 0, UART_BUFFER_SIZE);
                return;
            }

            memcpy((uart_buffer + uart_buffer_size), buffer, num_bytes);
            uart_buffer_size += num_bytes;
            memset(buffer, 0, BUF_SIZE);
        }
        else if (num_bytes == 0) {
            /*
             * Normally uncommon for UARTs.
             */
            printf("EOF\n");
            break;
        }
        else {
            if (errno == EAGAIN ||
                errno == EWOULDBLOCK) {
                /*
                 * No more data available.
                 */
                // printf("no more data\n");
                break;
            }

            // perror("read");
            break;
        }
    }
}

int main(void)
{
    int epfd;
    struct epoll_event ev;
    struct epoll_event events[MAX_EVENTS];

    int uart_fd = uart_open(UART_DEVICE);

    if (uart_fd < 0) {
        return EXIT_FAILURE;
    }

    uart_context_t *uart =
        malloc(sizeof(*uart));

    if (!uart) {
        perror("malloc");
        close(uart_fd);
        return EXIT_FAILURE;
    }

    uart->fd = uart_fd;
    uart->on_receive = handle_uart_read;

    epfd = epoll_create(1);

    if (epfd < 0) {
        perror("epoll_create");
        close(uart_fd);
        free(uart);
        return EXIT_FAILURE;
    }

    memset(&ev, 0, sizeof(ev));

    ev.events = EPOLLIN;
    ev.data.ptr = uart;

    if (
        epoll_ctl(
            epfd,
            EPOLL_CTL_ADD,
            uart_fd,
            &ev
        ) < 0
    ) 
    {
        perror("epoll_ctl");
        close(epfd);
        close(uart_fd);
        free(uart);
        return EXIT_FAILURE;
    }

    printf("Listening on %s\n", UART_DEVICE);

    while (1) {

        int nfds = epoll_wait(
            epfd,
            events,
            MAX_EVENTS,
            0);

        if (
            (nfds == 0) && 
            (uart_buffer_size != 0)
        ) {
            printf("Filled buffer: %d\n", uart_buffer_size);

            printf("Buffer: \n");
            for (unsigned int index = 0; index < uart_buffer_size; index++) {
                printf("0x%x", uart_buffer[index]);
            }
            printf("\n");

            // clear buffer after printing
            memset(uart_buffer, 0, UART_BUFFER_SIZE);
            uart_buffer_size = 0;
        }

        if (nfds < 0) {
            if (errno == EINTR)
                continue;

            perror("epoll_wait");
            break;
        }

        for (int i = 0; i < nfds; i++) {

            uart_context_t *ctx =
                events[i].data.ptr;

            if (events[i].events & EPOLLIN) {
                // handle_uart_read(ctx);
                if (NULL != ctx->on_receive) {
                    ctx->on_receive(ctx);
                }
            }

            if (events[i].events &
                (EPOLLERR | EPOLLHUP)) {

                fprintf(stderr,
                        "UART error/hangup\n");
            }
        }
    }

    close(epfd);
    close(uart_fd);
    free(uart);

    return EXIT_SUCCESS;
}

void transmit(uint8_t buffer, uint32_t size) {
    printf("Transmitting\n");
    return;
}
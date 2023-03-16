#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

int serial_ouvert()
{
    int fd;
    struct termios options;

    fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);

    if (fd == -1) {
        perror("Error: Unable to open serial port");
        return 1;
    }

    tcgetattr(fd, &options);
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_oflag &= ~OPOST;
    options.c_cc[VMIN] = 0;
    options.c_cc[VTIME] = 10;

    if (tcsetattr(fd, TCSANOW, &options) != 0) {
        perror("Error: Unable to set serial port options");
        return 1;
    }
    sleep(1);
    return fd;
}


void send_tensions(float t1, float t2, int fd){
    char buffer[255];
    char command_buf[10];

    printf("T1 : %f, T2 : %f\n", t1, t2);
    // cleanning the buffers
    memset(buffer, 0, sizeof(buffer));
    memset(command_buf, 0, sizeof(command_buf));

    // transform into char two floats separeted by a comma

    memcpy(command_buf, &t1, sizeof(float)); // copy the bytes of t1 into buffer
    memcpy(command_buf + 4, &t2, sizeof(float)); // copy the bytes of t2 into buffer

    read(fd, buffer, sizeof(buffer)) ;

    //printf(" %s ", buffer);

    // Send data to the Arduino

    write(fd, command_buf, sizeof(float)*2);

    // period
    sleep(4); // Sleep for 1 second
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>



// int treat_angle(angle)
// {
//     if (angle/abs(angle) == -1)
//         angle =+ 180;
//     return angle;
// }

int serial_ouvert()
{
    int fd;
    struct termios options;
    char buffer[255];
    
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
    return fd;
}


void send_tensions(float t1, float t2,int fd){
    
    char command_buf[10];

    // cleanning the buffers
    memset(buffer, 0, sizeof(buffer));
    memset(command_buf, 0, sizeof(command_buf));
    t1 = 5;
    t2 = 8;
    
    // transform into char two floats separeted by a comma

    memcpy(command_buf, &t1, sizeof(float)); // copy the bytes of t1 into buffer
    memcpy(command_buf + 4, &t2, sizeof(float)); // copy the bytes of t2 into buffer
    printf("testando\n");

    //  for (int i = 0; i < sizeof(command_buf); i++) {
    // printf("%02X ", command_buf[i]);
    // }
    // command_buf[0]=command;
    
    read(fd, buffer, sizeof(buffer)) ;
    
    // printf(" %s ", buffer);
    
    // Send data to the Arduino
    
    write(fd, command_buf, sizeof(float)*2);

    // period
    usleep(4000000); // Sleep for 1 second


    close(fd);
    return 0;
}

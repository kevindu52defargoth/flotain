#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>


int treat_angle(angle)
{
    if (angle/abs(angle) == -1)
        angle =+ 180;
    return angle;
}

int main()
{
    int fd;
    struct termios options;
    char buffer[255];
    int command;
    char command_buf[2];
    
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



    while (1) {
     
        // cleanning the buffers
        memset(buffer, 0, sizeof(buffer));
        memset(command_buf, 0, sizeof(command_buf));
        command = 2;
        
        // verify is it's a angle turn funtion 
        if (command > 5)
        {   
            command= treat_angle(command);
        }
        
        // transform into char a integer 
        command_buf[0]=command;
        
        
        /* 
         Pour les commandes : 
         * 0 : derriere 
         * 1 : turn left 
         * 2 : farward 
         * 3 : turn right 
         * 4 : ask for sensor data 
         * 5 : turn + angle 
         * 
         * The data are passed through a single byte, for the angle option, 
         * you simply send the angle directly. For determining the direction, 
         * you should add 128 for negative angles ( the treat angle does it) . 
         * It accepts only from 6 to 125 degrees
         */
        
        
        
        if (read(fd, buffer, sizeof(buffer)) > 0) {
            
            //int num = atoi(buffer);
         
            printf(" %s ", buffer);
            
            // Send data to the Arduino
            
            write(fd, command_buf, 1);

            // period
            usleep(4000000); // Sleep for 1 second
        }

    }

    close(fd);
    return 0;
}

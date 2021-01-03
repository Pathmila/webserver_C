#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

#define PORT 8080

char webpage[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=UTF-8\r\n\r\n"
        "<!DOCTYPE html>\r\n"
        "<html><head><title>POSSITIVE_THINKING</title></head>\r\n"
        "<body bgcolor><h1><u><b>CHANGING YOUR THOUGHTS FOR A BETTER LIFE</b></u></h1><br>\r\n"
        "<br/><br/><br/>\r\n"
	"<p>Positive thinking leads a man to success path. One who thinks that he can achieve the things, will put his best to achieve, will not fetter by the problems in the path of success and one day he will win positively. Self confidence, determination, perseverance, and hard work are the main factors of success. Every small or big, easy or complex problem have its solution. There is a way out of every labyrinth, there is an answer to every enigma. The only requirements are the confidence, hard work and determination and you get the answer.</p>\r\n"
	"<br/>\r\n"
	"<p>There are two types of genius people in the world according o the time they raise their intelligence. They are pre-developers and late-developers. Pre-developers are the gifted people that can perform from the childhood and late-developers take their time to spread their intelligence. </p>\r\n"
	"<br/>\r\n"
	"<p>As younger generation we should think positive. We should look at all these things in a positive mind. Not in a negative mind. Therefore we can face to all the problems that come to our life. We are able to face them in a very successful manner. So positive thinking is a mental attitude that admits into the mind thoughts, words and images that are conductive to growth, expansion and success. It is a mental attitude that expects good and favorable results. A positive mind anticipates happiness, joy, health and a successful outcome of every situation and action. So by thinking positively we can change our life to a very successful path.</p>\r\n"
"</body></html>\r\n";


int main(int argc, char const *argv[]){
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0){
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    
	address.sin_family = AF_INET;
    	address.sin_addr.s_addr = INADDR_ANY;
    	address.sin_port = htons( PORT );
    
    	memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0){
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0){
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    while(1){
        printf("\nWaiting for a connection..........................\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0){
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        
        char buffer[50000] = {0};
        valread = read( new_socket , buffer, 50000);
        printf("%s\n",buffer );
        write(new_socket, webpage, sizeof(webpage) - 1);
        close(new_socket);
    }
    return 0;
}

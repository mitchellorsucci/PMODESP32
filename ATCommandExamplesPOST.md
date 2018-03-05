AT+CIPSTART="SSL","192.168.1.107",4443

AT+CIPSEND=200

POST /blink HTTP/1.1\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: 18\r\n\r\ncmd=start+blinking\r\n

AT+CIPSEND=18
GET / HTTP/1.1\r\n\r\n

# nexus.c :signal_strength:
Simple and tiny Web Server implemented in... Yes. You guessed it right, in C.

It provides a basic foundation for hosting web applications and serving static content. The server is designed to be easy to understand and modify. The purpose of this project was to learn something about webserver and network programming in C in one day and have fun :)

## Todo
[ ] Make it Concurrent

## Features
* Implements a basic HTTP/1.1 server
* Supports serving static content

## Prerequisites
Before running the web server, ensure you have the following:

* C compiler (GCC or Clang)
* CMake
* POSIX-compliant operating system (Linux, macOS, Unix)

## Getting Started
1. Clone the repo
```bash
git clone https://github.com/lvntky/nexus.c.git
```
2. Navigate to the project directory:
```bash
cd nexus.c
```
3. Compile the source code
```bash
cmake ./
```
4. Run the server
```bash
./nexus
```
5. By default, the server listens on localhost (port 8080). You can access it in your web browser by navigating to http://localhost:8080

## Configuration
You can modify the server's behavior by adjusting the values in the config.h file. Here are some options you might want to customize:
[ ]  `PORT`: The port number the server listens on (default: 8080).
[ ]  `THREAD_POOL_SIZE`: The maximum number of threads that handle incoming requests 
[ ]  `WEB_ROOT`: The directory where the server looks for static files (default: "./public").

## Contributing
Contributions are welcome! If you find any bugs or have suggestions for improvements, please open an issue or submit a pull request. Make sure to follow the existing coding style and provide appropriate test coverage.

## License
This project is licensed under the MIT License.

## Referances/Documents
* [HTTP Server: Everything you need to know to Build a simple HTTP server from scratch](https://medium.com/from-the-scratch/http-server-what-do-you-need-to-know-to-build-a-simple-http-server-from-scratch-d1ef8945e4fa)
* [HTTP RFC](https://datatracker.ietf.org/doc/html/rfc2616)

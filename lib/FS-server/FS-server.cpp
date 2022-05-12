#include "FS-server.h"

FSServer::FSServer::FSServer(String root, int port) {
    this->server = new ESP8266WebServer(port);
    this->root = root;
}

FSServer::FSServer::~FSServer() {
    delete this->server;
}

void FSServer::FSServer::startServer(){

    server->onNotFound([this]() {
        //TODO: Don't assume that it's HTML
        String contentType = "text/html";
        String path = root + server->uri();
        if(path.endsWith("/")){
            path += "index.html";
        }
        //Send compressed file if avaliable
        if(LittleFS.exists(path + ".gz")){
            path += ".gz";
            contentType = "application/x-gzip";
        }
        
        if(LittleFS.exists(path)){
            File file = LittleFS.open(path, "r");
            server->streamFile(file, contentType);
            file.close();
        } else {
            server->send(404, "text/plain", "File Not Found");
        }

    });

    server->begin();
}

void FSServer::FSServer::handleClient(){
    this->server->handleClient();
}

void FSServer::FSServer::on(std::string path, std::function<void(void)> handler){
    server->on(path.c_str(), [handler]() {
        handler();
    });
}

void FSServer::FSServer::on(std::string path, HTTPMethod method, std::function<void(void)> handler){
    server->on(path.c_str(), method, [handler]() {
        handler();
    });
}

bool FSServer::FSServer::hasArg(std::string arg){
    return server->hasArg(arg.c_str());
}

std::string FSServer::FSServer::arg(std::string arg){
    return std::string(server->arg(arg.c_str()).c_str());
}

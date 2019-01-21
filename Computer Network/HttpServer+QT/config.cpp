#include "config.h"


using namespace std;

Config::Config(void)
{
}

Config::~Config(void)
{
}
const int Config::PORT = 80;
const string Config::SERVERADDRESS = "127.0.0.1";
const string Config::PATH = "C:\\Users\\LXR\\Desktop\\";
const int Config::MAXCONNECTION = 50;
const int Config::BUFFERLENGTH = 512;
const u_long Config::BLOCKMODE = 1;
vector<string> Config::split(const string& str, const string& delim) {
    vector<string> res;
    if ("" == str) return res;
    //?????????????????string????????char*????
    char * strs = new char[str.length() + 1]; //???????
    strcpy(strs, str.c_str());

    char * d = new char[delim.length() + 1];
    strcpy(d, delim.c_str());

    char *p = strtok(strs, d);
    while (p) {
        string s = p;
        res.push_back(s);
        p = strtok(NULL, d);
    }

    return res;
}
void Config::recvBuf_remsg(string http,string &head,string &msg,string path)
{
    if (http.find("HTTP") == string::npos)
        return;
    vector<string> request = split(http, "\r\n");
    vector<string> shead = split(request[0], " ");
    string filename = path + shead[1].substr(1);
    string httplevel = shead[2];


    ifstream content_file(filename);
    if (!content_file.is_open()) {
        head += httplevel + " 404 Not Found\r\n";
        string length = "0";
        head += "Content-Length:" + length + "\r\n\r\n";
        msg += head;
        msg += "Error??File not found.";
        return;
    }
    head += httplevel + " 200 OK\r\n";

    streampos file_size = content_file.tellg();
    content_file.seekg(0, ios::end);
    file_size = content_file.tellg() - file_size;
    content_file.seekg(0, ios::beg);

    string content = "";
    content.resize(file_size, 0);
    content_file.read((char *)content.c_str(), file_size);
    content_file.close();

    string length = to_string(content.size());
    head += "Content-Length:" + length + "\r\n\r\n";
    msg += head;
    msg += content;
    return;
}

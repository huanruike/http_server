#!/bin/bash
g++ deal_path.cpp work.cpp http_serv.cpp serv_send.cpp request.cpp error_handling.cpp -o http_serv -lpthread


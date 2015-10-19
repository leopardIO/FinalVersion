#include "Session.h"
#include <iostream>
#include <stdlib.h>
using namespace NodeServer;

Session::Session(): _sessionID_( 0 ),_is_recycler_( false )
{
}
Session::~Session()
{
}
string Session::FormMessage(uint32_t proto_length , uint32_t  proto_type , string &proto_str,string & content_str)
{	
	string ret_string ;
	HeadStructMessage header ;
	header.length = proto_str.length();
    
	header.type = proto_type;

    std::cout<<" head len"<< header.length <<std::endl;
    std::cout<<" head type"<< header.length <<std::endl;

    char* data_buf = (char*)malloc(8+proto_str.length()+content_str.length());
    char* ptr = data_buf;
	char header_buf[8];
	memset(data_buf , 0 ,8);
	memcpy(data_buf , &header , 8);
    ptr = ptr + 8;
    memcpy( ptr, proto_str.c_str(), proto_str.length());
    ptr = proto_str.length() + ptr;
    memcpy( ptr, content_str.c_str(), content_str.length());
    ptr = content_str.length() + ptr;

	ret_string +=  header_buf;
	ret_string += proto_str;
	ret_string += content_str;
	return string(data_buf, (8+proto_str.length()+content_str.length())); 			
}

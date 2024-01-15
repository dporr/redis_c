/* Implementation of a simple redis protocol parser
*/

// Max size of a single bulk string
#define PROTO_MAX_BULK_LEN 512 * (1024 * 1024 * sizeof(char)) 

struct RESP_cmd {
    char command[8];
    char* arguments[];
    };

struct RESP_cmd command;

/**
 * Parses a msg received by this server.RESP encodes bulk strings in the following way:
$<length>\r\n<data>\r\n
 * @param msg raw msg to parse
 * @param resp_cmd struc that will hold the parsed resp command
 */
void parse_msg(char*  msg);
void handle_CMDNAME();


/***************/
void parse_msg(char*  msg){
    if(!msg) printf("Invalid command");
    if(msg[0] != '$')  printf("Invalid command");
}
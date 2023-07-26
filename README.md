## ENEE459b Final Project - Binary Disassembly 
This was a project done in my reverse engineering lab class during my fall 2018 semester at UMD. 

For context, our previous project was to create an ELF file analyzer which had to accept an ELF binary file and report on information such as the size of specific sections, hashes of the data, and other information which required using libraries to dissect the binary. Additionally, we had to program an authentication method to use the program and a way to store an encrypted record of that information. 

In this project, we were given another student's symbol table stripped binary file and tasked to find information on how their authentication method worked, what sort of data structures were used to store the information, and what vulnerabilities were exploitable. This was done in IDA Freeware and the write up of the disassembly is available to read in "Project 2 writeup.docx"

The program we were to analyze is named proj1, and the IDA database is in proj1.i64. A summary of the process and findings are described below:
-  Running the program prompts a password, though it does not have a password database implying the password is embedded in the executable
-  strings analysis of the program shows prompts for encrypting a binary file and writing it to disk
-   some other strings such as "text_size:" "data_size:" "md5_record.md5:" imply that the program will analyze these features of a loaded binary file
-  IDA Pro disassembly of the entrant authentication function shows the following approximate C code:
   ![alt text](https://github.com/mtaost/ENEE459b-semester-project/blob/master/ida_auth_function.png?raw=true "ida pro")
  ```c
int authenticate() {
    char username[128];
    char password[128];

    int counter;

    int usr_char_sum = 0, pwd_char_sum = 0;
    char in_char;

    counter = 0;

    while (counter < 127) {
        in_char = get_password_char();
        if (in_char == '\n' || in_char == '\r') {
            break;
        }

        else {
            password[counter] = in_char;
            putc('*');
            counter++;
        }
    }

    counter = 0;

    while (counter < 127) {
        usr_char_sum = username[counter];
        pwd_char_sum = password[counter];
        counter++;
    }

    if (usr_char_sum == 550 && pwd_char_sum == 796) {
        // grant access
    }

    else {
        // access_denied
    }
}
```
- From this C code, we can determine a pattern of a password that will grant access
- Password can also be bypassed by modifying the JNZ instruction to JZ, which will negate the behavior of a failed password 

#include <stdio.h>
#include <stdlib.h>



int main(int argc,char **argv)
{
    char buffer[20]={0};
    FILE *fp=nullptr;
    if(fopen_s(&fp,argv[1],"rb")!=0)
        return -1;
    if(fread_s(buffer,20,1,20,fp)<0)
    {
        fclose(fp);
        return -2;
    }
    fclose(fp);
    printf("%02X-%02X-%02X-%02X-%02X-%02X-%02X-%02X-%02X-%02X",
        (unsigned char)buffer[0],
        (unsigned char)buffer[1],
        (unsigned char)buffer[2],
        (unsigned char)buffer[3],
        (unsigned char)buffer[4],
        (unsigned char)buffer[5],
        (unsigned char)buffer[6],
        (unsigned char)buffer[7],
        (unsigned char)buffer[8],
        (unsigned char)buffer[9]);
    return 0;
}

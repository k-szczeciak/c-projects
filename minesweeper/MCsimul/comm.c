#include <windows.h>
#include <stdio.h>

void configureSerialPort(HANDLE hComm)
{
    DCB dcbSerialParams = {0}; // Initializing DCB structure
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(hComm, &dcbSerialParams))
    {
        // Error getting state
        printf("Error getting device state\n");
        return;
    }

    dcbSerialParams.BaudRate = CBR_9600;    // Setting BaudRate to 9600
    dcbSerialParams.ByteSize = 7;           // Setting ByteSize = 8
    dcbSerialParams.StopBits = TWOSTOPBITS; // Setting StopBits = 1
    dcbSerialParams.Parity = EVENPARITY;    // Setting Parity = None

    if (!SetCommState(hComm, &dcbSerialParams))
    {
        // Error setting serial port state
        printf("Error setting device parameters\n");
        return;
    }

    COMMTIMEOUTS timeouts = {0}; // Setting timeouts
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hComm, &timeouts))
    {
        // Error setting timeouts
        printf("Error setting timeouts\n");
        return;
    }
}

void writeToSerialPort(HANDLE hComm, const char *data)
{
    DWORD dwBytesWritten = 0;
    if (!WriteFile(hComm, data, strlen(data), &dwBytesWritten, NULL))
    {
        // Error writing to serial port
        printf("Error writing to serial port\n");
        return;
    }
    printf("Data written to serial port: %s\n", data);
}

void readFromSerialPort(HANDLE hComm)
{
    char szBuffer[256] = {0};
    DWORD dwBytesRead = 0;
    if (!ReadFile(hComm, szBuffer, sizeof(szBuffer) - 1, &dwBytesRead, NULL))
    {
        // Error reading from serial port
        printf("Error reading from serial port\n");
        return;
    }
    printf("Data read from serial port: %s\n", szBuffer);
}

int main()
{
    // Open the serial port
    HANDLE hComm = CreateFile("\\\\.\\COM1", // Specify the COM port number
                              GENERIC_READ | GENERIC_WRITE,
                              0, NULL,
                              OPEN_EXISTING,
                              0, NULL);

    if (hComm == INVALID_HANDLE_VALUE)
    {
        // Error in opening serial port
        printf("Error in opening serial port\n");
        return 1;
    }
    else
    {
        printf("Opening serial port successful\n");
    }

    // Configure the serial port
    configureSerialPort(hComm);

    // Write to the serial port
    writeToSerialPort(hComm, "Hello, Serial Port!");

    // Read from the serial port
    readFromSerialPort(hComm);

    // Close the serial port
    CloseHandle(hComm);
    return 0;
}

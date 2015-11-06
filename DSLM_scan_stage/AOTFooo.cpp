// AOTFooo.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#using <System.dll>
#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>

using namespace System;
using namespace System::IO::Ports;
using namespace System::ComponentModel;
using namespace System::Windows::Forms;

int AOTF_status(System::IO::Ports::SerialPort^ sport);
 
void main()
{
    array<String^>^ serialPorts = nullptr;
    try
    {
        // Get a list of serial port names.
        serialPorts = SerialPort::GetPortNames();
    }
    catch (Win32Exception^ ex)
    {
        Console::WriteLine(ex->Message);
    }

    Console::WriteLine("The following serial ports were found:");

	int i=0;

    // Display each port name to the console.
    for each(String^ port in serialPorts)
    {
        Console::WriteLine(port);
	}

	Console::WriteLine("There are only ports.");
	
	System::IO::Ports::SerialPort^ sport;

	sport = gcnew System::IO::Ports::SerialPort();
	sport->PortName = "COM4";	
	sport->BaudRate = 9600;
	sport->DataBits = 8;
	sport->Parity = Parity::None;
	sport->StopBits = StopBits::One;
	sport->Handshake = Handshake::None;
	sport->ReadTimeout = 500;		

	int situation = AOTF_status(sport);
	
	Console::WriteLine("The AOTF is:");
	Console::WriteLine(situation);
}

int AOTF_status(System::IO::Ports::SerialPort^ sport){
	String^ Line = "";
	if(sport->IsOpen == false){			
		sport->Open();
		sport->WriteLine("st\r");
					
		int n=0;
		while(n < 1){
		try{				
			Line += sport->ReadLine();
			Console::WriteLine(Line);
		}
		catch(TimeoutException ^){
			 n = 1;
		}
		}
	}
		
	if(System::String::IsNullOrEmpty(Line)){
		return 0;
	}else{
		return 1;
	}
}
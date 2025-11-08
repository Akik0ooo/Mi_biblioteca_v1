#include "MenuForm.h"
using namespace System;
using namespace System::Windows::Forms;
[STAThread]
void main(array<String^>^ arg) //se pueden eliminar los argumentos del main
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew GameJam::MenuForm());
	//Reemplazar: Project1 es el nombre del proyecto que ha creado
}

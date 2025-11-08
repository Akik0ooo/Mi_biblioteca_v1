#pragma once
#include "JuegoForm.h"
#include "JuegoAutomaticoForm.h"

namespace GameJam {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de MenuForm
	/// </summary>
	public ref class MenuForm : public System::Windows::Forms::Form
	{
	public:
		MenuForm(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~MenuForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btnJugador;
	private: System::Windows::Forms::Button^ btnAutomatico;
	protected:

	protected:


	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btnJugador = (gcnew System::Windows::Forms::Button());
			this->btnAutomatico = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btnJugador
			// 
			this->btnJugador->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->btnJugador->ForeColor = System::Drawing::SystemColors::Highlight;
			this->btnJugador->Location = System::Drawing::Point(768, 249);
			this->btnJugador->Name = L"btnJugador";
			this->btnJugador->Size = System::Drawing::Size(315, 152);
			this->btnJugador->TabIndex = 0;
			this->btnJugador->Text = L"Jugador";
			this->btnJugador->UseVisualStyleBackColor = false;
			this->btnJugador->Click += gcnew System::EventHandler(this, &MenuForm::button1_Click);
			// 
			// btnAutomatico
			// 
			this->btnAutomatico->BackColor = System::Drawing::SystemColors::Info;
			this->btnAutomatico->Location = System::Drawing::Point(243, 255);
			this->btnAutomatico->Name = L"btnAutomatico";
			this->btnAutomatico->Size = System::Drawing::Size(315, 141);
			this->btnAutomatico->TabIndex = 1;
			this->btnAutomatico->Text = L"Automatico";
			this->btnAutomatico->UseVisualStyleBackColor = false;
			this->btnAutomatico->Click += gcnew System::EventHandler(this, &MenuForm::btnAutomatico_Click);
			// 
			// MenuForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1280, 720);
			this->Controls->Add(this->btnAutomatico);
			this->Controls->Add(this->btnJugador);
			this->Name = L"MenuForm";
			this->Text = L"MenuForm";
			this->Load += gcnew System::EventHandler(this, &MenuForm::MenuForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion

		
	private: System::Void MenuForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		JuegoForm^ ventanaJuego = gcnew JuegoForm();
		ventanaJuego->Show();
		this->Hide();
	}
	private: System::Void btnAutomatico_Click(System::Object^ sender, System::EventArgs^ e) {
		JuegoAutomaticoForm^ ventanaJuegoAuto = gcnew JuegoAutomaticoForm();
		ventanaJuegoAuto->Show();
		this->Hide();
	}
	};
}

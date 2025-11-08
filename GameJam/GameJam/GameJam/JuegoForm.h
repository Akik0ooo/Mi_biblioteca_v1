#pragma once
#include"PowerUp.h"

using namespace System::Collections::Generic;
using namespace System::Drawing;
namespace GameJam {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;

	/// <summary>
	/// Resumen de JuegoForm
	/// </summary>
	public ref class JuegoForm : public System::Windows::Forms::Form
	{
	public:
		JuegoForm(void)
		{
			InitializeComponent();
			this->DoubleBuffered = true;
			random = gcnew System::Random(); 
			coloresPermitidos = gcnew array<Color>{ Color::Red, Color::Yellow, Color::Blue }; 
			listaPowerUps = gcnew List<PowerUp^>();
			posicionJugador = PointF(100, 150);
			ladosJugador = 3;
			radioJugador = 30;
			velocidadX = 0;
			velocidadY = 0;
			colorJugador = coloresPermitidos[random->Next(coloresPermitidos->Length)];
			numeroCentralJugador = 0;
			velocidadScroll = (float)(random->Next(3) + 2);
			tramoActual = 1; 
			gameOver = false;
			mensajeFinal = "";
			
			ticksParaSiguienteTramo = 750; //15 seg pa cambiar d tramoxd
			ticksTotalesDelTramo = 750;
			ticksParaSpawn = 100;
		}
				
	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~JuegoForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pistaPictureBox;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;
	protected:

	private:
		PointF posicionJugador;
		int ladosJugador;
		Color colorJugador;
		float radioJugador;
		float velocidadX;
		float velocidadY;
		int numeroCentralJugador;
		System::Random^ random;
		array<Color>^ coloresPermitidos;
		float velocidadScroll;
		int tramoActual;
		int ticksParaSiguienteTramo;
		List<PowerUp^>^ listaPowerUps;
	private: System::Windows::Forms::PictureBox^ uiPanel;
		   int ticksTotalesDelTramo;
		   int ticksParaSpawn;
		   bool gameOver;
		   System::String^ mensajeFinal;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->pistaPictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->uiPanel = (gcnew System::Windows::Forms::PictureBox());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pistaPictureBox))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->uiPanel))->BeginInit();
			this->SuspendLayout();
			// 
			// pistaPictureBox
			// 
			this->pistaPictureBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pistaPictureBox->Location = System::Drawing::Point(1, 1);
			this->pistaPictureBox->Name = L"pistaPictureBox";
			this->pistaPictureBox->Size = System::Drawing::Size(954, 718);
			this->pistaPictureBox->TabIndex = 0;
			this->pistaPictureBox->TabStop = false;
			this->pistaPictureBox->Click += gcnew System::EventHandler(this, &JuegoForm::pistaPictureBox_Click);
			this->pistaPictureBox->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &JuegoForm::pistaPictureBox_Paint);
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Interval = 20;
			this->timer1->Tick += gcnew System::EventHandler(this, &JuegoForm::timer1_Tick);
			// 
			// uiPanel
			// 
			this->uiPanel->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->uiPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->uiPanel->Location = System::Drawing::Point(1011, 163);
			this->uiPanel->Name = L"uiPanel";
			this->uiPanel->Size = System::Drawing::Size(226, 293);
			this->uiPanel->TabIndex = 2;
			this->uiPanel->TabStop = false;
			this->uiPanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &JuegoForm::pictureBox1_Paint);
			// 
			// JuegoForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1280, 720);
			this->Controls->Add(this->uiPanel);
			this->Controls->Add(this->pistaPictureBox);
			this->Name = L"JuegoForm";
			this->Text = L"JuegoForm";
			this->Load += gcnew System::EventHandler(this, &JuegoForm::JuegoForm_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &JuegoForm::JuegoForm_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &JuegoForm::JuegoForm_KeyUp);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pistaPictureBox))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->uiPanel))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void JuegoForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pistaPictureBox_Click(System::Object^ sender, System::EventArgs^ e) {
	}


		   array<PointF>^ CalcularVertices(int lados, float radio, PointF centro)
		   {
			   if (lados < 3)
				   lados = 3;

			   array<PointF>^ vertices = gcnew array<PointF>(lados);
			   double anguloPorVertice = 2 * System::Math::PI / lados;

			   for (int i = 0; i < lados; i++)
			   {
				   double anguloActual = (i * anguloPorVertice) - (System::Math::PI / 2);
				   float x = (float)(centro.X + radio * System::Math::Cos(anguloActual));
				   float y = (float)(centro.Y + radio * System::Math::Sin(anguloActual));
				   vertices[i] = PointF(x, y);
			   }
			   return vertices;
		   }

		   void GenerarPowerUp()
		   {
			   PointF pos;
			   float velX = 0;
			   float velY = 0;

			   // Lógica Común (Color, Lados, Número)
			   Color color = coloresPermitidos[random->Next(coloresPermitidos->Length)];
			   int lados = random->Next(3, 7);
			   int numero = random->Next(1, 6);

			   // Revisa en qué tramo estamos para decidir la lógica
			   if (tramoActual == 1)
			   {
				   // --- TRAMO 1
				   // Aparece en la IZQUIERDA, fuera de pantalla
				   int posX = -50;
				   int posY = random->Next(radioJugador, pistaPictureBox->Height - radioJugador);
				   pos = PointF((float)posX, (float)posY);

				   // Se mueve a la DERECHA (velocidadScroll es Positiva)
				   velX = velocidadScroll;
				   velY = 0;
			   }
			   else if (tramoActual == 2)
			   {
				   // --- TRAMO 2: Bajo Hacia Arriba ---
				   int posX = random->Next(radioJugador, pistaPictureBox->Width - radioJugador);
				   int posY = pistaPictureBox->Height + 50;
				   pos = PointF((float)posX, (float)posY);

				   velX = 0;
				   velY = velocidadScroll;
			   }
			   else // (tramoActual == 3)
			   {
				   // Aparece a la DERECHA, fuera de pantalla
				   int posX = pistaPictureBox->Width + 50;
				   int posY = random->Next(radioJugador, pistaPictureBox->Height - radioJugador);
				   pos = PointF((float)posX, (float)posY);

				   velX = velocidadScroll;
				   velY = 0;
			   }

			   listaPowerUps->Add(gcnew PowerUp(
				   pos, lados, color, numero, radioJugador,
				   velX,  
				   velY   
			   ));
		   }

	


	private: System::Void pistaPictureBox_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e)
	{
		//font¿?
		System::Drawing::Font^ fuente = gcnew System::Drawing::Font("Arial", 12, System::Drawing::FontStyle::Bold);
		System::Drawing::SolidBrush^ pincelTexto = gcnew System::Drawing::SolidBrush(System::Drawing::Color::White);
		System::Drawing::StringFormat^ formatoTexto = gcnew System::Drawing::StringFormat();
		formatoTexto->Alignment = System::Drawing::StringAlignment::Center;
		formatoTexto->LineAlignment = System::Drawing::StringAlignment::Center;


		array<PointF>^ puntosJugador = CalcularVertices(ladosJugador, radioJugador, posicionJugador);
		System::Drawing::SolidBrush^ pincelJugador = gcnew System::Drawing::SolidBrush(colorJugador);
		e->Graphics->FillPolygon(pincelJugador, puntosJugador);
		delete pincelJugador;

		e->Graphics->DrawString(
			numeroCentralJugador.ToString(),
			fuente,
			pincelTexto,
			posicionJugador,
			formatoTexto
		);


		for each (PowerUp ^ power in listaPowerUps)
		{

			array<PointF>^ puntosPower = CalcularVertices(power->lados, power->radio, power->posicion);
			System::Drawing::SolidBrush^ pincelPower = gcnew System::Drawing::SolidBrush(power->color);
			e->Graphics->FillPolygon(pincelPower, puntosPower);
			delete pincelPower;


			e->Graphics->DrawString(
				power->numeroCentral.ToString(),
				fuente,
				pincelTexto,
				power->posicion,
				formatoTexto
			);
		}

		
		if (gameOver)
		{
			System::Drawing::SolidBrush^ velo = gcnew System::Drawing::SolidBrush(
				System::Drawing::Color::FromArgb(180, 0, 0, 0) 
			);
			e->Graphics->FillRectangle(velo, 0, 0, pistaPictureBox->Width, pistaPictureBox->Height);

			System::Drawing::Font^ fuenteFinal = gcnew System::Drawing::Font("Arial", 48, System::Drawing::FontStyle::Bold);
			System::Drawing::SolidBrush^ pincelFinal = gcnew System::Drawing::SolidBrush(System::Drawing::Color::White);
			System::Drawing::StringFormat^ formatoFinal = gcnew System::Drawing::StringFormat();
			formatoFinal->Alignment = System::Drawing::StringAlignment::Center;
			formatoFinal->LineAlignment = System::Drawing::StringAlignment::Center;

			e->Graphics->DrawString(
				mensajeFinal,
				fuenteFinal,
				pincelFinal,
				(float)(pistaPictureBox->Width / 2),
				(float)(pistaPictureBox->Height / 2),
				formatoFinal
			);

			delete velo;
			delete fuenteFinal;
			delete pincelFinal;
			delete formatoFinal;
		}


		delete fuente;
		delete pincelTexto;
		delete formatoTexto;
	}
		  


	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e)
	{
		posicionJugador.X += velocidadX;
		posicionJugador.Y += velocidadY;

		// --- 2. LÓGICA DE TRAMOS 
		if (ticksParaSiguienteTramo > 0)
		{
			ticksParaSiguienteTramo--;
		}

		if (ticksParaSiguienteTramo == 0) 
		{
			if (tramoActual == 1)
			{
				// Avanzar a T2
				tramoActual = 2;
				velocidadScroll = (float)(random->Next(2) - 4); 
				pistaPictureBox->BackColor = System::Drawing::Color::DeepSkyBlue;
				ticksParaSiguienteTramo = 1000; // 20 seg
				ticksTotalesDelTramo = 1000;
			}
			else if (tramoActual == 2)
			{
				// Avanzar a T3
				tramoActual = 3;
				velocidadScroll = (float)(random->Next(2) - 6); // T3: Derecha a Izquierda (Negativo)
				pistaPictureBox->BackColor = System::Drawing::Color::MediumSpringGreen;
				ticksParaSiguienteTramo = 1250; // T3 dura 25 seg
				ticksTotalesDelTramo = 1250;
			}
			else if (tramoActual == 3)
			{
				
				if (!gameOver) 
				{
					gameOver = true;
					mensajeFinal = "YOU LOST";
					timer1->Stop(); 
				}
			}
		}
		//FIN LÓGICA DE TRAMOS 

		// LÓGICA DE GENERACIÓN (SPAWN) 
		ticksParaSpawn--;
		if (ticksParaSpawn <= 0 && timer1->Enabled) // Solo genera si el timer corre
		{
			GenerarPowerUp();
			ticksParaSpawn = random->Next(75, 126);
		}

		// --- 4. LÓGICA DE COLISIÓN Y DESPAWN (CORREGIDA) ---
		for (int i = listaPowerUps->Count - 1; i >= 0; i--)
		{
			PowerUp^ power = listaPowerUps[i];
			power->Mover();

			double difX = (double)(posicionJugador.X - power->posicion.X);
			double difY = (double)(posicionJugador.Y - power->posicion.Y);
			double distancia = System::Math::Sqrt(System::Math::Pow(difX, 2) + System::Math::Pow(difY, 2));
			if (distancia < (radioJugador + power->radio))
			{
				if (power->color == colorJugador)
				{
					// POWER-UP (mismo color)
					// --- ¡ESTA ES LA LÓGICA DE SUMA QUE PEDISTE! ---
					numeroCentralJugador += power->numeroCentral;

					if (ladosJugador < 10)
					{
						ladosJugador++;
					}

					// --- ¡NUEVO! LÓGICA "YOU WIN" ---
					if (ladosJugador == 10 && tramoActual == 3)
					{
						gameOver = true;
						mensajeFinal = "YOU WIN";
						timer1->Stop(); // ¡Detiene el juego!
					}
				}
				else
				{
					// POWER-DOWN (diferente color)
					numeroCentralJugador -= power->numeroCentral;
					if (numeroCentralJugador < 0) { numeroCentralJugador = 0; }
					if (ladosJugador > 3) { ladosJugador--; }
				}
				listaPowerUps->RemoveAt(i);
			}
			else
			{
				// (Lógica de Despawn... sin cambios)
				bool fueraDePantalla = false;
				if (tramoActual == 1) { /*...*/ }
				else if (tramoActual == 2) { /*...*/ }
				else if (tramoActual == 3) { /*...*/ }
				if (fueraDePantalla) { listaPowerUps->RemoveAt(i); }
			}
		} // fin del bucle for

		// 5. Pedir Redibujar (Sin cambios)
		pistaPictureBox->Invalidate();
		uiPanel->Invalidate();
	}




	private: System::Void JuegoForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::Up)
		{
			velocidadY = -5;
		}
		else if (e->KeyCode == Keys::Down)
		{
			velocidadY = 5;
		}
		else if (e->KeyCode == Keys::Left)
		{
			velocidadX = -5;
		}
		else if (e->KeyCode == Keys::Right)
		{
			velocidadX = 5;
		}
	}
	private: System::Void JuegoForm_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		if (e->KeyCode == Keys::Up || e->KeyCode == Keys::Down)
		{
			velocidadY = 0;
		}

		if (e->KeyCode == Keys::Left || e->KeyCode == Keys::Right)
		{
			velocidadX = 0;
		}


	}
	

private: System::Void pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	System::Drawing::Font^ fuenteEtiqueta = gcnew System::Drawing::Font("Arial", 10, System::Drawing::FontStyle::Bold);
	System::Drawing::Font^ fuenteValor = gcnew System::Drawing::Font("Arial", 10, System::Drawing::FontStyle::Regular);
	System::Drawing::SolidBrush^ pincelNegro = gcnew System::Drawing::SolidBrush(System::Drawing::Color::Black);
	System::Drawing::Pen^ penBorde = gcnew System::Drawing::Pen(System::Drawing::Color::Black, 2); // Pluma para bordes

	int y = 10; 
	// INDICADORES

	e->Graphics->DrawString("Lados:", fuenteEtiqueta, pincelNegro, 10, y);
	e->Graphics->DrawString(ladosJugador.ToString(), fuenteValor, pincelNegro, 80, y);
	y += 20;
	e->Graphics->DrawString("Número:", fuenteEtiqueta, pincelNegro, 10, y);
	e->Graphics->DrawString(numeroCentralJugador.ToString(), fuenteValor, pincelNegro, 80, y);
	y += 20;
	int sumaAngulos = (ladosJugador - 2) * 180;
	e->Graphics->DrawString("Suma Ang:", fuenteEtiqueta, pincelNegro, 10, y);
	e->Graphics->DrawString(sumaAngulos.ToString() + "°", fuenteValor, pincelNegro, 80, y);
	y += 20;
	e->Graphics->DrawString("Velocidad:", fuenteEtiqueta, pincelNegro, 10, y);
	e->Graphics->DrawString(System::Math::Abs(velocidadScroll).ToString(), fuenteValor, pincelNegro, 80, y);
	y += 30;

	//  MINIMAPA

	int mapStartY = y; 


	System::Drawing::Rectangle rectT1 = System::Drawing::Rectangle(10, mapStartY, 150, 40); 
	

	System::Drawing::Rectangle rectT2 = System::Drawing::Rectangle(110, rectT1.Bottom, 50, 80);
	System::Drawing::Rectangle rectT3 = System::Drawing::Rectangle(10, rectT2.Bottom, 150, 40);

	// Dibuja los bordes
	e->Graphics->DrawRectangle(penBorde, rectT1);
	e->Graphics->DrawRectangle(penBorde, rectT2);
	e->Graphics->DrawRectangle(penBorde, rectT3);

	// Dibuja las etiquetas (T1, T2, T3)
	e->Graphics->DrawString("T1", fuenteEtiqueta, pincelNegro, rectT1.Left + 5, rectT1.Top + 5);
	e->Graphics->DrawString("T2", fuenteEtiqueta, pincelNegro, rectT2.Left + 5, rectT2.Top + 5);
	e->Graphics->DrawString("T3", fuenteEtiqueta, pincelNegro, rectT3.Left + 5, rectT3.Top + 5);

	
	System::Drawing::SolidBrush^ pincelJugadorMinimapa = gcnew System::Drawing::SolidBrush(colorJugador);

	float progresoPorcentaje = 0.0f;
	if (ticksTotalesDelTramo > 0)
	{
		int ticksTranscurridos = ticksTotalesDelTramo - ticksParaSiguienteTramo;
		progresoPorcentaje = (float)ticksTranscurridos / (float)ticksTotalesDelTramo;
	}

	if (progresoPorcentaje < 0.0f) progresoPorcentaje = 0.0f;

	float mapX = 0;
	float mapY = 0; 
	int radioPunto = 5;

	if (tramoActual == 1)
	{
		if (progresoPorcentaje > 1.0f) progresoPorcentaje = 1.0f;
		mapX = (float)rectT1.Left + (progresoPorcentaje * rectT1.Width);
		mapY = (float)rectT1.Top + (rectT1.Height / 2);
	}
	else if (tramoActual == 2)
	{
		if (progresoPorcentaje > 1.0f) progresoPorcentaje = 1.0f;
		mapX = (float)rectT2.Left + (rectT2.Width / 2);
		mapY = (float)rectT2.Top + (progresoPorcentaje * rectT2.Height);
	}
	else if (tramoActual == 3)
	{
		int ticksTranscurridos = ticksTotalesDelTramo - ticksParaSiguienteTramo;
		if (ticksTranscurridos < 0) ticksTranscurridos = 0;

		if (ticksParaSiguienteTramo <= 0)
		{
			progresoPorcentaje = 0.0;
		}

		mapX = (float)rectT3.Right - (progresoPorcentaje * rectT3.Width); 
		mapY = (float)rectT3.Top + (rectT3.Height / 2);
	}

	e->Graphics->FillEllipse(pincelJugadorMinimapa, (float)(mapX - radioPunto), (float)(mapY - radioPunto), (float)(radioPunto * 2), (float)(radioPunto * 2));

	delete fuenteEtiqueta;
	delete fuenteValor;
	delete pincelNegro;
	delete penBorde;
	delete pincelJugadorMinimapa;
}
};
}
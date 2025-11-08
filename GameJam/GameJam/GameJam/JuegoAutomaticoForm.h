#pragma once
#include "PowerUp.h"
using namespace System::Collections::Generic;
using namespace System::Drawing;
namespace GameJam {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de JuegoAutomaticoForm
	/// </summary>
	public ref class JuegoAutomaticoForm : public System::Windows::Forms::Form
	{
	public:
		JuegoAutomaticoForm(void)
		{
			InitializeComponent();
			this->DoubleBuffered = true;
			
			this->pistaPictureBox->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &JuegoAutomaticoForm::pistaPictureBox_Paint);
			this->uiPanel->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &JuegoAutomaticoForm::uiPanel_Paint);

			random = gcnew System::Random();
			coloresPermitidos = gcnew array<Color>{ Color::Red, Color::Yellow, Color::Blue };
			listaPowerUps = gcnew List<PowerUp^>();
			
			posicionJugador = PointF((float)(pistaPictureBox->Width / 2), (float)(pistaPictureBox->Height / 2));

			radioJugador = 25.0f;
			ladosJugador = 3;
			colorJugador = coloresPermitidos[random->Next(coloresPermitidos->Length)];
			numeroCentralJugador = 0;
			velocidadX = 0; // Se usará para el movimiento automatico
			velocidadY = 0; 
			velocidadAutomatica = 8; // Velocidad base para el movimiento automatico

			ticksParaSpawn = 75; // Controla la generación de PowerUps
			tramoActual = 1; // 1: Izquierda a Derecha, 2: Abajo a Arriba, 3: Derecha a Izquierda
			ticksParaSiguienteTramo = 750; // Duración del primer tramo
			ticksTotalesDelTramo = 750; // Para el minimapa
			velocidadScroll = (float)(random->Next(3) + 2); // Velocidad del movimiento de los PowerUps

			gameOver = false;
			mensajeFinal = "";
		}

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~JuegoAutomaticoForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pistaPictureBox;
	private: System::Windows::Forms::PictureBox^ uiPanel;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::ComponentModel::IContainer^ components;
	protected:

	protected:


	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		PointF posicionJugador;
		float radioJugador;
		int ladosJugador;
		Color colorJugador;
		int numeroCentralJugador;
		float velocidadX;
		float velocidadY;
		int velocidadAutomatica;
		Random^ random;
		List<PowerUp^>^ listaPowerUps;
		array<Color>^ coloresPermitidos;
		int ticksParaSpawn; // Controla la generación de PowerUps
		int tramoActual; // 1: Izquierda a Derecha, 2: Abajo a Arriba, 3: Derecha a Izquierda
		int ticksParaSiguienteTramo; // Duración del primer tramo
		int ticksTotalesDelTramo; // Para el minimapa
		float velocidadScroll; // Velocidad del movimiento de los PowerUps
		bool gameOver;
		String^ mensajeFinal;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->pistaPictureBox = (gcnew System::Windows::Forms::PictureBox());
			this->uiPanel = (gcnew System::Windows::Forms::PictureBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pistaPictureBox))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->uiPanel))->BeginInit();
			this->SuspendLayout();
			
			this->pistaPictureBox->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pistaPictureBox->Location = System::Drawing::Point(2, 1);
			this->pistaPictureBox->Name = L"pistaPictureBox";
			this->pistaPictureBox->Size = System::Drawing::Size(954, 718);
			this->pistaPictureBox->TabIndex = 1;
			this->pistaPictureBox->TabStop = false;
			this->pistaPictureBox->Click += gcnew System::EventHandler(this, &JuegoAutomaticoForm::pistaPictureBox_Click);
			
			this->uiPanel->BackColor = System::Drawing::SystemColors::ActiveBorder;
			this->uiPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->uiPanel->Location = System::Drawing::Point(1014, 200);
			this->uiPanel->Name = L"uiPanel";
			this->uiPanel->Size = System::Drawing::Size(226, 293);
			this->uiPanel->TabIndex = 3;
			this->uiPanel->TabStop = false;
			
			this->timer1->Enabled = true;
			this->timer1->Interval = 20; // 50 FPS
			this->timer1->Tick += gcnew System::EventHandler(this, &JuegoAutomaticoForm::timer1_Tick);
			
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1280, 720);
			this->Controls->Add(this->uiPanel);
			this->Controls->Add(this->pistaPictureBox);
			this->Name = L"JuegoAutomaticoForm";
			this->Text = L"JuegoAutomaticoForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pistaPictureBox))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->uiPanel))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {

		//Logica del movimiento automatico
		if (!gameOver)
		{
			PowerUp^ objetivo = nullptr;
			PowerUp^ amenaza = nullptr;
			double min_distancia_powerup = 99999.0;
			double min_distancia_amenaza = 99999.0;

			//logica usada con ia para que el personaje evada los power downs
			//Si el power down esta dentro de este radio, el juego automaticamente lo evitara
			float radioPeligroIA = radioJugador * 4.0f; // 4 veces el radio del jugador

			//Buscar el power up y el power down mas cercano 
			for each(PowerUp ^ power in listaPowerUps)
			{
				double difX = (double)(posicionJugador.X - power->posicion.X);
				double difY = (double)(posicionJugador.Y - power->posicion.Y);
				double distancia = System::Math::Sqrt(System::Math::Pow(difX, 2) + System::Math::Pow(difY, 2));

				if (power->color == colorJugador)
				{
					// Es un PowerUp 
					if (distancia < min_distancia_powerup)
					{
						min_distancia_powerup = distancia;
						objetivo = power;
					}
				}
				else // Es un PowerDown 
				{
					if (distancia < min_distancia_amenaza)
					{
						min_distancia_amenaza = distancia;
						amenaza = power;
					}
				}
			}

			//Precisar el movimiento 
			if (amenaza != nullptr && min_distancia_amenaza < radioPeligroIA)
			{
				// Si el power down está dentro del radio de peligro, evadirlo
				float difX = amenaza->posicion.X - posicionJugador.X;
				float difY = amenaza->posicion.Y - posicionJugador.Y;

				
				// Calculamos el vector para evitar los power downs
				double magnitud = System::Math::Sqrt(difX * difX + difY * difY);
				if (magnitud > 0)
				{
					// Multiplicamos por -1 para invertir la dirección
					velocidadX = (float)((-difX / magnitud) * velocidadAutomatica);
					velocidadY = (float)((-difY / magnitud) * velocidadAutomatica);
				}
			}
			//Perseguir los power ups
			else if (objetivo != nullptr)
			{
				// Moverse hacia el PowerUp 
				float difX = objetivo->posicion.X - posicionJugador.X;
				float difY = objetivo->posicion.Y - posicionJugador.Y;

				// Normalización del vector y aplicación de velocidad
				double magnitud = System::Math::Sqrt(difX * difX + difY * difY);
				if (magnitud > 0)
				{
					velocidadX = (float)((difX / magnitud) * velocidadAutomatica);
					velocidadY = (float)((difY / magnitud) * velocidadAutomatica);
				}
				else {
					velocidadX = 0;
					velocidadY = 0;
				}
			}
			//Movimiento aleatorio suave
			else
			{
				//La figura se movera de forma aleatoria suave cuando no haya objetivos ni amenazas
				if (random->Next(30) < 1)
				{
					velocidadX = (float)(random->Next(-1, 2) * (velocidadAutomatica / 2.0f));
					velocidadY = (float)(random->Next(-1, 2) * (velocidadAutomatica / 2.0f));
				}
			}

			//Para que la figura no se salga de la pantalla
			float margen = radioJugador * 1.0f;

			if (posicionJugador.X < margen) {
				velocidadX = (float)velocidadAutomatica;
			}
			if (posicionJugador.X > pistaPictureBox->Width - margen) {
				velocidadX = (float)-velocidadAutomatica;
			}
			if (posicionJugador.Y < margen) {
				velocidadY = (float)velocidadAutomatica;
			}
			if (posicionJugador.Y > pistaPictureBox->Height - margen) {
				velocidadY = (float)-velocidadAutomatica;
			}
		}
		posicionJugador.X += velocidadX;
		posicionJugador.Y += velocidadY;
		// FIN LÓGICA AUTOMÁTICA
		

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
				// Velocidad negativa para ir hacia arriba
				velocidadScroll = (float)(random->Next(2) - 4);
				pistaPictureBox->BackColor = System::Drawing::Color::DeepSkyBlue;
				ticksParaSiguienteTramo = 1000; // 20 seg
				ticksTotalesDelTramo = 1000;
			}
			else if (tramoActual == 2)
			{
				// Avanzar a T3
				tramoActual = 3;
				// Velocidad negativa para ir hacia la izquierda
				velocidadScroll = (float)(random->Next(2) - 6);
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

		//GENERACION DE SPAWN
		ticksParaSpawn--;
		if (ticksParaSpawn <= 0 && timer1->Enabled) // Solo genera si el timer corre
		{
			GenerarPowerUp();
			ticksParaSpawn = random->Next(75, 126);
		}

		//COLISIONES
		for (int i = listaPowerUps->Count - 1; i >= 0; i--)
		{
			PowerUp^ power = listaPowerUps[i];
			power->Mover();

			double difX = (double)(posicionJugador.X - power->posicion.X);
			double difY = (double)(posicionJugador.Y - power->posicion.Y);
			double distancia = System::Math::Sqrt(System::Math::Pow(difX, 2) + System::Math::Pow(difY, 2));

			// Colisión
			if (distancia < (radioJugador + power->radio))
			{
				if (power->color == colorJugador)
				{
					// POWER-UP (mismo color)
					numeroCentralJugador += power->numeroCentral;

					if (ladosJugador < 10)
					{
						ladosJugador++;
					}

					// Lógica de Victoria
					if (ladosJugador == 10 && tramoActual == 3)
					{
						gameOver = true;
						mensajeFinal = "YOU WIN";
						timer1->Stop();
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
				// Despawn (Fuera de pantalla)
				bool fueraDePantalla =
					(tramoActual == 1 && power->posicion.X > pistaPictureBox->Width + 50) ||
					(tramoActual == 2 && power->posicion.Y < -50) ||
					(tramoActual == 3 && power->posicion.X < -50);

				if (fueraDePantalla) { listaPowerUps->RemoveAt(i); }
			}
		}

		pistaPictureBox->Invalidate();
		uiPanel->Invalidate();
	}


	private: System::Void pistaPictureBox_Click(System::Object^ sender, System::EventArgs^ e) {
	}
		   array<PointF>^ CalcularVertices(int lados, float radio, PointF centro) {
			 
			   if (lados < 3)
				   lados = 3;

			   array<PointF>^ vertices = gcnew array<PointF>(lados);
			   double anguloPorVertice = 2 * System::Math::PI / lados;

			   for (int i = 0; i < lados; i++) {

				   double anguloActual = (i * anguloPorVertice) - (System::Math::PI / 2);
				   float x = (float)(centro.X + radio * System::Math::Cos(anguloActual));
				   float y = (float)(centro.Y + radio * System::Math::Sin(anguloActual));
				   vertices[i] = PointF(x, y);
			   }
			   return vertices;

		   }

		   void GenerarPowerUp() {
			   
			   PointF pos;
			   float velX = 0;
			   float velY = 0;

			   Color color = coloresPermitidos[random->Next(coloresPermitidos->Length)];
			   int lados = random->Next(3, 7);
			   int numero = random->Next(1, 6);

			   if (tramoActual == 1)
			   {
				   // --- TRAMO 1: Izquierda a Derecha ---
				   int posX = -50;
				   int posY = random->Next(radioJugador, pistaPictureBox->Height - radioJugador);
				   pos = PointF((float)posX, (float)posY);

				   // Se mueve a la DERECHA
				   velX = velocidadScroll;
				   velY = 0;
			   }
			   else if (tramoActual == 2)
			   {
				   // --- TRAMO 2: Abajo Hacia Arriba ---
				   int posX = random->Next(radioJugador, pistaPictureBox->Width - radioJugador);
				   int posY = pistaPictureBox->Height + 50;
				   pos = PointF((float)posX, (float)posY);

				   velX = 0;
				   // En el tramo 2, los objetos deben subir
				   velY = velocidadScroll;
			   }
			   else // (tramoActual == 3)
			   {
				   // --- TRAMO 3: Derecha a Izquierda ---
				   int posX = pistaPictureBox->Width + 50;
				   int posY = random->Next(radioJugador, pistaPictureBox->Height - radioJugador);
				   pos = PointF((float)posX, (float)posY);

				   // Se mueve a la IZQUIERDA 
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
		e->Graphics->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

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


	private: System::Void uiPanel_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		e->Graphics->SmoothingMode = System::Drawing::Drawing2D::SmoothingMode::AntiAlias;

		System::Drawing::Font^ fuenteEtiqueta = gcnew System::Drawing::Font("Arial", 10, System::Drawing::FontStyle::Bold);
		System::Drawing::Font^ fuenteValor = gcnew System::Drawing::Font("Arial", 10, System::Drawing::FontStyle::Regular);
		System::Drawing::SolidBrush^ pincelNegro = gcnew System::Drawing::SolidBrush(System::Drawing::Color::Black);
		System::Drawing::Pen^ penBorde = gcnew System::Drawing::Pen(System::Drawing::Color::Black, 2);

		int y = 10;
		
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

		// MINIMAPA

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
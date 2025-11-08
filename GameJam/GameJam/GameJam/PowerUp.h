#pragma once

using namespace System::Drawing;

public ref class PowerUp
{
public:

    PointF posicion;
    int lados;
    Color color;
    int numeroCentral;
    float radio;
    float velocidadX;
    float velocidadY;

    // Ahora recibe ambas velocidades
    PowerUp(PointF pos, int lad, Color col, int num, float rad, float velX, float velY)
    {
        posicion = pos;
        lados = lad;
        color = col;
        numeroCentral = num;
        radio = rad;

        velocidadX = velX; // Asigna velocidad horizontal
        velocidadY = velY; // Asigna velocidad vertical
    }

    
    // Ahora mueve en ambas direcciones
    void Mover()
    {
        posicion.X += velocidadX;
        posicion.Y += velocidadY;
    }
};
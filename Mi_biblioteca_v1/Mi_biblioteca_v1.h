#ifndef MI_BIBLIOTECA_V1_H
#define MI_BIBLIOTECA_V1_H

// FUNCIONES PRINCIPALES
void iniciarJuego();
void actualizarJuego();
void renderizarJuego();
void procesarEntrada(char tecla);
void terminarJuego(bool victoria);

// PERSONAJE PRINCIPAL
void moverPersonaje(char direccion);
void interactuarConPersonaje();
void iniciarCombate(const char* enemigo);
void usarItemEnCombate(const char* item);
void abrirInventario();
void actualizarSalud(int cambio);
int obtenerSalud();
bool tieneItemEspecial();

// INVENTARIO
void agregarItem(const char* item);
void eliminarItem(const char* item);
bool usarItem(const char* item);
bool contieneItem(const char* item);
void mostrarInventario();
void guardarConsejo(const char* consejo);
void mostrarConsejos();

// TUTOR
void interactuarConTutor(int id);
void tutorDarConsejo(const char* consejo);
void tutorEntregarItem(const char* item);
void tutorPorNivel(int nivel);

// ENEMIGOS - BULLYS
void aparecerBully();
void robarTarea();
void evitarBully();
void usarItemContraBully(const char* item);

// ENEMIGOS - PERROS
void aparecerPerro();
void alimentarPerro(const char* comida);
void convertirEnMascota();
void ayudarContraBullys();

// ENEMIGOS - TULPAS
void aparecerTulpa();
void presentarPreguntasTulpa();
void evaluarRespuestasTulpa(const char* respuestas[]);
void quitarLibroSiFallas();
void derrotarTulpa();

// JEFE FINAL - NERD
void iniciarBossNerd();
void presentarPreguntasNerd();
void reducirIQ();
void restaurarLibros();
void entregarBono();

// JEFE FINAL - PRESIDENTA
void iniciarBossPresidenta();
void bloquearTutor();
void cuestionarioPresidenta();
void devolverLibrosRobados();

// JEFE FINAL - NIGHTMARE
void iniciarBossNightmare();
void preguntasNightmare();
void quitarLibrosPorTiempo();
void quitarLibrosPorError();
void despertarPersonaje();


// Nivel 1 - Escuela
void cargarNivel1();
void resolverPizarra(int id);
void obtenerLlaveSecreta();
void abrirAulaOculta();
void verificarProgresoNivel1();

// Nivel 2 - Campamento
void cargarNivel2();
void recuperarCuadernos();
void obtenerMartillo();
void abrirCabanaSecreta();
void completarEjerciciosCampamento();
void verificarProgresoNivel2();

// Nivel 3 - Dream Park
void cargarNivel3();
void explorarDreamPark();
void encontrarLibroSecreto();
void derrotarTulpasParaLibro();
void verificarProgresoNivel3();

// QUIZZ TIME
void iniciarQuiz(int nivel);
void generarPreguntasQuiz(int nivel);
bool verificarRespuestasQuiz(const char* respuestas[]);
void otorgarItemPorQuiz(const char* item);

// PUNTAJE Y PROGRESO
void actualizarProgreso(int nivel, int progreso);
void verificarPorcentajeCompletado(int nivel);
void mostrarResultadosFinales();

// MENÚ
void mostrarMenuPrincipal();
void mostrarInstrucciones();
void seleccionarNivel();
void mostrarPantallaGameOver();
void mostrarPantallaVictoria();

#endif 




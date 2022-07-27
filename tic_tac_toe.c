//Se imporantan las bibliotecas que se utilizaran en el programa

#include <gtk/gtk.h>
#include <stdlib.h>

// Se crean las funciones inciales
void inicializar(GtkButton *buttonInit,int i,int j);
int verificar_gane(int a[3][3]);
void restablecer_botones();

// Se crean las variables generales
static GtkButton *statusClick,*gameClick;
static GtkButton *button[3][3]={{NULL,NULL,NULL},{NULL,NULL,NULL},{NULL,NULL,NULL}};
static int bandera=0;
static int continuar=1;
static int initialise=0;
static int status_bandera=0;
static int pressed[3][3]={{0,0,0},{0,0,0},{0,0,0}};
static int espacios=0;
static int lista[3][3]={{0,0,0},{0,0,0},{0,0,0}};
static int gameType=0;

// Se crea la funcion main
int main(int argc, char *argv[])
{
    // Se declara el builder y se agrega la pantalla
    GtkBuilder      *builder;
    GtkWidget       *window;

    gtk_init(&argc, &argv);

    // Se inicia el builder y se carga el archivo glade
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "tic_tac_toe.glade", NULL);

    //S e define la ventana y se agrega la pantalla main
    window = GTK_WIDGET (gtk_builder_get_object(builder, "Juego"));
    gtk_builder_connect_signals(builder, NULL);

    // Se muestra la pantalla del juego
    gtk_widget_show(window);

    // Se usa un puntero de desreferencia
    g_object_unref(builder);
    gtk_main();
    return 0;
}

// Se crea la funcion para salir del juego al presionar el boton
void salir_activado()
{
    gtk_main_quit();
    exit(0);
}

// Se crea la funcion para reinciar el juego al presionar el boton
void reinicio_activado(GtkWidget *click_button, gpointer   user_data)
{
  //T odas las variables vuelven a su estado inicial para reiniciar el juego
  int i,j;
 if(!status_bandera) return;
 gameType=0; bandera=0; espacios=0; continuar=1; initialise=0;
 GtkWidget *Juego = (GtkWidget *) user_data;
 gtk_widget_destroy(Juego);
  for(i=0;i<3;i++)
  {
      for(j=0;j<3;j++)
      {
          button[i][j]=NULL;
          lista[i][j]=0;
          pressed[i][j]=0;
      }
  }
  main(0, NULL);
  // Se llama a la fucion de restablecer los botones
  restablecer_botones();
}

//S e crea la funcion del boton listo para empezar a jugar
void listo_activado(GtkWidget *click_button, gpointer   user_data)
{
  gameType = 0;
  gtk_widget_destroy((GtkWidget *) user_data);
  // Se incia con el turno de las X
  gtk_button_set_label(gameClick, "Turno X");
}

// Se crea la funcion del boton jugar
void jugar_activado(GtkWidget *click_button, gpointer   user_data)
{
  gameClick = (GtkButton *) user_data;
  statusClick = (GtkButton *) user_data;
  status_bandera=1;
  if(!status_bandera) return;
  if(bandera)
  {
    gtk_button_set_label(statusClick, "Reiniciar para nueva partida");
    return;
  }
  bandera=1;
  gtk_button_set_label(statusClick, "Jugar");
  GtkBuilder  *builder;
  GtkWidget   *gameDialog;
  // Se inicializa el builder con la ventana del boton listo_activado
  builder = gtk_builder_new();
  gtk_builder_add_from_file (builder, "tic_tac_toe.glade", NULL);
  gameDialog = GTK_WIDGET(gtk_builder_get_object(builder, "vent_lis"));
  gtk_builder_connect_signals(builder, NULL);
  g_object_unref(builder);
  gtk_dialog_run (GTK_DIALOG (gameDialog));
  //Se elimina el boton despues de presionarlo
  gtk_widget_destroy(gameDialog);
}

// Se crea la funcion inicializar para la primera vez que se presionen los botones
void inicializar(GtkButton *buttonInit,int i,int j)
{
    if(button[i][j]!=NULL) return;
    button[i][j]=buttonInit;
    gtk_button_set_label(button[i][j], "OK");
    if(++initialise==10)
    {
      initialise=0;
      gtk_button_set_label(statusClick, "Turno X");
      restablecer_botones();
    }
}

// Se crea la funcion boton11_activado la cual se activa cuando se presiona ese
// boton
int boton11_activado(GtkWidget *click_button, gpointer   user_data)
{
  GtkButton *buttonTemp = (GtkButton *) user_data;

  // Si el juego esta corriendo se ejecuta
  if(initialise!=0)
  {
    inicializar(buttonTemp,0,0);
    return 0;
  }

  // Se ejecuta si el botón se presiona
  if(pressed[0][0]) return 0;

  if(bandera&&continuar)
  {
    // Se ejecuta durante el turno de las X
    if(++espacios%2)
    {
      // Se añade el valor a la lista
      lista[0][0]=1;
      // Se añade a la interfaz la X
      gtk_button_set_label(buttonTemp, "X");
      pressed[0][0]=1;
      // Se verficia si alguien gano y se dan las opciones
      switch(verificar_gane(lista))
      {
        // Si es 0 y los espacios son 9 imprime un Emapte
        case 0: if(espacios==9)
                {
                  gtk_button_set_label(statusClick, "Empate");
                  continuar=0; return 0;
                } break;
        // Si es 1 ganaron las X
        case 1: gtk_button_set_label(statusClick, "Ganó X");
                continuar=0; return 0;
        // Si es 2 ganaron las O
        case 2: gtk_button_set_label(statusClick, "Ganó O");
                continuar=0; return 0;
      }
      // Se cambia el turno a las O
      gtk_button_set_label(statusClick, "Turno O");
    }
    // Se ejecuta cuando el turno es de las O
    else
    {
      lista[0][0]=2;
      // Se añade a la interfaz la O
      gtk_button_set_label(buttonTemp, "O");
      switch(verificar_gane(lista))
      {
        case 1: gtk_button_set_label(statusClick, "Ganó X");
                continuar=0; return 0;
        case 2: gtk_button_set_label(statusClick, "Ganó O");
                continuar=0; return 0;
      }
      gtk_button_set_label(statusClick, "Turno X");
    }
    pressed[0][0]=1;
  }
  return 0;
}

// Botón en la posición 12
int boton12_activado(GtkWidget *click_button, gpointer   user_data)
{
  GtkButton *buttonTemp = (GtkButton *) user_data;

  if(initialise!=0)
  {
    inicializar(buttonTemp,0,1);
    return 0;
  }

  if(pressed[0][1]) return 0;

  if(bandera&&continuar)
  {
    if(++espacios%2)
    {
      lista[0][1]=1;
      gtk_button_set_label(buttonTemp, "X");
      pressed[0][1]=1;
      switch(verificar_gane(lista))
      {
        case 0: if(espacios==9)
                {
                  gtk_button_set_label(statusClick, "Empate");
                  continuar=0; return 0;
                } break;
        case 1: gtk_button_set_label(statusClick, "Ganó X");
                continuar=0; return 0;
        case 2: gtk_button_set_label(statusClick, "Ganó O");
                continuar=0; return 0;
      }
      gtk_button_set_label(statusClick, "Turno O");
    }
    else
    {
      lista[0][1]=2;
      gtk_button_set_label(buttonTemp, "O");
      switch(verificar_gane(lista))
      {
        case 1: gtk_button_set_label(statusClick, "Ganó X");
                continuar=0; return 0;
        case 2: gtk_button_set_label(statusClick, "Ganó O");
                continuar=0; return 0;
      }
      gtk_button_set_label(statusClick, "Turno X");
    }
    pressed[0][1]=1;
  }
  return 0;
}

// Botón en la posición 13
int boton13_activado(GtkWidget *click_button, gpointer   user_data)
{
  GtkButton *buttonTemp = (GtkButton *) user_data;

  if(initialise!=0)
  {
    inicializar(buttonTemp,0,2);
    return 0;
  }

  if(pressed[0][2]) return 0;

  if(bandera&&continuar)
  {
    if(++espacios%2)
    {
      lista[0][2]=1;
      gtk_button_set_label(buttonTemp, "X");
      pressed[0][2]=1;
      switch(verificar_gane(lista))
      {
        case 0: if(espacios==9)
                {
                  gtk_button_set_label(statusClick, "Empate");
                  continuar=0; return 0;
                } break;
        case 1: gtk_button_set_label(statusClick, "Ganó X");
                continuar=0; return 0;
        case 2: gtk_button_set_label(statusClick, "Ganó O");
                continuar=0; return 0;
      }
      gtk_button_set_label(statusClick, "Turno O");
    }
    else
    {
      lista[0][2]=2;
      gtk_button_set_label(buttonTemp, "O");
      switch(verificar_gane(lista))
      {
        case 1: gtk_button_set_label(statusClick, "Ganó X");
                continuar=0; return 0;
        case 2: gtk_button_set_label(statusClick, "Ganó O");
                continuar=0; return 0;
      }
      gtk_button_set_label(statusClick, "Turno X");
    }
    pressed[0][2]=1;
  }
  return 0;
}

// Botón en la posición 21
int boton21_activado(GtkWidget *click_button, gpointer   user_data)
{
  GtkButton *buttonTemp = (GtkButton *) user_data;

  if(initialise!=0)
  {
    inicializar(buttonTemp,1,0);
    return 0;
  }

  if(pressed[1][0]) return 0;

  if(bandera&&continuar)
  {
    if(++espacios%2)
    {
      lista[1][0]=1;
      gtk_button_set_label(buttonTemp, "X");
      pressed[1][0]=1;
      switch(verificar_gane(lista))
      {
        case 0: if(espacios==9)
                {
                  gtk_button_set_label(statusClick, "Empate");
                  continuar=0; return 0;
                } break;
        case 1: gtk_button_set_label(statusClick, "Ganó X");
                continuar=0; return 0;
        case 2: gtk_button_set_label(statusClick, "Ganó O");
                continuar=0; return 0;
      }
      gtk_button_set_label(statusClick, "Turno O");
    }
    else
    {
      lista[1][0]=2;
      gtk_button_set_label(buttonTemp, "O");
      switch(verificar_gane(lista))
      {
        case 1: gtk_button_set_label(statusClick, "Ganó X");
                continuar=0; return 0;
        case 2: gtk_button_set_label(statusClick, "Ganó O");
                continuar=0; return 0;
      }
      gtk_button_set_label(statusClick, "Turno X");
    }
    pressed[1][0]=1;
  }
  return 0;
}

// Botón en la posición 22
int boton22_activado(GtkWidget *click_button, gpointer   user_data)
{
  GtkButton *buttonTemp = (GtkButton *) user_data;

  if(initialise!=0)
  {
    inicializar(buttonTemp,1,1);
    return 0;
  }

  if(pressed[1][1]) return 0;

  if(bandera&&continuar)
  {
    if(++espacios%2)
    {
      lista[1][1]=1;
      gtk_button_set_label(buttonTemp, "X");
      pressed[1][1]=1;
      switch(verificar_gane(lista))
      {
        case 0: if(espacios==9)
                {
                  gtk_button_set_label(statusClick, "Empate");
                  continuar=0; return 0;
                } break;
        case 1: gtk_button_set_label(statusClick, "Ganó X");
                continuar=0; return 0;
        case 2: gtk_button_set_label(statusClick, "Ganó O");
                continuar=0; return 0;
      }
      gtk_button_set_label(statusClick, "Turno O");
    }
    else
    {
      lista[1][1]=2;
      gtk_button_set_label(buttonTemp, "O");
      switch(verificar_gane(lista))
      {
        case 1: gtk_button_set_label(statusClick, "Ganó X");
                continuar=0; return 0;
        case 2: gtk_button_set_label(statusClick, "Ganó O");
                continuar=0; return 0;
      }
      gtk_button_set_label(statusClick, "Turno X");
    }
    pressed[1][1]=1;
  }
  return 0;
}

// Botón en la posición 23
int boton23_activado(GtkWidget *click_button, gpointer   user_data)
{
  GtkButton *buttonTemp = (GtkButton *) user_data;

  if(initialise!=0)
  {
    inicializar(buttonTemp,1,2);
    return 0;
  }

  if(pressed[1][2]) return 0;

  if(bandera&&continuar)
  {
    if(++espacios%2)
    {
      lista[1][2]=1;
      gtk_button_set_label(buttonTemp, "X");
      pressed[1][2]=1;
      switch(verificar_gane(lista))
      {
        case 0: if(espacios==9)
                {
                  gtk_button_set_label(statusClick, "Empate");
                  continuar=0; return 0;
                } break;
        case 1: gtk_button_set_label(statusClick, "Ganó X");
                continuar=0; return 0;
        case 2: gtk_button_set_label(statusClick, "Ganó O");
                continuar=0; return 0;
      }
      gtk_button_set_label(statusClick, "Turno O");
    }
    else
    {
      lista[1][2]=2;
      gtk_button_set_label(buttonTemp, "O");
      switch(verificar_gane(lista))
      {
        case 1: gtk_button_set_label(statusClick, "Ganó X");
                continuar=0; return 0;
        case 2: gtk_button_set_label(statusClick, "Ganó O");
                continuar=0; return 0;
      }
      gtk_button_set_label(statusClick, "Turno X");
    }
    pressed[1][2]=1;
  }
  return 0;
}

// Botón en la posición 31
int boton31_activado(GtkWidget *click_button, gpointer   user_data)
{
  GtkButton *buttonTemp = (GtkButton *) user_data;

  if(initialise!=0)
  {
    inicializar(buttonTemp,2,0);
    return 0;
  }

  if(pressed[2][0]) return 0;

  if(bandera&&continuar)
  {
    if(++espacios%2)
    {
      lista[2][0]=1;
      gtk_button_set_label(buttonTemp, "X");
      pressed[2][0]=1;
      switch(verificar_gane(lista))
      {
        case 0: if(espacios==9)
                {
                  gtk_button_set_label(statusClick, "Empate");
                  continuar=0; return 0;
                } break;
        case 1: gtk_button_set_label(statusClick, "Ganó X");
                continuar=0; return 0;
        case 2: gtk_button_set_label(statusClick, "Ganó O");
                continuar=0; return 0;
      }
      gtk_button_set_label(statusClick, "Turno O");
    }
    else
    {
      lista[2][0]=2;
      gtk_button_set_label(buttonTemp, "O");
      switch(verificar_gane(lista))
      {
        case 1: gtk_button_set_label(statusClick, "Ganó X");
                continuar=0; return 0;
        case 2: gtk_button_set_label(statusClick, "Ganó O");
                continuar=0; return 0;
      }
      gtk_button_set_label(statusClick, "Turno X");
    }
    pressed[2][0]=1;
  }
  return 0;
}

// Botón en la posición 32
int boton32_activado(GtkWidget *click_button, gpointer   user_data)
{
  GtkButton *buttonTemp = (GtkButton *) user_data;

  if(initialise!=0)
  {
      inicializar(buttonTemp,2,1);
      return 0;
  }

  if(pressed[2][1]) return 0;

  if(bandera&&continuar)
  {
    if(++espacios%2)
    {
      lista[2][1]=1;
      gtk_button_set_label(buttonTemp, "X");
      pressed[2][1]=1;
      switch(verificar_gane(lista))
      {
        case 0: if(espacios==9)
                {
                  gtk_button_set_label(statusClick, "Empate");
                  continuar=0; return 0;
                } break;
        case 1: gtk_button_set_label(statusClick, "Ganó X");
                continuar=0; return 0;
        case 2: gtk_button_set_label(statusClick, "Ganó O");
                continuar=0; return 0;
      }
      gtk_button_set_label(statusClick, "Turno O");
    }
    else
    {
      lista[2][1]=2;
      gtk_button_set_label(buttonTemp, "O");
      switch(verificar_gane(lista))
      {
        case 1: gtk_button_set_label(statusClick, "Ganó X");
                continuar=0; return 0;
        case 2: gtk_button_set_label(statusClick, "Ganó O");
                continuar=0; return 0;
      }
      gtk_button_set_label(statusClick, "Turno X");
    }
    pressed[2][1]=1;
  }
  return 0;
}

// Botón en la posición 33
int boton33_activado(GtkWidget *click_button, gpointer   user_data)
{
  GtkButton *buttonTemp = (GtkButton *) user_data;

  if(initialise!=0)
  {
      inicializar(buttonTemp,2,2);
      return 0;
  }

  if(pressed[2][2]) return 0;

  if(bandera&&continuar)
  {
    if(++espacios%2)
    {
      lista[2][2]=1;
      gtk_button_set_label(buttonTemp, "X");
      pressed[2][2]=1;
      switch(verificar_gane(lista))
      {
        case 0: if(espacios==9)
                {
                  gtk_button_set_label(statusClick, "Empate");
                  continuar=0; return 0;
                } break;
        case 1: gtk_button_set_label(statusClick, "Ganó X");
                continuar=0; return 0;
        case 2: gtk_button_set_label(statusClick, "Ganó O");
                continuar=0; return 0;
      }
      gtk_button_set_label(statusClick, "Turno del O");
    }
    else
    {
      lista[2][2]=2;
      gtk_button_set_label(buttonTemp, "O");
      switch(verificar_gane(lista))
      {
        case 1: gtk_button_set_label(statusClick, "Ganó X");
                continuar=0; return 0;
        case 2: gtk_button_set_label(statusClick, "Ganó O");
                continuar=0; return 0;
      }
      gtk_button_set_label(statusClick, "Turno del X");
    }
    pressed[2][2]=1;
  }
  return 0;
}

// Se crea la funcion para verficar si alguien gano
int verificar_gane(int a[3][3])
{
  // Se crean las variables
  int X_gano=0;
  int O_gano=0;
  int i,j;
  for(i=0;i<3;i++)
  {
    for(j=0;j<3;j++)
    {
      // Si en la matriz hay 1 es porque hay X
      // Si en la matriz hay 2 es porque hay O
      if(a[i][j]==1) X_gano++;
      if(a[i][j]==2) O_gano++;
    }
    // Si hay 3 X en raya se retorna 1
    // Si hay 3 O en raya se retorna 2
    if(X_gano==3) return 1;
    if(O_gano==3) return 2;
    // Se reincian las variables
    X_gano=0; O_gano=0;
  }
  for(i=0;i<3;i++)
  {
    for(j=0;j<3;j++)
    {
      if(a[j][i]==1) X_gano++;
      if(a[j][i]==2) O_gano++;
    }
    if(X_gano==3) return 1;
    if(O_gano==3) return 2;
    X_gano=0; O_gano=0;
  }
  for(i=0;i<3;i++)
  {
    if(a[i][i]==1) X_gano++;
    if(a[i][i]==2) O_gano++;
  }
  if(X_gano==3) return 1;
  if(O_gano==3) return 2;
  X_gano=0; O_gano=0;
  for(i=0,j=2;i<3;i++,j--)
  {
    if(a[i][j]==1) X_gano++;
    if(a[i][j]==2) O_gano++;
  }
  if(X_gano==3) return 1;
  if(O_gano==3) return 2;
  // Si se retona 0 es que no ha ganado nadie
  return 0;
}

// Se crea la funcion de restablecer los botones
void restablecer_botones()
{
    int i,j;
    for(i=0;i<3;i++)
    {
        for(j=0;j<3;j++)
        {
            // Se vuelven a poner en espacios vacios
            gtk_button_set_label(button[i][j], " ");
        }
    }
}

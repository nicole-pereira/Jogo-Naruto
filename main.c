#include <allegro.h>
#include <math.h>
#include <time.h>

/// variaveis globais
int colidir(int ax, int ay, int bx, int by, int aw, int ah, int bw, int bh);
int m;
int caindo = 1;
float vel_y = 0;
float gravidade = 0.1;
float eixo_y = 0.0;

volatile int timer;
void incrementa_timer() { timer++; }
END_OF_FUNCTION(incrementa_timer)

volatile int exit_program;
void fecha_programa() { exit_program = TRUE; }
END_OF_FUNCTION(fecha_programa)

volatile int milisegundos;
void msec_counter() { milisegundos++; }
END_OF_FUNCTION(msec_counter)

volatile int ticks;
void tick_counter() { ticks++; }
END_OF_FUNCTION(tick_counter)

///função menu
int menu()
{
    BITMAP* buf = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* seta = load_bitmap("seta.bmp", NULL);
    BITMAP* fundo = load_bitmap("fundo.bmp", NULL);
    BITMAP* logo = load_bitmap("logo.bmp", NULL);

    int setay = 260;
    m = 1;



    while(m==1)
    {


            if(key[KEY_S])
            {
                setay = 330;
            }



            if(key[KEY_W])
            {
                setay = 260;
            }
            if(setay == 260 && key[KEY_ENTER])
                {
                    m = 0;
                    END_OF_FUNCTION(menu);

                }
            if(setay == 330 && key[KEY_ENTER])
                {


                   m = 2;
                }




    draw_sprite(buf, fundo, 0, 0);
    draw_sprite(buf, logo, 270, 40);
    textout_ex(buf, font, "Game", 310, 268, makecol(255,255,255), -1);
    textout_ex(buf, font, "Exit", 310, 338, makecol(255,255,255), -1);
    draw_sprite(buf, seta, 230, setay);
    draw_sprite(screen, buf, 0, 0);

    }
    destroy_bitmap(buf);
    destroy_bitmap(fundo);
    destroy_bitmap(seta);

    return m;
}
 ///função introdução
int intro()
{
    timer = 0;
  LOCK_FUNCTION(incrementa_timer);
  LOCK_VARIABLE(timer);
  install_int_ex(incrementa_timer, SECS_TO_TIMER(1));

    int marc = timer;
    int frame_papiro = 0;
    BITMAP* buff = create_bitmap(SCREEN_W, SCREEN_H);
    BITMAP* papiro[2];
    papiro[0] = load_bitmap("papiro.bmp", NULL);
    papiro[1] = load_bitmap("papiro2.bmp", NULL);
    while(m==0)
    {


        if(timer-marc >=3)
        {
            frame_papiro = 1;

            if(key[KEY_ENTER])
            {
                m = 1;
            }
        }
        draw_sprite(buff, papiro[frame_papiro], 0, 0);
        draw_sprite(screen, buff, 0, 0);

    }

    for(int i = 0; i <2; i++) {destroy_bitmap(papiro[i]);}
    destroy_bitmap(buff);

    return m;

}

int loading()
{

    milisegundos = 0;
  LOCK_FUNCTION(msec_counter);
  LOCK_VARIABLE(milisegundos);
  install_int_ex(msec_counter, MSEC_TO_TIMER(1));

    BITMAP* bf = create_bitmap(SCREEN_W, SCREEN_H);

    BITMAP* carregar[20];
    carregar[0] = load_bitmap("carregando1.bmp", NULL);
    carregar[1] = load_bitmap("carregando2.bmp", NULL);
    carregar[2] = load_bitmap("carregando3.bmp", NULL);
    carregar[3] = load_bitmap("carregando4.bmp", NULL);
    carregar[4] = load_bitmap("carregando5.bmp", NULL);
    carregar[5] = load_bitmap("carregando6.bmp", NULL);
    carregar[6] = load_bitmap("carregando7.bmp", NULL);
    carregar[7] = load_bitmap("carregando8.bmp", NULL);
    carregar[8] = load_bitmap("carregando9.bmp", NULL);
    carregar[9] = load_bitmap("carregando10.bmp", NULL);
    carregar[10] = load_bitmap("carregando1.bmp", NULL);
    carregar[11] = load_bitmap("carregando2.bmp", NULL);
    carregar[12] = load_bitmap("carregando3.bmp", NULL);
    carregar[13] = load_bitmap("carregando4.bmp", NULL);
    carregar[14] = load_bitmap("carregando5.bmp", NULL);
    carregar[15] = load_bitmap("carregando6.bmp", NULL);
    carregar[16] = load_bitmap("carregando7.bmp", NULL);
    carregar[17] = load_bitmap("carregando8.bmp", NULL);
    carregar[18] = load_bitmap("carregando9.bmp", NULL);
    carregar[19] = load_bitmap("carregando10.bmp", NULL);

    int frame_carregar = 0;

    while(m==3) {frame_carregar = (milisegundos / 100) % 20; if(frame_carregar == 19) {m = 9;}


    draw_sprite(bf, carregar[frame_carregar], 100, 400);
    textout_centre_ex(bf, font, "Loading", SCREEN_W/2, SCREEN_H/2, makecol(255,255,255), -1);
    draw_sprite(screen, bf, 0, 0);
    clear_to_color(bf, makecol(0,0,0));}


return m;
}

int morte()
{
         BITMAP* bufff = create_bitmap(SCREEN_W, SCREEN_H);
         BITMAP* game_over = load_bitmap("game_over.bmp", NULL);
         MIDI *morte = load_midi("morte.mid");
         play_midi(morte, TRUE);

         if(key[KEY_ENTER]){m=1;}
         else if(key[KEY_ESC]) { m=2;fecha_programa();}
         draw_sprite(bufff, game_over, 0, 0);
         textout_centre_ex(bufff, font, "To exit the game press ESC", 400, 460, makecol(255, 255, 255), -1);
         draw_sprite(screen, bufff, 0, 0);

     return m;
}

int ganhar()
{


    BITMAP* bfff = create_bitmap(SCREEN_W, SCREEN_H);

    BITMAP* ganhou = load_bitmap("ganhou.bmp", NULL);


    while(m==8) {rest(1200); m = 2; fecha_programa();}




    draw_sprite(bfff, ganhou, 0, 0);
    draw_sprite(screen, bfff, 0, 0);



return 0;
}

int main()
{
///iniciando
  allegro_init();
  install_timer();
  install_keyboard();
  install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
  set_color_depth(32);
  set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0);
  set_window_title("Naruto");

  exit_program = FALSE;
  LOCK_FUNCTION(fecha_programa);
  LOCK_VARIABLE(exit_program);
  set_close_button_callback(fecha_programa);

  ticks = 0;
  LOCK_FUNCTION(tick_counter);
  LOCK_VARIABLE(ticks);
  install_int_ex(tick_counter, BPS_TO_TIMER(2));

  timer = 0;
  LOCK_FUNCTION(incrementa_timer);
  LOCK_VARIABLE(timer);
  install_int_ex(incrementa_timer, SECS_TO_TIMER(1));


  milisegundos = 0;
  LOCK_FUNCTION(msec_counter);
  LOCK_VARIABLE(milisegundos);
  install_int_ex(msec_counter, MSEC_TO_TIMER(1));

  ///BITMAPS
  BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H);

  BITMAP* naruto[12];
  naruto[0] = load_bitmap("andou1.bmp", NULL);
  naruto[1] = load_bitmap("andou2.bmp", NULL);
  naruto[2] = load_bitmap("andou3.bmp", NULL);
  naruto[3] = load_bitmap("andou4.bmp", NULL);
  naruto[4] = load_bitmap("andou5.bmp", NULL);
  naruto[5] = load_bitmap("andou6.bmp", NULL);
  naruto[6] = load_bitmap("andou7.bmp", NULL);
  naruto[7] = load_bitmap("andou8.bmp", NULL);
  naruto[8] = load_bitmap("parado.bmp", NULL);
  naruto[9] = load_bitmap("pulando.bmp", NULL);
  naruto[10] = load_bitmap("murro_4.bmp", NULL);
  naruto[11] = load_bitmap("fumaca.bmp", NULL);


  BITMAP* sky = load_bitmap("sky.bmp", NULL);
  BITMAP* montanha = load_bitmap("montanha_hokage.bmp", NULL);
  BITMAP* cenario[8];
  for(int i =0; i<8;i++){cenario[i] = load_bitmap("cenario.bmp", NULL);}

  BITMAP* vale = load_bitmap("vale_do_fim.bmp", NULL);
  BITMAP* cenario2[8];
  for(int i =0; i<8;i++){cenario2[i] = load_bitmap("cenario2.bmp", NULL);}

  BITMAP* caverna = load_bitmap("caverna.bmp", NULL);
  BITMAP* chao = load_bitmap("chao.bmp", NULL);


  BITMAP* bloco = load_bitmap("bloco.bmp", NULL);
  BITMAP* bloco2 = load_bitmap("bloco2.bmp", NULL);

  BITMAP* manda[3];
  manda[0] = load_bitmap("manda.bmp", NULL);
  manda[1] = load_bitmap("manda2.bmp", NULL);
  manda[2] = load_bitmap("nada.bmp", NULL);

  BITMAP* vida[11];
  vida[0] = load_bitmap("vida_vazia.bmp", NULL);
  vida[1] = load_bitmap("vida_1.bmp", NULL);
  vida[2] = load_bitmap("vida_2.bmp", NULL);
  vida[3] = load_bitmap("vida_3.bmp", NULL);
  vida[4] = load_bitmap("vida_4.bmp", NULL);
  vida[5] = load_bitmap("vida_5.bmp", NULL);
  vida[6] = load_bitmap("vida_6.bmp", NULL);
  vida[7] = load_bitmap("vida_7.bmp", NULL);
  vida[8] = load_bitmap("vida_8.bmp", NULL);
  vida[9] = load_bitmap("vida_9.bmp", NULL);
  vida[10] = load_bitmap("vida_cheia.bmp", NULL);


  BITMAP* orochimaru[19];
  orochimaru[0] = load_bitmap("pri.bmp", NULL);
  orochimaru[1] = load_bitmap("seg.bmp", NULL);
  orochimaru[2] = load_bitmap("terc.bmp", NULL);
  orochimaru[3] = load_bitmap("qua.bmp", NULL);
  orochimaru[4] = load_bitmap("quin.bmp", NULL);
  orochimaru[5] = load_bitmap("sex.bmp", NULL);
  orochimaru[6] = load_bitmap("set.bmp", NULL);
  orochimaru[7] = load_bitmap("oit.bmp", NULL);
  orochimaru[8] = load_bitmap("nov.bmp", NULL);
  orochimaru[9] = load_bitmap("dez.bmp", NULL);
  orochimaru[10] = load_bitmap("onz.bmp", NULL);
  orochimaru[11] = load_bitmap("doze.bmp", NULL);
  orochimaru[12] = load_bitmap("trez.bmp", NULL);
  orochimaru[13] = load_bitmap("cato.bmp", NULL);
  orochimaru[14] = load_bitmap("quinz.bmp", NULL);
  orochimaru[15] = load_bitmap("sixteen.bmp", NULL);
  orochimaru[16] = load_bitmap("sevent.bmp", NULL);
  orochimaru[17] = load_bitmap("eiteen.bmp", NULL);
  orochimaru[18] = load_bitmap("caiu.bmp", NULL);

  BITMAP* vidas_oroc[5];
  vidas_oroc[0] = load_bitmap("vida_vazia_orochi.bmp", NULL);
  vidas_oroc[1] = load_bitmap("vida_1_orochi.bmp", NULL);
  vidas_oroc[2] = load_bitmap("vida_2_orochi.bmp", NULL);
  vidas_oroc[3] = load_bitmap("vida_3_orochi.bmp", NULL);
  vidas_oroc[4] = load_bitmap("vida_cheia_orochi.bmp", NULL);

  BITMAP* ganhou = load_bitmap("ganhou.bmp", NULL);


  SAMPLE *soco = load_sample("soco.wav");
  SAMPLE *pulo = load_sample("pulo.wav");
  MIDI *musica = load_midi("musica.mid");

  play_midi(musica, TRUE);//repetir a musica

  ///Variaveis
  float eixo_x = 0.0;
  float eixo_x_personagem = 250.0;
  float larg_pers = 80.0;
  float alt_pers = 80.0;
  float alt_bloco = 60.0;
  float larg_bloco = 60.0;
  float vel_x = 0.8;
  int num_frames = 8;
  int frame_atual = 0;
  int tempo_troca = 90;
  double direcao;
  int num_manda = 2;
  int frame_manda1 = 0;
  int frame_vida = 10;
  int frame_manda2 = 0;
  int frame_manda3 = 0;
  int frame_manda4 = 0;
  int frame_manda5 = 0;
  int frame_manda6 = 0;
  int frame_manda7 = 0;
  int frame_manda8 = 0;
  int frame_manda12 = 0;
  int frame_manda22 = 0;
  int frame_manda32 = 0;
  int frame_manda42 = 0;
  int frame_manda52 = 0;
  int frame_manda62 = 0;
  int frame_manda72 = 0;
  int frame_manda82 = 0;
  int frame_manda92 = 0;
  int frame_manda102 = 0;
  int frame_manda112 = 0;
  int frame_manda122 = 0;
  int frame_manda132 = 0;
  int frame_manda142 = 0;
  int frame_oro = 0;
  int frame_vida_oroc = 4;


   int marcador = timer; // MARCADOR DE TEMPO

    menu();
    if(m==2)
    {
        fecha_programa();
    }


    intro();

  ///GAME LOOP
  while(!exit_program)
  {
     while(m==1)
     {
     //CONTROLES

          if(key[KEY_ESC])
          {
              menu();
              if(m==2)
              {
                  fecha_programa();
              }
          }

         if(key[KEY_D])
         {
            frame_atual = (milisegundos / tempo_troca) % num_frames; //MUDANÇA DE FRAME DO NARUTO
            direcao = DRAW_SPRITE_NO_FLIP; //DIREÇÃO DO FRAME (SÓ FUNCIONA NO DRAW_SPRITE_EX)


            eixo_x = eixo_x - vel_x; // FAZ O CENARIO ANDAR (QUE DA A IMPRESSÃO DO NARUTO ESTA SE MOVENDO)
         }
         else if(key[KEY_A])
         {
             frame_atual = (milisegundos / tempo_troca) % num_frames; //MUDANÇA DE FRAME DO NARUTO
             direcao = DRAW_SPRITE_H_FLIP; //DIREÇÃO DO FRAME (SÓ FUNCIONA NO DRAW_SPRITE_EX)

            eixo_x = eixo_x + vel_x; // FAZ O CENARIO ANDAR (QUE DA A IMPRESSÃO DO NARUTO ESTA SE MOVENDO)
         }

         else
         {
             frame_atual = 8; // FRAME DO NARUTO PARADO


         }

          if(key[KEY_SPACE])
         {
             frame_atual = 10;
             play_sample(soco, 190, 128, 1000, 0); //volume, canal, velocidade e repeticao
         }

         if(key[KEY_W]&& eixo_y > 70) // PULO
         {

                vel_y = -3;
                frame_atual = 9;
                vel_y += gravidade; eixo_y += vel_y;
                play_sample(pulo, 190, 128, 1000, 0); //volume, canal, velocidade e repeticao
         }


        // COLISÃO
        if(colidir(250, eixo_y, eixo_x+860, 240, 50, 80, 255, 1)) ////COLISÃO 1ª SERIE DE BLOCOS
        {
            if(!key[KEY_W]){
                if(eixo_y != 175){eixo_y = 175;}
            }

        }
        else if (colidir(250, eixo_y, eixo_x+1760, 330, 50, 80, 360, 1)) //COLISÃO 2ª SERIE DE BLOCOS
        {
            if(!key[KEY_W]){
                if(eixo_y != 280){eixo_y = 280;}}
        }
        else if (colidir(250, eixo_y, eixo_x+2229, 254, 50, 80, 300, 1)) //COLISÃO 3ª SERIE DE BLOCOS
        {
            if(!key[KEY_W]){
                if(eixo_y != 220){eixo_y = 220;}}
        }
        else if (colidir(250, eixo_y, eixo_x+2915, 200, 50, 80, 600, 1)) //COLISÃO 4ª SERIE DE BLOCOS
        {
            if(!key[KEY_W]){
                if(eixo_y != 130){eixo_y = 130;}}
        }
        else if (colidir(250, eixo_y, eixo_x+4250, 155, 50, 80, 120, 1)) //COLISÃO 5ª SERIE DE BLOCOS
        {
            if(!key[KEY_W]){
                if(eixo_y != 105){eixo_y = 105;}}
        }
        else if (colidir(250, eixo_y, eixo_x+5400, 250, 50, 80, 200, 1)) //COLISÃO 6ª SERIE DE BLOCOS
        {
            if(!key[KEY_W]){
                if(eixo_y != 200){eixo_y = 200;}}
        }
        else{vel_y += gravidade; eixo_y += vel_y;} // FUNÇÃO DE GRAVIDADE

    if(frame_manda1 != 2){frame_manda1 = (milisegundos / 900) % num_manda;
        if(colidir(250, eixo_y, eixo_x+1015, 140, 50, 80, 150, 150)) ////COLISÃO 1ª COBRA
        {
            if(eixo_x<=-709 && eixo_x>=-730){eixo_x = -709;} // BLOQUEIA A PASSAGEM PELA FRENTE DA COBRA
            else if(eixo_x>=-860 && eixo_x<=-740){eixo_x = -860;} // BLOQUEIA A PASSAGEM POR TRAS DA COBRA
            if(key[KEY_SPACE])
            {
                frame_atual = 10;

                frame_manda1 = 2;

            }

            else if(frame_manda1 == 1 && timer - marcador >=1){frame_vida--; marcador = timer;if(frame_vida == 0){m = 8;}} // SERVE PARA NÃO FICAR PERDENDO VIDA CONTINUAMENTE
        }
    }

    if(frame_manda2 != 2){frame_manda2 = (milisegundos / 800) % num_manda;////COLISÃO 2ª COBRA
        if(colidir(250, eixo_y, eixo_x+1950, 240, 50, 80, 150, 150))
        {
            if(eixo_x<=-1649 && eixo_x>=-1665){eixo_x = -1649;}
            else if(eixo_x>=-1802 && eixo_x<=-1682){eixo_x = -1802;} // BLOQUEIA A PASSAGEM POR TRAS DA COBRA

            if(key[KEY_SPACE])
            {
                frame_atual = 10;

                frame_manda2= 2;

            }

            else if(frame_manda2 == 1 && timer - marcador >=1){frame_vida--; marcador = timer;if(frame_vida == 0){m=8;}}
        }
    }

     if(frame_manda3 != 2){frame_manda3 = (milisegundos / 700) % num_manda;////COLISÃO 3ª COBRA
         if(colidir(250, eixo_y, eixo_x+2329, 179, 50, 80, 150, 150))
            {
                if(eixo_x<=-2029 && eixo_x>=-2050){eixo_x = -2029;}
                else if(eixo_x>=-2182 && eixo_x<=-2062){eixo_x = -2182;} // BLOQUEIA A PASSAGEM POR TRAS DA COBRA

                if(key[KEY_SPACE])
                {
                    frame_atual = 10;

                    frame_manda3= 2;

                }

                else if(frame_manda3 == 1 && timer - marcador >=1){frame_vida--; marcador = timer;if(frame_vida == 0){m=8;}}
            }
        }

    if(frame_manda4 != 2){frame_manda4 = (milisegundos / 700) % num_manda;////COLISÃO 4ª COBRA
         if(colidir(250, eixo_y, eixo_x+2950, 100, 50, 80, 150, 150))
            {
                if(eixo_x<=-2650 && eixo_x>=-2666){eixo_x = -2650;}
                else if(eixo_x>=-2803 && eixo_x<=-2783){eixo_x = -2803;} // BLOQUEIA A PASSAGEM POR TRAS DA COBRA

                if(key[KEY_SPACE])
                {
                    frame_atual = 10;

                    frame_manda4= 2;

                }

                else if(frame_manda4 == 1 && timer - marcador >=1){frame_vida--; marcador = timer;if(frame_vida == 0){m=8;}}
            }
        }

    if(frame_manda5 != 2){frame_manda5 = (milisegundos / 600) % num_manda;////COLISÃO 5ª COBRA
         if(colidir(250, eixo_y, eixo_x+3400, 100, 50, 80, 150, 150))
            {
                if(eixo_x<=-3100 && eixo_x>=-3116){eixo_x = -3100;}
                else if(eixo_x>=-3253 && eixo_x<=-3133){eixo_x = -3253;} // BLOQUEIA A PASSAGEM POR TRAS DA COBRA

                if(key[KEY_SPACE])
                {
                    frame_atual = 10;

                    frame_manda5= 2;

                }

                else if(frame_manda5 == 1 && timer - marcador >=1){frame_vida--; marcador = timer;if(frame_vida == 0){m=8;}}
            }
        }


     if(frame_manda6 != 2){frame_manda6 = (milisegundos / 600) % num_manda;////COLISÃO 6ª COBRA
         if(colidir(250, eixo_y, eixo_x+4210, 60, 50, 80, 150, 150))
            {
                if(eixo_x<=-3910 && eixo_x>=-3926){eixo_x = -3910;}
                else if(eixo_x>=-4063 && eixo_x<=-3943){eixo_x = -4063;} // BLOQUEIA A PASSAGEM POR TRAS DA COBRA

                if(key[KEY_SPACE])
                {
                    frame_atual = 10;

                    frame_manda6= 2;

                }

                else if(frame_manda6 == 1 && timer - marcador >=1){frame_vida--; marcador = timer;if(frame_vida == 0){m=8;}}
            }
        }

    if(frame_manda7 != 2){frame_manda7 = (milisegundos / 500) % num_manda;////COLISÃO 7ª COBRA
         if(colidir(250, eixo_y, eixo_x+4748, 500, 50, 80, 150, 150))
            {
                if(eixo_x<=-4450 && eixo_x>=-4466){eixo_x = -4450;}
                else if(eixo_x>=-4603 && eixo_x<=-4480){eixo_x = -4603;} // BLOQUEIA A PASSAGEM POR TRAS DA COBRA

                if(key[KEY_SPACE])
                {
                    frame_atual = 10;

                    frame_manda7= 2;

                }

                else if(frame_manda7 == 1 && timer - marcador >=1){frame_vida--; marcador = timer;if(frame_vida == 0){m=8;}}
            }
        }


    if(frame_manda8 != 2){frame_manda8 = (milisegundos / 500) % num_manda;////COLISÃO 8ª COBRA
         if(colidir(250, eixo_y, eixo_x+5450, 175, 50, 80, 150, 150))
            {
                if(eixo_x<=-5150 && eixo_x>=-5166){eixo_x = -5150;}
                else if(eixo_x>=-5303 && eixo_x<=-5183){eixo_x = -5303;} // BLOQUEIA A PASSAGEM POR TRAS DA COBRA

                if(key[KEY_SPACE])
                {
                    frame_atual = 10;

                    frame_manda8= 2;

                }

                else if(frame_manda8 == 1 && timer - marcador >=1){frame_vida--; marcador = timer;if(frame_vida == 0){m=8;}}
            }
        }








         //CONDIÇÕES
        if(eixo_x <= -5599 && frame_manda1 == 2 && frame_manda2 == 2 && frame_manda3 == 2 && frame_manda4 == 2 && frame_manda5 == 2 && frame_manda6 == 2 && frame_manda7 == 2 && frame_manda8 == 2)
             {
                 frame_atual = 11;
                 eixo_x = -5600;
                 m = 3;

             }

         if(eixo_x<-5600)
         {
             eixo_x = -5600; // PONTO FINAL DO EIXO X

         }
         if(eixo_x>0)
         {
             eixo_x = 0; // PONTO INICIAL DO EIXO X
         }


         if(eixo_y > 460.0)
         {
             eixo_y = 460.0; // PONTO FINAL EIXO Y
         }






         //DRAW

         draw_sprite(buffer, sky, 0, 0);
         draw_sprite(buffer, montanha, 0, 0);
         draw_sprite(buffer, cenario[0], eixo_x, 10); //PRIMEIRO CENARIO
         for(int c = 1; c<8; c++){draw_sprite(buffer, cenario[c], eixo_x+800*c, 10);} // REPETIÇÃO DO CENARIO
         for(int b = 0; b<5; b++){draw_sprite(buffer, bloco, eixo_x+850+(60*b), 265);} //1ª SERIE DE BLOCOS
         for(int b = 0; b<7; b++){draw_sprite(buffer, bloco, eixo_x+1750+(60*b), 365);} //2ª SERIE DE BLOCOS
         for(int b = 0; b<6; b++){draw_sprite(buffer, bloco, eixo_x+2229+(60*b), 304);} //3ª SERIE DE BLOCOS
         for(int b = 0; b<11; b++){draw_sprite(buffer, bloco, eixo_x+2900+(60*b), 225);} //4ª SERIE DE BLOCOS
         for(int b = 0; b<3; b++){draw_sprite(buffer, bloco, eixo_x+4200+(60*b), 185);} //5ª SERIE DE BLOCOS
         for(int b = 0; b<5; b++){draw_sprite(buffer, bloco, eixo_x+5350+(60*b), 300);} //6ª SERIE DE BLOCOS
         draw_sprite_ex(buffer, manda[frame_manda1], eixo_x+1015, 140, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);//1ª COBRA
         draw_sprite_ex(buffer, manda[frame_manda2], eixo_x+1950, 240, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);//2ª COBRA
         draw_sprite_ex(buffer, manda[frame_manda3], eixo_x+2329, 179, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);//3ª COBRA
         draw_sprite_ex(buffer, manda[frame_manda4], eixo_x+2950, 100, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);//4ª COBRA
         draw_sprite_ex(buffer, manda[frame_manda5], eixo_x+3400, 100, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);//5ª COBRA
         draw_sprite_ex(buffer, manda[frame_manda6], eixo_x+4210, 60, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);//6ª COBRA
         draw_sprite_ex(buffer, manda[frame_manda7], eixo_x+4750, 420, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);//7ª COBRA
         draw_sprite_ex(buffer, manda[frame_manda8], eixo_x+5450, 175, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);//8ª COBRA
         draw_sprite_ex(buffer, naruto[frame_atual], eixo_x_personagem, eixo_y, DRAW_SPRITE_NORMAL, direcao);//PERSONAGEM
         draw_sprite(buffer, vida[frame_vida], 30, 50);
         textout_ex(buffer, font, "Vida", 40, 40, makecol(255,255,255), -1);
         draw_sprite(screen, buffer, 0, 0);

     }
     rest(1200);
     loading();
     if(m==9){m=4;}

     eixo_x = 0.0;

    while(m==4)
    {
        if(key[KEY_ESC])
          {
              menu();
              if(m==2)
              {
                  fecha_programa();
              }
          }
        if(key[KEY_D])
         {
            frame_atual = (milisegundos / tempo_troca) % num_frames; //MUDANÇA DE FRAME DO NARUTO
            direcao = DRAW_SPRITE_NO_FLIP; //DIREÇÃO DO FRAME (SÓ FUNCIONA NO DRAW_SPRITE_EX)


            eixo_x = eixo_x - vel_x; // FAZ O CENARIO ANDAR (QUE DA A IMPRESSÃO DO NARUTO ESTA SE MOVENDO)
         }
         else if(key[KEY_A])
         {
             frame_atual = (milisegundos / tempo_troca) % num_frames; //MUDANÇA DE FRAME DO NARUTO
             direcao = DRAW_SPRITE_H_FLIP; //DIREÇÃO DO FRAME (SÓ FUNCIONA NO DRAW_SPRITE_EX)

            eixo_x = eixo_x + vel_x; // FAZ O CENARIO ANDAR (QUE DA A IMPRESSÃO DO NARUTO ESTA SE MOVENDO)
         }

         else
         {
             frame_atual = 8; // FRAME DO NARUTO PARADO


         }

          if(key[KEY_SPACE])
         {
             frame_atual = 10;
         }

         if(key[KEY_W]&& eixo_y > 70) // PULO
         {

                vel_y = -3;
                frame_atual = 9;
                vel_y += gravidade; eixo_y += vel_y;
         }

        // COLISÃO
        if(colidir(250, eixo_y, eixo_x+941, 204, 50, 80, 90, 1)) ////COLISÃO 1ª SERIE DE BLOCOS
        {
            if(!key[KEY_W]){
                if(eixo_y != 135){eixo_y = 135;}}

        }
        else if (colidir(250, eixo_y, eixo_x+1614, 404, 50, 80, 360, 1)) //COLISÃO 2ª SERIE DE BLOCOS
        {
            if(!key[KEY_W]){
                if(eixo_y != 335){eixo_y = 335;}}
        }
        else if (colidir(250, eixo_y, eixo_x+1961, 324, 50, 80, 240, 1)) //COLISÃO 3ª SERIE DE BLOCOS
        {
            if(!key[KEY_W]){
                if(eixo_y != 255){eixo_y = 255;}}
        }
         else if (colidir(250, eixo_y, eixo_x+2461, 204, 50, 80, 300, 1)) //COLISÃO 4ª SERIE DE BLOCOS
        {
            if(!key[KEY_W]){
                if(eixo_y != 135){eixo_y = 135;}}
        }
        else if (colidir(250, eixo_y, eixo_x+3416, 204, 50, 80, 320, 1)) //COLISÃO 5ª SERIE DE BLOCOS
        {
            if(!key[KEY_W]){
                if(eixo_y != 135){eixo_y = 135;}}
        }

        else if (colidir(250, eixo_y, eixo_x+4610, 461, 50, 80, 190, 1)) //COLISÃO 6ª SERIE DE BLOCOS
        {
            if(!key[KEY_W]){
                if(eixo_y != 395){eixo_y = 395;}}
        }
        else if (colidir(250, eixo_y, eixo_x+5004, 190, 50, 80, 200, 1)) //COLISÃO 7ª SERIE DE BLOCOS
        {
            if(!key[KEY_W]){
                if(eixo_y != 121){eixo_y = 121;}}
        }

        else{vel_y += gravidade; eixo_y += vel_y;} // FUNÇÃO DE GRAVIDADE



        if(frame_manda12 != 2){frame_manda12 = (milisegundos / 700) % num_manda;
        if(colidir(250, eixo_y, eixo_x+900, 90, 50, 80, 150, 150)) ////COLISÃO 1ª COBRA
        {
            if(eixo_x<=-641 && eixo_x>=-657){eixo_x = -641;} // BLOQUEIA A PASSAGEM PELA FRENTE DA COBRA
            else if(eixo_x>=-794 && eixo_x<=-674){eixo_x = -794;} // BLOQUEIA A PASSAGEM POR TRAS DA COBRA
            if(key[KEY_SPACE])
            {
                frame_atual = 10;

                frame_manda12 = 2;

            }

            else if(frame_manda12 == 1 && timer - marcador >=1){frame_vida--; marcador = timer;if(frame_vida == 0){m=8;}} // SERVE PARA NÃO FICAR PERDENDO VIDA CONTINUAMENTE
        }
    }

    if(frame_manda22 != 2){frame_manda22 = (milisegundos / 700) % num_manda;////COLISÃO 2ª COBRA
        if(colidir(250, eixo_y, eixo_x+900, 500, 50, 80, 150, 150))
        {
            if(eixo_x<=-600 && eixo_x>=-616){eixo_x = -600;}
            else if(eixo_x>=-753 && eixo_x<=-633){eixo_x = -753;} // BLOQUEIA A PASSAGEM POR TRAS DA COBRA

            if(key[KEY_SPACE])
            {
                frame_atual = 10;

                frame_manda22= 2;

            }

            else if(frame_manda22 == 1 && timer - marcador >=1){frame_vida--; marcador = timer;if(frame_vida == 0){m=8;}}
        }
    }

     if(frame_manda32 != 2){frame_manda32 = (milisegundos / 600) % num_manda;////COLISÃO 3ª COBRA
         if(colidir(250, eixo_y, eixo_x+1200, 500, 50, 80, 150, 150))
            {
                if(eixo_x<=-900 && eixo_x>=-916){eixo_x = -900;}
                else if(eixo_x>=-1053 && eixo_x<=-933){eixo_x = -1053;} // BLOQUEIA A PASSAGEM POR TRAS DA COBRA

                if(key[KEY_SPACE])
                {
                    frame_atual = 10;

                    frame_manda32 = 2;

                }

                else if(frame_manda32 == 1 && timer - marcador >=1){frame_vida--; marcador = timer;if(frame_vida == 0){m=8;}}
            }
        }

    if(frame_manda42 != 2){frame_manda42 = (milisegundos / 600) % num_manda;////COLISÃO 4ª COBRA
         if(colidir(250, eixo_y, eixo_x+1700, 300, 50, 80, 150, 150))
            {
                if(eixo_x<=-1400 && eixo_x>=-1416){eixo_x = -1400;}
                else if(eixo_x>=-1553 && eixo_x<=-1433){eixo_x = -1553;} // BLOQUEIA A PASSAGEM POR TRAS DA COBRA

                if(key[KEY_SPACE])
                {
                    frame_atual = 10;

                    frame_manda42 = 2;

                }

                else if(frame_manda42 == 1 && timer - marcador >=1){frame_vida--; marcador = timer;if(frame_vida == 0){m=8;}}
            }
        }

    if(frame_manda52 != 2){frame_manda52 = (milisegundos / 600) % num_manda;////COLISÃO 5ª COBRA
         if(colidir(250, eixo_y, eixo_x+2000, 230, 50, 80, 150, 150))
            {
                if(eixo_x<=-1700 && eixo_x>=-1716){eixo_x = -1700;}
                else if(eixo_x>=-1853 && eixo_x<=-1733){eixo_x = -1853;} // BLOQUEIA A PASSAGEM POR TRAS DA COBRA

                if(key[KEY_SPACE])
                {
                    frame_atual = 10;

                    frame_manda52 = 2;

                }

                else if(frame_manda52 == 1 && timer - marcador >=1){frame_vida--; marcador = timer;if(frame_vida == 0){m=8;}}
            }
        }


     if(frame_manda62 != 2){frame_manda62 = (milisegundos / 600) % num_manda;////COLISÃO 6ª COBRA
         if(colidir(250, eixo_y, eixo_x+2600, 100, 50, 80, 150, 150))
            {
                if(eixo_x<=-2300 && eixo_x>=-2316){eixo_x = -2300;}
                else if(eixo_x>=-2453 && eixo_x<=-2333){eixo_x = -2453;} // BLOQUEIA A PASSAGEM POR TRAS DA COBRA

                if(key[KEY_SPACE])
                {
                    frame_atual = 10;

                    frame_manda62 = 2;

                }

                else if(frame_manda62 == 1 && timer - marcador >=1){frame_vida--; marcador = timer;if(frame_vida == 0){m=8;}}
            }
        }

    if(frame_manda72 != 2){frame_manda72 = (milisegundos / 500) % num_manda;////COLISÃO 7ª COBRA
         if(colidir(250, eixo_y, eixo_x+2500, 500, 50, 80, 150, 150))
            {
                if(eixo_x<=-2200 && eixo_x>=-2216){eixo_x = -2200;}
                else if(eixo_x>=-2353 && eixo_x<=-2233){eixo_x = -2353;} // BLOQUEIA A PASSAGEM POR TRAS DA COBRA

                if(key[KEY_SPACE])
                {
                    frame_atual = 10;

                    frame_manda72 = 2;

                }

                else if(frame_manda72 == 1 && timer - marcador >=1){frame_vida--; marcador = timer;if(frame_vida == 0){m=8;}}
            }
        }


    if(frame_manda82 != 2){frame_manda82 = (milisegundos / 500) % num_manda;////COLISÃO 8ª COBRA
         if(colidir(250, eixo_y, eixo_x+3000, 500, 50, 80, 150, 150))
            {
                if(eixo_x<=-2700 && eixo_x>=-2716){eixo_x = -2700;}
                else if(eixo_x>=-2853 && eixo_x<=-2733){eixo_x = -2853;} // BLOQUEIA A PASSAGEM POR TRAS DA COBRA

                if(key[KEY_SPACE])
                {
                    frame_atual = 10;

                    frame_manda82 = 2;

                }

                else if(frame_manda82 == 1 && timer - marcador >=1){frame_vida--; marcador = timer;if(frame_vida == 0){m=8;}}
            }
        }


        if(frame_manda92 != 2){frame_manda92 = (milisegundos / 400) % num_manda;
        if(colidir(250, eixo_y, eixo_x+3600, 95, 50, 80, 150, 150)) ////COLISÃO 1ª COBRA
        {
            if(eixo_x<=-3300 && eixo_x>=-3316){eixo_x = -3300;} // BLOQUEIA A PASSAGEM PELA FRENTE DA COBRA
            else if(eixo_x>=-3453 && eixo_x<=-3333){eixo_x = -3453;} // BLOQUEIA A PASSAGEM POR TRAS DA COBRA
            if(key[KEY_SPACE])
            {
                frame_atual = 10;

                frame_manda92 = 2;

            }

            else if(frame_manda92 == 1 && timer - marcador >=1){frame_vida--; marcador = timer;if(frame_vida == 0){m=8;}} // SERVE PARA NÃO FICAR PERDENDO VIDA CONTINUAMENTE
        }
    }

    if(frame_manda102 != 2){frame_manda102 = (milisegundos / 400) % num_manda;////COLISÃO 2ª COBRA
        if(colidir(250, eixo_y, eixo_x+4000, 500, 50, 80, 150, 150))
        {
            if(eixo_x<=-3700 && eixo_x>=-3716){eixo_x = -3700;}
            else if(eixo_x>=-3853 && eixo_x<=-3733){eixo_x = -3853;} // BLOQUEIA A PASSAGEM POR TRAS DA COBRA

            if(key[KEY_SPACE])
            {
                frame_atual = 10;

                frame_manda102= 2;

            }

            else if(frame_manda102 == 1 && timer - marcador >=1){frame_vida--; marcador = timer;if(frame_vida == 0){m=8;}}
        }
    }

     if(frame_manda112 != 2){frame_manda112 = (milisegundos / 400) % num_manda;////COLISÃO 3ª COBRA
         if(colidir(250, eixo_y, eixo_x+4500, 500, 50, 80, 150, 150))
            {
                if(eixo_x<=-4200 && eixo_x>=-4216){eixo_x = -4200;}
                else if(eixo_x>=-4353 && eixo_x<=-4233){eixo_x = -4353;} // BLOQUEIA A PASSAGEM POR TRAS DA COBRA

                if(key[KEY_SPACE])
                {
                    frame_atual = 10;

                    frame_manda112 = 2;

                }

                else if(frame_manda112 == 1 && timer - marcador >=1){frame_vida--; marcador = timer;if(frame_vida == 0){m=8;}}
            }
        }

    if(frame_manda122 != 2){frame_manda122 = (milisegundos / 400) % num_manda;////COLISÃO 4ª COBRA
         if(colidir(250, eixo_y, eixo_x+4700, 340, 50, 80, 150, 150))
            {
                if(eixo_x<=-4400 && eixo_x>=-4416){eixo_x = -4400;}
                else if(eixo_x>=-4553 && eixo_x<=-4433){eixo_x = -4553;} // BLOQUEIA A PASSAGEM POR TRAS DA COBRA

                if(key[KEY_SPACE])
                {
                    frame_atual = 10;

                    frame_manda122 = 2;

                }

                else if(frame_manda122 == 1 && timer - marcador >=1){frame_vida--; marcador = timer;if(frame_vida == 0){m=8;}}
            }
        }

    if(frame_manda132 != 2){frame_manda132 = (milisegundos / 400) % num_manda;////COLISÃO 5ª COBRA
         if(colidir(250, eixo_y, eixo_x+5000, 90, 50, 80, 150, 150))
            {
                if(eixo_x<=-4700 && eixo_x>=-4716){eixo_x = -4700;}
                else if(eixo_x>=-4853 && eixo_x<=-4733){eixo_x = -4853;} // BLOQUEIA A PASSAGEM POR TRAS DA COBRA

                if(key[KEY_SPACE])
                {
                    frame_atual = 10;

                    frame_manda132 = 2;

                }

                else if(frame_manda132 == 1 && timer - marcador >=1){frame_vida--; marcador = timer;if(frame_vida == 0){m=8;}}
            }
        }


     if(frame_manda142 != 2){frame_manda142 = (milisegundos / 400) % num_manda;////COLISÃO 6ª COBRA
         if(colidir(250, eixo_y, eixo_x+5500, 500, 50, 80, 150, 150))
            {
                if(eixo_x<=-5200 && eixo_x>=-5216){eixo_x = -5200;}
                else if(eixo_x>=-5353 && eixo_x<=-5233){eixo_x = -5353;} // BLOQUEIA A PASSAGEM POR TRAS DA COBRA

                if(key[KEY_SPACE])
                {
                    frame_atual = 10;

                    frame_manda142 = 2;

                }

                else if(frame_manda142 == 1 && timer - marcador >=1){frame_vida--; marcador = timer; if(frame_vida == 0){m=8;}}
            }
        }




         //CONDIÇÕES

        if(eixo_x <= -5599 && frame_manda12 == 2 && frame_manda22 == 2 && frame_manda32 == 2 && frame_manda42 == 2 &&
                              frame_manda52 == 2 && frame_manda62 == 2 && frame_manda72 == 2 && frame_manda82 == 2 &&
                              frame_manda92 == 2 && frame_manda102 == 2 && frame_manda112 == 2 && frame_manda132 == 2 &&
                              frame_manda142 == 2)
             {
                 frame_atual = 11;
                 eixo_x = -5600;
                 m = 3;

             }

         if(eixo_x<-5600)
         {
             eixo_x = -5600; // PONTO FINAL DO EIXO X

         }
         if(eixo_x>0)
         {
             eixo_x = 0; // PONTO INICIAL DO EIXO X
         }


         if(eixo_y > 460.0)
         {
             eixo_y = 460.0; // PONTO FINAL EIXO Y
         }





         //DRAW

         draw_sprite(buffer, vale, 0, 0);
         draw_sprite(buffer, cenario2[0], eixo_x, 10);
         for(int c = 1; c<8; c++){draw_sprite(buffer, cenario2[c], eixo_x+800*c, 10);} // REPETIÇÃO DO CENARIO
         for(int b = 0; b<2; b++){draw_sprite(buffer, bloco2, eixo_x+941+(60*b), 204);} //1ª SERIE DE BLOCOS
         for(int b = 0; b<7; b++){draw_sprite(buffer, bloco2, eixo_x+1614+(60*b), 404);} //2ª SERIE DE BLOCOS
         for(int b = 0; b<4; b++){draw_sprite(buffer, bloco2, eixo_x+1961+(60*b), 324);} //3ª SERIE DE BLOCOS
         for(int b = 0; b<6; b++){draw_sprite(buffer, bloco2, eixo_x+2461+(60*b), 204);} //5ª SERIE DE BLOCOS
         for(int b = 0; b<6; b++){draw_sprite(buffer, bloco2, eixo_x+3416+(60*b), 204);} //6ª SERIE DE BLOCOS
         for(int b = 0; b<4; b++){draw_sprite(buffer, bloco2, eixo_x+4610+(60*b), 461);} //7ª SERIE DE BLOCOS
         for(int b = 0; b<3; b++){draw_sprite(buffer, bloco2, eixo_x+5004+(60*b), 190);} //8ª SERIE DE BLOCOS

         draw_sprite_ex(buffer, manda[frame_manda12], eixo_x+941,  90, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);//1ª COBRA
         draw_sprite_ex(buffer, manda[frame_manda22], eixo_x+900, 400, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);//2ª COBRA
         draw_sprite_ex(buffer, manda[frame_manda32], eixo_x+1200, 400, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);//3ª COBRA
         draw_sprite_ex(buffer, manda[frame_manda42], eixo_x+1700, 300, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);//4ª COBRA
         draw_sprite_ex(buffer, manda[frame_manda52], eixo_x+2000, 230, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);//5ª COBRA
         draw_sprite_ex(buffer, manda[frame_manda62], eixo_x+2600, 100, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);//6ª COBRA
         draw_sprite_ex(buffer, manda[frame_manda72], eixo_x+2500, 400, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);//7ª COBRA
         draw_sprite_ex(buffer, manda[frame_manda82], eixo_x+3000, 400, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);//8ª COBRA
         draw_sprite_ex(buffer, manda[frame_manda92], eixo_x+3600, 95, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);//9ª COBRA
         draw_sprite_ex(buffer, manda[frame_manda102], eixo_x+4000, 400, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);//10ª COBRA
         draw_sprite_ex(buffer, manda[frame_manda112], eixo_x+4500, 400, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);//11ª COBRA
         draw_sprite_ex(buffer, manda[frame_manda122], eixo_x+4700, 340, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);//12ª COBRA
         draw_sprite_ex(buffer, manda[frame_manda132], eixo_x+5000, 90, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);//13ª COBRA
         draw_sprite_ex(buffer, manda[frame_manda142], eixo_x+5500, 400, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);//14ª COBRA

         draw_sprite_ex(buffer, naruto[frame_atual], eixo_x_personagem, eixo_y, DRAW_SPRITE_NORMAL, direcao);//PERSONAGEM
         draw_sprite(buffer, vida[frame_vida], 30, 50);
         textout_ex(buffer, font, "Vida", 40, 40, makecol(255,255,255), -1);
         draw_sprite(screen, buffer, 0, 0);
    }
    rest(1200);
    loading();
    eixo_x = 0.0;
    frame_vida = 10;
    vel_x = 1.5;
    if(m==9){m=5;}

  while(m==5)
  {
      if(key[KEY_ESC])
          {
              menu();
              if(m==2)
              {
                  fecha_programa();
              }
          }

         if(key[KEY_A])
         {
            frame_atual = (milisegundos / tempo_troca) % num_frames; //MUDANÇA DE FRAME DO NARUTO
            direcao = DRAW_SPRITE_H_FLIP; //DIREÇÃO DO FRAME (SÓ FUNCIONA NO DRAW_SPRITE_EX)


            eixo_x_personagem = eixo_x_personagem - vel_x; //naruto que anda
         }
         else if(key[KEY_D])
         {
             frame_atual = (milisegundos / tempo_troca) % num_frames; //MUDANÇA DE FRAME DO NARUTO
             direcao = DRAW_SPRITE_NO_FLIP; //DIREÇÃO DO FRAME (SÓ FUNCIONA NO DRAW_SPRITE_EX)

            eixo_x_personagem = eixo_x_personagem + vel_x; //naruto que anda
         }

         else
         {
             frame_atual = 8; // FRAME DO NARUTO PARADO


         }

          if(key[KEY_SPACE])
         {
             frame_atual = 10;
         }

         if(key[KEY_W]&& eixo_y > 80) // PULO
         {


                vel_y = -3;
                frame_atual = 9;
                vel_y += gravidade; eixo_y += vel_y;

         }
         else{vel_y += gravidade; eixo_y += vel_y;}




        frame_oro = (milisegundos / 250) % 18;

        if(eixo_x_personagem + 100 > 500 && eixo_x_personagem < 500+100)
        {

            if(frame_oro == 13 || frame_oro == 14 || frame_oro== 15 || frame_oro== 16 || frame_oro == 17 && eixo_x_personagem == 450)
            {
                if(key[KEY_SPACE]){
                    frame_atual = 10;
                    if(timer-marcador >=1)
                    {
                        frame_vida_oroc--; marcador = timer;
                        if(frame_vida_oroc==0){frame_oro = 18; m = 10;}
                    }

                    }




            }
            else if(timer - marcador >=3){frame_vida--; marcador = timer; if(frame_vida == 0){m=8;} }
        }





         //CONDIÇÕES


         if(eixo_x_personagem<0)
         {
             eixo_x_personagem = 0; // PONTO FINAL DO EIXO X
         }
         if(eixo_x_personagem>750)
         {
             eixo_x_personagem = 750;
              // PONTO INICIAL DO EIXO X
         }


         if(eixo_y > 420.0)
         {
             eixo_y = 420.0; // PONTO FINAL EIXO Y
         }






         //DRAW


         draw_sprite(buffer, caverna, 0, 0);
         draw_sprite(buffer, chao, 0, 0);
         draw_sprite_ex(buffer, orochimaru[frame_oro], 300, 350, DRAW_SPRITE_NORMAL, DRAW_SPRITE_H_FLIP);
         draw_sprite_ex(buffer, naruto[frame_atual], eixo_x_personagem, eixo_y, DRAW_SPRITE_NORMAL, direcao);
         draw_sprite(buffer, vida[frame_vida], 30, 50);
         draw_sprite(buffer, vidas_oroc[frame_vida_oroc], 550, 50);
         textout_ex(buffer, font, "Vida", 40, 40, makecol(255,255,255), -1);
         draw_sprite(screen, buffer, 0, 0);

        }

  if(m==8)
  {
      morte();
  }
  else if(m==10){ ganhar();}



  }

  ///FINALIZAÇÃOs
  destroy_bitmap(buffer);
  destroy_bitmap(naruto);
  destroy_bitmap(sky);
  destroy_bitmap(montanha);
  destroy_bitmap(cenario);
  destroy_bitmap(bloco);
  destroy_bitmap(manda);
  destroy_bitmap(vale);
  destroy_bitmap(cenario2);
  destroy_bitmap(bloco2);
  destroy_sample(soco);
  destroy_midi(musica);
  destroy_sample(pulo);


  return 0;
}
END_OF_MAIN();

///FUNÇÃO COLISÃO
int colidir(int ax, int ay, int bx, int by, int aw, int ah, int bw, int bh){
    if(ax+aw>bx && ax<bx+bw && ay+ah >by && ay<by+bh)return 1; // AX = EIXO X DO PERSONAGEM; AY = EIXO Y DO PERSONAGEM; BX = EIXO X DO OBJETO; BY = EIXO Y DO OBJETO; AW = LARGURA DO PERSONAGEM; AH = ALTURA DO PERSONAGEM; BW = LARGURA DO OBJETO; BH = ALTURA DO OBJETO

    return 0;}









#include "Controller.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Tiro.h"
#include <iostream>

using namespace std;

Controller::Controller(Model &model) : model(model){
        this->rodando = true;
        this->state = SDL_GetKeyboardState(nullptr);
        f=0;
        a=0;
}

void Controller::polling(){
      SDL_PumpEvents(); // atualiza estado do teclado
      if (state[SDL_SCANCODE_LEFT]) model.set_x_atual(model.get_x_atual()-10);
      if (state[SDL_SCANCODE_RIGHT]) model.set_x_atual(model.get_x_atual() + 10);
      if (state[SDL_SCANCODE_UP]) model.set_y_atual(model.get_y_atual() - 10);
      if (state[SDL_SCANCODE_DOWN]) model.set_y_atual(model.get_y_atual() + 10);
      if(state[SDL_SCANCODE_SPACE]) {
          float x = model.get_x_atual();
          float y = model.get_y_atual();
          //float vx = (model.get_vx_atual() > 0) ? 16. : 0. ;
          float vy = -16;
          float dt = model.get_dt();
          Tiro tiroNave = Tiro(x,y,0,vy,dt);
          tiroNave.flag = true;
          model.setTiro(tiroNave);
          cout << "Cheguei no negocio" << endl;
      }

      while (SDL_PollEvent(&(this->evento))) {
        if (this->evento.type == SDL_QUIT) {
          this->rodando = false;
        }
        // Exemplos de outros eventos.
        // Que outros eventos poderiamos ter e que sao uteis?
        //if (evento.type == SDL_KEYDOWN) {
        //}
        //if (evento.type == SDL_MOUSEBUTTONDOWN) {
        //}
    }
} 

bool Controller::get_rodando(){
      return this->rodando;
}

void Controller::calcular_forca(){
    f = -(model.get_x_atual()-320)*model.get_k() - model.get_b()*model.get_v_atual();
}
void Controller::estimar_aceleracao(){
    a = f/model.get_m();
}
void Controller::calcular_velocidade(){
    model.set_v_atual(model.get_v_atual() + a * model.get_dt());
}
void Controller::calcular_posicao(){  
    model.set_x_atual(model.get_x_atual() + model.get_v_atual() * model.get_dt());
}
void Controller::update(){
    //calcular_forca();
    //estimar_aceleracao();   
    //calcular_velocidade();
    //calcular_posicao();              
}
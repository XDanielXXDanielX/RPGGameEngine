#include "map.hpp"

tiny_location mapper::build_tiny_location(T x, T y, T z){
  tiny_location temp;
  temp.x = x;
  temp.y = y;
  temp.z = z;
}

mapper::location::location(T x, T y, T z){
  Pnow.x = x;
  Pnow.y = y;
  Pnow.z = z;
}

mapper::location::location(tiny_location const& now){
  Pnow = now;
}

mapper::location::location(tiny_location const& now, tiny_location const& previous){
  Pnow = now;
  Pprevious = previous;
}

mapper::location::location(std::string const& code){
  std::string temp = code;
  int count = 0;
  std::string to_convert[2] = { "", "", ""};
  for( char a : temp){
    if( a >= 48 && a <= 57){
      to_convert[count] = to_convert[count] + a;
    }else if( a == ";"){
      count++;
    }else if( a == "}"){
      break;
    }
  }
  Pnow.z = stoull(to_convert[0]);
  Pnow.x = stoull(to_convert[1]);
  Pnow.y = stoull(to_convert[2]);
}

tiny_location mapper::location::get_location(void){
  return Pnow;
}

tiny_location mapper::location::get_prev_location(void){
  return Pprevious;
}

std::string mapper::location::write_now_code(void){
  return "{" + Pnow.z + ";" + Pnow.x + ";" + Pnow.y + "}";
}

std::string mapper::location::write_prev_code(void){
  return "{" + Pprevious.z + ";" + Pprevious.x + ";" + Pprevious.y + "}";
}

location mapper::location::operator+(location const& a){
  Pprevious = Pnow;
  Pnow.x = Pnow.x + a.get_location().x;
  Pnow.y = Pnow.y + a.get_location().y;
  Pnow.z = Pnow.z + a.get_location().z;
}

location mapper::location::operator+(tiny_location a){
  Pprevious = Pnow;
  Pnow.x = Pnow.x + a.x;
  Pnow.y = Pnow.y + a.y;
  Pnow.z = Pnow.z + a.z;
}

location mapper::location::operator+(direction6 a){
  Pprevious = Pnow;
  switch (a) {
    case up:
      location temp(0, -1, 0);
      this = this + temp;
    case right:
      location temp(1, 0, 0);
      this = this + temp;
    case down:
      location temp(0, 1, 0);
      this = this + temp;
    case left:
      location temp(0, -1, 0);
      this = this + temp;
    case floor_up:
      location temp(0, 0, -1);
      this = this + temp;
    case floor_down:
      location temp(0, 0, 1);
      this = this + temp;
  }
}

location mapper::location::operator-(location const& a){
  Pprevious = Pnow;
  Pnow.x = Pnow.x - a.get_location().x;
  Pnow.y = Pnow.y - a.get_location().y;
  Pnow.z = Pnow.z - a.get_location().z;
}

location mapper::location::operator-(tiny_location a){
  Pprevious = Pnow;
  Pnow.x = Pnow.x + a.x;
  Pnow.y = Pnow.y + a.y;
  Pnow.z = Pnow.z + a.z;
}

location mapper::location::operator-(direction6 a){
  Pprevious = Pnow;
  switch (a) {
    case up:
      location temp(0, 1, 0);
      this = this + temp;
    case right:
      location temp(-1, 0, 0);
      this = this + temp;
    case down:
      location temp(0, -1, 0);
      this = this + temp;
    case left:
      location temp(0, 1, 0);
      this = this + temp;
    case floor_up:
      location temp(0, 0, 1);
      this = this + temp;
    case floor_down:
      location temp(0, 0, -1);
      this = this + temp;
}

location& mapper::location::operator=(location const& a){
  if(this!=a){
    Pprevious = Pnow;
    Pnow.x = a.get_location().x;
    Pnow.y = a.get_location().y;
    Pnow.z = a.get_location().z;
  }
}

location& mapper::location::operator=(tiny_location a){
  Pprevious = Pnow;
  Pnow = a;
}

bool mapper::location::operator==(location a){
  if( a.get_location().x == Pnow.x &&
      a.get_location().y == Pnow.y &&
      a.get_location().z == Pnow.z){
    return true;
  } else{
    return false;
  }
}

bool mapper::location::operator==(tiny_location a){
  if( a.x == Pnow.x && a.y == Pnow.y && a.z == Pnow.z){
    return true;
  } else{
    return false;
  }
}

bool mapper::location::operator!=(location a){
  if( a.get_location().x == Pnow.x &&
      a.get_location().y == Pnow.y &&
      a.get_location().z == Pnow.z){
    return false;
  } else{
    return true;
  }
}

bool mapper::location::operator!=(tiny_location a){
  if( a.x == Pnow.x && a.y == Pnow.y && a.z == Pnow.z){
    return false;
  } else{
    return true;
  }
}

mapper::range::range(void){

}

mapper::range::range(std::string code){

}

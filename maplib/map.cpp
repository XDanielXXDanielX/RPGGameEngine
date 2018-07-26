#include "map.hpp"

std::vector<std::string> mapper::tools::cuts(std::string const& str,
                                             std::string const& list){
  std::vector<std::string> result;
  std::vector<char> cutter;
  for( char c : list){
    cutter.push_back(c);
  }
  result.push_back("");
  bool is = false;
  for( char c : str){
    for( char d : cutter){
      if( c == d){
        is = true;
        break;
      }
    }
    if(is){
      cutter.push_back("");
    }else{
      result[result.size()-1] = result[result.size()-1] + c;
    }
  }
  if(result[result.size()-1] == ""){
    result.pop_back();
  }
}

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
  std::vector<std::string> on_plus_cutter = tools::cuts(code, "+");
  std::vector<std::string[1]> parsed;
  std::vector<std::string[1][2]> parsed_coords_s;
  std::vector<T[1][2]> parsed_coords_n;
  for( std::string s : on_plus_cutter){
    std::vector<std::string> tempv;
    std::string[1] tempa;
    if(s.find(":") != std::string::npos){
      tempv = tools::cuts(s, ":");
      tempa[0] = tempv[0];
      tempa[1] = tempv[1];
      parsed.push_back(tempa);
    }else{
      tempa[0] = s;
      tempa[1] = "";
    }
  }

  for(std::string s1[1] : parsed){
    std::string[1][2] tempa;
    std::vector<std::string> tempv;
    if(s1 != ""){
      tempv = tools::cuts(s2, "{};");
    }
    for(std::string& scrut[1] : tempa){
      if(s1 != ""){
        scrut[0] = tempv[0];
        scrut[1] = tempv[1];
        scrut[2] = tempv[2];
      }
      else{
        scrut[0] = "";
        scrut[1] = "";
        scrut[2] = "";
      }
    }
    parsed_coords_s.push_back(tempa);
  }

  int i, j, y = 0;
  for(std::string scrut1[1][2] : parsed_coords_s){
    T n1[1][2];
    for(std::string scrut2[2] : scrut1){
      T n2[2];
      for(std::string scrut3 : scrut2){
        T n3;
        if(n3 != ""){
          n3 = stoll(scrut3);
        }
        else{
          n3 = static_cast<long long int>(-1);
        }
        n2[y] = n3;
        y++;
      }
      n1[j] = n2;
      j++;
    }
    parsed_coords_n.push_back(n1);
  }

  std::vector<std::vector<std::unique_ptr<location> > > parsedl;
  for(long long int scrutn1[1][2] : parsed_coords_n){
    parsedl.push_back();
    for(long long int scrutn2[2] : scrutn1){
      if(scrutn2[0] != -1){
        parsedl[parsedl.size()-1].push_back(new location(scrutn2[1], scrutn2[2], scrutn2[0]));
      }
    }
  }

  for(std::vector<std::unique_ptr<location> >& scrut : parsedl){
    if(scrut.size() == 1){
      blocks_pos.push_back(*(new location(scrut[0]->get_location())));
    }else if(scrut.size() == 2){
      tiny_location start = scrut[0]->get_location();
      tiny_location end = scrut[1]->get_location();
      tiny_location inc;
      if(start.x < end.x){
        if(start.y < end.y){
          if(start.z < end.z){
            for(inc.x = start.x; inc.x <= end.x; inc.x++){
              for(inc.y = start.y; inc.y <= end.y; inc.y++){
                for(inc.z = start.z; inc.z <= end.z; inc.z++){
                  blocks_pos.push_back(*(new location(inc)));
                }
              }
            }
          }else{
            for(inc.x = start.x; inc.x <= end.x; inc.x++){
              for(inc.y = start.y; inc.y <= end.y; inc.y++){
                for(inc.z = end.z; inc.z <= start.z; inc.z++){
                  blocks_pos.push_back(*(new location(inc)));
                }
              }
            }
          }
        }else{
          if(start.z < end.z){
            for(inc.x = start.x; inc.x <= end.x; inc.x++){
              for(inc.y = end.y; inc.y <= start.y; inc.y++){
                for(inc.z = start.z; inc.z <= end.z; inc.z++){
                  blocks_pos.push_back(*(new location(inc)));
                }
              }
            }
          }else{
            for(inc.x = start.x; inc.x <= end.x; inc.x++){
              for(inc.y = end.y; inc.y <= begin.y; inc.y++){
                for(inc.z = end.z; inc.z <= begin.z; inc.z++){
                  blocks_pos.push_back(*(new location(inc)));
                }
              }
            }
          }
        }
      }else{
        if(start.y < end.y){
          if(start.z < end.z){
            for(inc.x = end.x; inc.x <= begin.x; inc.x++){
              for(inc.y = start.y; inc.y <= end.y; inc.y++){
                for(inc.z = start.z; inc.z <= end.z; inc.z++){
                  blocks_pos.push_back(*(new location(inc)));
                }
              }
            }
          }else{
            for(inc.x = end.x; inc.x <= begin.x; inc.x++){
              for(inc.y = start.y; inc.y <= end.y; inc.y++){
                for(inc.z = end.z; inc.z <= start.z; inc.z++){
                  blocks_pos.push_back(*(new location(inc)));
                }
              }
            }
          }
        }else{
          if(start.z < end.z){
            for(inc.x = end.x; inc.x <= begin.x; inc.x++){
              for(inc.y = end.y; inc.y <= start.y; inc.y++){
                for(inc.z = start.z; inc.z <= end.z; inc.z++){
                  blocks_pos.push_back(*(new location(inc)));
                }
              }
            }
          }else{
            for(inc.x = end.x; inc.x <= begin.x; inc.x++){
              for(inc.y = end.y; inc.y <= begin.y; inc.y++){
                for(inc.z = end.z; inc.z <= begin.z; inc.z++){
                  blocks_pos.push_back(*(new location(inc)));
                }
              }
            }
          }
        }
      }
    }
  }
  sort();
}

void mapper::range::sort(void){
  if(blocks_pos.size()){
    std::vector<location> organized;
    int x, y, z = 0;
    tiny_location max;
    max = blocks_pos[0].x
    for( location scrut : blocks_pos){
      max.x = ((scrut.get_location().x > max.x)?scrut.get_location().x:max.x);
      max.y = ((scrut.get_location().y > max.y)?scrut.get_location().y:max.y);
      max.z = ((scrut.get_location().z > max.z)?scrut.get_location().z:max.z);
    }
    for(z = 0; z <= max.z; z++){
      for(y = 0; y <= max.y; y++){
        for(x = 0; x <= max.x; y++){
          tiny_location cmp;
          cmp.x = x;
          cmp.y = y;
          cmp.z = z;
          for( location scrut : blocks_pos){
            if( scrut == cmp ){
              organized.push_back(scrut);
            }
          }
        }
      }
    }
    blocks_pos = organized;
  }
}

std::string mapper::range::write_code(void){
  sort();

}
